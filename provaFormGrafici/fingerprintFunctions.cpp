
#include <string.h>
#include "fxISOdll.h"
#include "fxISOenrdlg.h" 
#include "fxISOImageTools.h"
#include "AcquisitionWarnings.h"
#include <tchar.h>
#include <windows.h>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "fingerprintFunctions.h"
#include <stdio.h>
#include <vector> 
#include <regex>
#include <sstream>



namespace fs = std::filesystem;

using namespace System;
using namespace System::IO;
using namespace std;

FxBuffer gImage, gModel;

int CaptureFinger(char* filename)
{
	float q;
	int err;

	//Fingerprint acquisition
	err = FxISO_Fing_AcquireAutomatic(NULL, -1, -1, &q, 50, 20, 1.5);
	if (err)
		return err;

	//Image saved to file
	err = FxISO_Fing_SaveToMemory(&gImage, NATIVE_RESOLUTION, NULL);
	err = FxISO_Mem_SaveBufferToFile(filename, &gImage);

	return err;
}

int CreateModel(char* image, char* model)
{
	int err;
	float q;

	//Load tif fingerprint image into FingSlot
	err = FxISO_Mem_LoadBufferFromFile(image, &gImage);
	err = FxISO_Fing_LoadFromMemory(&gImage, &q);
	if (err)
		return err;

	//Create model in SMslot
	err = FxISO_SM_CreateFromFing();
	if (err)
		return err;

	//Save model to file
	err = FxISO_SM_SaveToMemory(&gModel, ISOFORMAT_STANDARD, TRUE);
	err = FxISO_Mem_SaveBufferToFile(model, &gModel);

	return err;
}

float TestMatch(char* first, char* second)
{
	int err;
	float sim;
	char model1[200], model2[200];


	sprintf_s(model1, 199, "%s", first);
	sprintf_s(model2, 199, "%s", second);

	err = FxISO_Mem_LoadBufferFromFile(model1, &gModel);
	err = FxISO_MM_LoadFromMemory(&gModel, ISOFORMAT_STANDARD);
	if (err)
		return 0.0;

	err = FxISO_Mem_LoadBufferFromFile(model2, &gModel);
	err = FxISO_SM_LoadFromMemory(&gModel, ISOFORMAT_STANDARD);
	if (err)
		return 0.0;

	err = FxISO_Eng_Matching(0.6f, &sim);
	if (err)
		return err;

	return sim;
}



#define SimilarityThreshold 0.6


int editModel(const char* cf) {
	int err;
	char path[256] = "";
	std::fstream users;
	std::string updatedLine;


	//find model
	try {
		std::string patternStr = R"(([^_]+)_([^_]+)_)";
		patternStr += std::string(cf) + R"(\.ist$)";
		std::regex filePattern(patternStr);

		for (const auto& entry : fs::directory_iterator("./")) {
			if (entry.is_regular_file()) {
				std::string fileName = entry.path().filename().string();
				if (std::regex_match(fileName, filePattern)) {
					std::string fullPath = entry.path().string();
					strcpy(path, fullPath.c_str());
				}
			}
		}
	}
	catch (const std::exception& e) {
		std::string errore = "Error: " + std::string(e.what());
		MessageBoxA(NULL, errore.c_str(), "Error", MB_OK);
		return -1;
	}

	if (strcmp(path, "") == 0) {
		MessageBoxA(NULL, "User not found", "Error", MB_OK);
		return -10;
	}

	// Edit model
	err = FxISO_MM_DeleteAll();
	if (err)
		return err;

	err = FxISO_Mem_LoadBufferFromFile(path, &gModel);
	if (err)
		return err;

	err = FxISO_MM_LoadFromMemory(&gModel, ISOFORMAT_STANDARD);
	if (err)
		return err;

	err = FxISO_MM_EnrollmentDlg(AUTOMATIC, NULL, -1, -1, 50, 10, 0.5, FINGERS_ALL_BITMASK);
	if (err)
		return err;

	err = FxISO_MM_SaveToMemory(&gModel, ISOFORMAT_STANDARD, TRUE);
	if (err)
		return err;

	err = FxISO_Mem_SaveBufferToFile(path, &gModel);
	if (err)
		return err;

	// Update users csv
	users.open("users.csv", std::ios::in | std::ios::out);
	if (!users) {
		return -1; 
	}

	std::string line;
	bool userFound = false;
	std::string updatedFingerInfo;
	int nFingerVect[10] = { 0 };
	int nUnknownFinger = 0;


	// Extract saved fingers info
	err = FxISO_MM_GetInfo(nFingerVect, &nUnknownFinger);
	if (err)
		return err;

	const char* fingerNames[10] = {
		"Right Thumb", "Right Forefinger", "Right Middle Finger",
		"Right Ring Finger", "Right Little Finger",
		"Left Thumb", "Left Forefinger", "Left Middle Finger",
		"Left Ring Finger", "Left Little Finger"
	};

	updatedFingerInfo = "";
	for (int i = 0; i < 10; i++) {
		if (nFingerVect[i] > 0) {
			updatedFingerInfo += fingerNames[i] + std::string(" x") + std::to_string(nFingerVect[i]) + ", ";
		}
	}
	if (nUnknownFinger > 0) {
		updatedFingerInfo += "Unknown x" + std::to_string(nUnknownFinger);
	}

	std::ostringstream oss;
	while (getline(users, line)) {
		if (line.find(cf) != std::string::npos) {
			userFound = true;
			size_t pos = line.find(",", line.find(",", line.find(",") + 1) + 1); 
			line = line.substr(0, pos + 2) + updatedFingerInfo;
			updatedLine = line;
		}
		else {
			oss << line << "\n";
		}
	}

	if (!userFound) {
		users.close();
		MessageBoxA(NULL, "User not found in CSV", "Error", MB_OK);
		return -10;
	}

	users.close();
	users.open("users.csv", std::ios::out | std::ios::trunc);
	if (!users) {
		return -1;
	}

	users << oss.str();  
	users << updatedLine << "\n";
	users.close();

	MessageBoxA(NULL, "User model modified", "Edit OK", MB_OK);
	return 0;
}



int Work(const char* nome, const char* cognome, const char* cf)
{
	float r0;
	int err, flag;
	char msg[200];
	BOOL repeatAgain;


	//Clear the MM-slot
	err = FxISO_MM_DeleteAll();
	if (err)
		return err;

	do
	{
		//Edit multiple model
		err = FxISO_MM_EnrollmentDlg(SUPERVISED, NULL, -1, -1, 50, 10, 0.5, FINGERS_ALL_BITMASK);
		if (err)
			return err;

		err = FxISO_MM_SaveToMemory(&gModel, ISOFORMAT_STANDARD, TRUE);
		if (err)
			return err;


		size_t buffer_size = strlen(nome) + strlen(cognome) + 1; // +1 per il terminatore nullo

		// Allocazione dinamica della memoria per 'model'
		char* model = (char*)malloc(buffer_size);
		if (model == NULL) {
			return -1; // Errore di allocazione della memoria
		}

		// Inizializza il buffer 'model' con la stringa 'nome'
		strcpy(model, nome);

		// Concatenazione delle stringhe
		strcat(model, "_");
		strcat(model, cognome);
		strcat(model, ".ist");

		err = FxISO_Mem_SaveBufferToFile(model, &gModel);
		if (err)
			return err;


		char file1[] = "Test.tif";
		char model1[] = "SingleM.ist";
		char model2[] = "MultiM.ist";

		err = CaptureFinger(file1);	//capture image Test.tif
		if (err)
			return err;

		err = CreateModel(file1, model1);	//Create model SingleM.ist from Test.tif
		if (err)
			return err;

		//DeleteFile(_T("Test.tif"));	// /usually images are not recorded for privacy protection

		//Perform the match
		r0 = TestMatch(model2, model1);



		sprintf_s(msg, 199, "Matching result between 2 models: %f\n", r0);

		if (r0 > SimilarityThreshold)
		{
			strcat_s(msg, 199, "\nUser identified");
			flag = MB_ICONINFORMATION | MB_OK;
		}
		else
		{
			strcat_s(msg, 199, "\nUser NOT identified\nDo you want to modify retry?");
			flag = MB_ICONWARNING | MB_RETRYCANCEL;
		}

		printf(msg);
		if (MessageBoxA(NULL, msg, "Result", flag | MB_OK) == IDRETRY)
			repeatAgain = TRUE;

		else
			repeatAgain = FALSE;

	} while (repeatAgain);

	return 0;
}


int work(const char* nome, const char* cognome, const char* cf)
{
	int err;

	err = FxISO_Init();
	if (err)
		return -1;

	err = FxISO_Mem_NewBuffer(&gImage);
	err = FxISO_Mem_NewBuffer(&gModel);

	err = Work(nome, cognome, cf);
	if (err)
		MessageBoxW(NULL, _T("Error Working with FxISO"), _T("Result"), MB_OK);


	err = FxISO_Mem_DeleteBuffer(&gImage);
	err = FxISO_Mem_DeleteBuffer(&gModel);

	err = FxISO_End();

	return 0;
}



int init()
{
	int err;

	err = FxISO_Init();
	if (err)
		return -1;

	err = FxISO_Mem_NewBuffer(&gImage);
	err = FxISO_Mem_NewBuffer(&gModel);

	return 0;
}

int end()
{
	int err;

	err = FxISO_Mem_DeleteBuffer(&gImage);
	err = FxISO_Mem_DeleteBuffer(&gModel);

	err = FxISO_End();

	return 0;
}

int createUserModel(const char* nome, const char* cognome, const char* cf) {
	fstream users;
	users.open("users.csv", ios::in);
	if (users) {
		string line;
		while (getline(users, line)) {
			if (line.find(cf) != string::npos) {
				users.close();
				return -1;
			}
		}
	}
	users.close();

	MessageBoxA(NULL, "Starting enrollment", "", MB_OK);

	int err = FxISO_MM_DeleteAll();
	if (err)
		return err;

	err = FxISO_MM_EnrollmentDlg(SUPERVISED, NULL, -1, -1, 50, 10, 0.5, FINGERS_ALL_BITMASK);
	if (err)
		return err;

	err = FxISO_MM_SaveToMemory(&gModel, ISOFORMAT_STANDARD, TRUE);
	if (err)
		return err;

	// Get model info
	int nFingerVect[10] = { 0 };
	int nUnknownFinger = 0;
	err = FxISO_MM_GetInfo(nFingerVect, &nUnknownFinger);
	if (err)
		return err;

	users.open("users.csv", ios::app);
	if (!users) {
		return -1;
	}

	users << nome << ", " << cognome << ", " << cf;

	const char* fingerNames[10] = {
		"Right Thumb", "Right Forefinger", "Right Middle Finger",
		"Right Ring Finger", "Right Little Finger",
		"Left Thumb", "Left Forefinger", "Left Middle Finger",
		"Left Ring Finger", "Left Little Finger"
	};

	for (int i = 0; i < 10; i++) {
		if (nFingerVect[i] > 0) {
			users << ", " << fingerNames[i] << " x" << nFingerVect[i];
		}
	}

	if (nUnknownFinger > 0) {
		users << ", Unknown x" << nUnknownFinger;
	}

	users << "\n";
	users.close();

	size_t buffer_size = strlen(nome) + strlen(cognome) + strlen(cf) + 10;
	char* model = (char*)malloc(buffer_size);
	if (model == NULL) {
		return -1;
	}
	strcpy(model, nome);
	strcat(model, "_");
	strcat(model, cognome);
	strcat(model, "_");
	strcat(model, cf);
	strcat(model, ".ist");

	err = FxISO_Mem_SaveBufferToFile(model, &gModel);
	free(model);

	if (err)
		return err;

	MessageBoxA(NULL, "User successfully enrolled", "", MB_OK);
	return 0;
}


int authenticate() {
	char acquiredFile[] = "acquiredFingerprint.tif";
	char acquiredModel[] = "acquiredModel.ist";
	int err;
	float r0;
	char msg[200];
	float q;

	string folderPath = "./";
	vector<string> istFiles;

	// Check if there is at least one user enrolled

	try {
		regex pattern(R"(([^_]+_[^_]+_[^_]+)\.ist$)");

		for (const auto& entry : fs::directory_iterator(folderPath)) {
			if (entry.is_regular_file() && entry.path().extension() == ".ist") {
				if (regex_match(entry.path().filename().string(), pattern)) {
					istFiles.push_back(entry.path().filename().string());
				}
			}
		}
	}
	catch (const fs::filesystem_error& e) {
		string errore = "Errore: " + string(e.what());
		MessageBoxA(NULL, errore.c_str(), "Errore", MB_OK);
	}

	if (istFiles.size() == 0) {
		MessageBoxA(NULL, "No file .ist found: no user enrolled", "No user enrolled error", MB_OK);
		return 404;
	}

	// Acquire fingerprint

	while (true) {

		BYTE* pImage;
		int imageSize;
		BYTE* pRawCopy;
		char buffer[64];
		

		int width, height = 0;

		err = FxISO_Fing_AcquireAutomatic(NULL, -1, -1, &q, 50, 20, 1.5);
		if (err) return err;

		err = FxISO_Fing_SaveToMemory(&gImage, NATIVE_RESOLUTION, NULL);
		if (err) return err;

		// Check fingerprint quality and acquisition warnings

		pImage = FxISO_Mem_GetImageRow(&gImage, 0);
		imageSize = gImage.imageWidth * gImage.imageHeight;
		width = gImage.imageWidth;
		height = gImage.imageHeight;

		pRawCopy = new BYTE[imageSize];
		memcpy(pRawCopy, pImage, imageSize);

		int resolution = 500;
		int qualityWarning, qualityNIST, quality100;

		// Evaluate fingerprint quality
		err = FxISO_ImageTool_EvaluateNISTQuality(pRawCopy, width, height, resolution, &qualityNIST);
		if (err) return err;

		err = FxISO_ImageTool_NFIQ_Evaluate(pRawCopy, width, height, &quality100);
		if (err) return err;

		char quality[14];
		switch (qualityNIST) {
			case 1:
				strcpy(quality, " (Excellent)");
				break;
			case 2:
				strcpy(quality, " (Very good)");
				break;
			case 3:
				strcpy(quality, " (Good)");
				break;
			case 4:
				strcpy(quality, " (Fair)");
				break;
			case 5:
				strcpy(quality, " (Poor)");
				break;
		}

		std::string acquisitionMsg = "Info on acquired fingerprint: \n";
		acquisitionMsg += "Quality (NFIQ): " + std::to_string(quality100) + "/100\n";
		acquisitionMsg += "Quality (NIST): " + std::to_string(qualityNIST) +quality+"\n";
		acquisitionMsg += "Resolution: " + std::to_string(resolution) + " dpi\n";
		MessageBoxA(NULL, acquisitionMsg.c_str(), "Acquisition Info", MB_OK);

		// Evaluate warnings
		err = FxISO_ImageTool_EvaluateWarning(q, pRawCopy, width, height, resolution, &qualityWarning);

		if (err) {
			MessageBoxA(NULL, "Error evaluating the fingerprint warning!", "Error", MB_ICONERROR | MB_OK);
			return err;
		}

		if (qualityWarning != AWRN_OK) {
			const char* warningMessages[] = {
				"Image Quality is Ok",
				"Fingerprint not found. Please place your finger properly.",
				"Too many fingerprints detected. Use only one finger.",
				"Low contrast detected. Apply more pressure or use a moisturizer.",
				"Fingerprint is too dark. Apply less pressure or dry your finger.",
				"Low-quality fingerprint. Try using a moisturizer.",
				"Dirty prism detected. Please clean the platen surface.",
				"Fingerprint is too close to the left margin.",
				"Fingerprint is too close to the right margin.",
				"Fingerprint is too close to the top margin.",
				"Fingerprint is too close to the bottom margin.",
				"Excessive rotation detected. Adjust finger placement.",
				"Motion detected. Please keep your finger still."
			};

			std::string warningMsg = "WARNING: ";
			warningMsg += warningMessages[qualityWarning];
			warningMsg += "\n\nDo you want to use this fingerprint?";

			int userChoice = MessageBoxA(NULL, warningMsg.c_str(), "Warning", MB_ICONWARNING | MB_YESNO);
			if (userChoice == IDNO) continue;
		}
		break;
	}


	// PAD score

	int pad;
	err = FxISO_Fing_GetPAD(&pad);
	if (err) return err;

	std::string Msg = "PAD Score: ";
	std::stringstream ss;
	ss << Msg << pad;

	if (pad > 50) {
		ss << "\nInvalid fingerprint detected (high PAD score)";
		MessageBoxA(NULL, ss.str().c_str(), "PAD Score", MB_ICONERROR | MB_OK);
		return -50;
	}
	else {
		ss << "\nValid fingerprint detected (low PAD score). Please continue";
		MessageBoxA(NULL, ss.str().c_str(), "PAD Score", MB_OK);
	}

	// Save acquired fingerprint to file
	err = FxISO_Mem_SaveBufferToFile(acquiredFile, &gImage); //TOGLIERE PER NON SALVARE L'IMPRONTA IN LOCALE
	if (err) return err;

	err = CreateModel(acquiredFile, acquiredModel);
	if (err) return err;

	

	
	// Match fingerprint with enrolled users

	for (const auto& fileName : istFiles) {
		char model1[200], model2[200];
		sprintf_s(model1, 199, "%s", fileName.c_str());
		sprintf_s(model2, 199, "%s", acquiredModel);

		r0 = TestMatch(model1, model2);
		sprintf_s(msg, 199, "Matching result between 2 models: %f\n", r0);

		if (r0 > SimilarityThreshold) {
			std::string baseName = fileName.substr(0, fileName.find_last_of('.'));
			std::string userName = baseName.substr(0, baseName.find('_'));
			std::string userSurname = baseName.substr(baseName.find('_') + 1, baseName.find_last_of('_') - baseName.find('_') - 1);
			std::string cf = baseName.substr(baseName.find_last_of('_') + 1);

            std::ostringstream oss;
            oss << "User identified: welcome back " << userName << " " << userSurname << " (" << cf << ")\nMatching score: " << r0;
            std::string message = oss.str();
			MessageBoxA(NULL, message.c_str(), "Result", MB_ICONINFORMATION | MB_OK);

			DeleteFileA(acquiredModel);
			return 0;
		}
	}

	sprintf_s(msg, 199, "\nUser NOT identified!");
	MessageBoxA(NULL, msg, "Result", MB_ICONERROR | MB_OK);
	DeleteFileA(acquiredModel);
	return -1;
}


int extractMinutiaeTXT() {
	char acquiredFile[] = "acquiredFingerprint.tif";
	char acquiredModel[] = "acquiredModel.ist";
	int err;

	err = CreateModel(acquiredFile, acquiredModel);
	if (err) return err;

	// Minutiae extraction
	int nMinutiae = 0;
	err = FxISO_SM_GetNumMinutiae(&nMinutiae);
	if (err || nMinutiae == 0) {
		MessageBoxA(NULL, "No minutiae detected in the fingerprint.", "Minutiae Info", MB_ICONERROR | MB_OK);
		return -100;
	}
	else {
		std::ofstream outFile("minutiae_info.txt");
		if (!outFile) {
			MessageBoxA(NULL, "Failed to create minutiae info file.", "Error", MB_ICONERROR | MB_OK);
			return -1;
		}

		outFile << "Number of minutiae: " << nMinutiae << "\n\n";

		for (int i = 0; i < nMinutiae; ++i) {
			int x, y, angle, quality;
			err = FxISO_SM_GetMinutia(i, &x, &y, &angle, &quality);
			if (err) continue; 

			outFile << "Minutia " << (i + 1) << ":\n";
			outFile << "  Position: (" << x << ", " << y << ")\n";
			outFile << "  Angle: " << angle << "°\n";
			outFile << "  Quality: " << quality << "/100\n\n";
		}

		outFile.close();

		MessageBoxA(NULL, "Minutiae details saved to 'minutiae_info.txt'.", "Minutiae Info", MB_OK);
		return 0;
	}
}


// Convert SDK error code to text
const char* convertErrorToText(int err) {
	switch (err) {
		case -50:
			return "Invalid fingerprint detected (high PAD score)";
		case 1:
			return "Insufficient memory";
		case 3:
			return "Timeout";
		case 4:
			return "File not existing";
		case 5:
			return "Invalid fingerprint data";
		case 6:
			return "Too low quality";
		case 7:
			return "Invalid model file";
		case 8:
			return "Model not created";
		case 9:
			return "Cannot write to disk";
		case 10:
			return "Cannot update model";
		case 11:
			return "Invalid mode";
		case 12:
			return "Fingerprint not available";
		case 13:
			return "Cannot process fingerprint";
		case 14:
			return "Low number of minutiae";
		case 15:
			return "Model not available";
		case 16:
			return "Operation cancelled";
		case 17:
			return "Invalid size";
		case 18:
			return "Invalid parameter";
		case 20:
			return "Init not called";
		case 21:
			return "Incomplete DLL set";
		case 100:
			return "Acquisition error";
		case 110:
			return "DLL Not found";
		case 111:
			return "Corrupted DLL";
		case 112:
			return "Initialization failure";
		case 113:
			return "Setting failure";
		case 114:
			return "Grabbing failure";
		case 115:
			return "UnInitialization Error";
		case 116:
			return "Show error";
		case 117:
			return "Timer error";
		case 118:
			return "Invalid parameters";
		case 120:
			return "No Online Capability";
		case 121:
			return "Invalid Fingerprint Image";
		case 122:
			return "Invalid Latent";
		case 123:
			return "Invalid Liveness";
		case 124:
			return "Feature Not Available";
		case 125:
			return "Communication error";
		case 126:
			return "File Permission Error";
		case 127:
			return "Filesystem Error";
		}
}