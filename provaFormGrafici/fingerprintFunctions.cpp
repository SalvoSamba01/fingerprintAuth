
#include <string.h>
#include "fxISOdll.h"
#include "fxISOenrdlg.h" 
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

	//message box col nome dei due modelli in confronto
	/*
	std::string message = "Matching tra: " + string(model1) + " e " + string(model2);
	MessageBoxA(NULL, message.c_str(), "Matching", MB_OK);
	*/

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
		return 0.0;

	return sim;
}



#define SimilarityThreshold 0.6


int editModel(const char* cf) {
	int err;

	char path[256] = "";
	

	try {
		// Definizione della regex per il nome del file
		std::string patternStr = R"(([^_]+)_([^_]+)_)";
		patternStr += std::string(cf) + R"(\.ist$)";
		std::regex filePattern(patternStr);

		// Scansiona la directory corrente
		for (const auto& entry : fs::directory_iterator("./")) {
			if (entry.is_regular_file()) {
				std::string fileName = entry.path().filename().string();
				if (std::regex_match(fileName, filePattern)) {
					std::string fullPath = entry.path().string();
					// Copia il percorso nel buffer `path`
					strcpy(path, fullPath.c_str());
				}
			}
		}
	}
	catch (const std::exception& e) {
		string errore = "Error: " + string(e.what());
		MessageBoxA(NULL, errore.c_str(), "Error", MB_OK);
		return -1;
	}

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


	size_t buffer_size = strlen(nome) + strlen(cognome) + 1; // +1 per il terminatore nullo

	// Allocazione dinamica della memoria per 'model'
	char* model = (char*)malloc(buffer_size);
	if (model == NULL) {
		return -1; // Errore di allocazione della memoria
	}

	// file contenente i dati degli utenti

	



	users.open("users.csv", ios::app);

	users << nome << ", " << cognome << ", " << cf << "\n";

	users.close();

	// Inizializza il buffer 'model' con la stringa 'nome'
	strcpy(model, nome);

	// Concatenazione delle stringhe
	strcat(model, "_");
	strcat(model, cognome);
	strcat(model, "_");
	strcat(model, cf);
	strcat(model, ".ist");

	err = FxISO_Mem_SaveBufferToFile(model, &gModel);
	if (err)
		return err;
	else {
		MessageBoxA(NULL, "User succesfully enrolled", "", MB_OK);
		return 0;
	}
}

int authenticate() {
	char acquiredFile[] = "acquiredFingerprint.tif";
	char acquiredModel[] = "acquiredModel.ist";
	int err;
	float r0;
	char msg[200];

	string folderPath = "./"; // Sostituisci con il percorso della tua cartella
	vector<string> istFiles;

	try {
		// Regex per controllare il formato [qualunquecosa]_[qualunquecosa]_[qualunquecosa]
		regex pattern(R"(([^_]+_[^_]+_[^_]+)\.ist$)");

		for (const auto& entry : fs::directory_iterator(folderPath)) {
			if (entry.is_regular_file() && entry.path().extension() == ".ist") {
				// Verifica se il nome del file corrisponde al pattern
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
		// MessageBox che dice che non ci sono file .ist
		MessageBoxA(NULL, "No file .ist found: no user enrolled", "No user enrolled error", MB_OK);
		return 404;
	}

	// modelli .ist di utenti registrati
	/*
	for (const auto& fileName : istFiles) {
		std::string message = "File trovato: " + fileName;
		// Mostra il MessageBox con il nome del file
		MessageBoxA(NULL, message.c_str(), "File", MB_OK);
	}
	*/
		
		
	err = CaptureFinger(acquiredFile);	//capture user fingerprint
	if (err)
		return err;

	err = CreateModel(acquiredFile, acquiredModel);	//crea modello che contiene l'impronta
	if (err)
		return err;

	//DeleteFile(_T("Test.tif"));	//usually images are not recorded for privacy protection

	//Perform the match with every ist found
	for (const auto& fileName : istFiles) {

		//message box che stampa il nome del modello con cui sto tentando il matching in questa iterazione
		/*
		std::string message = "Matching con: " + fileName;
		MessageBoxA(NULL, message.c_str(), "Matching", MB_OK);
		*/

		char model1[200], model2[200];
		sprintf_s(model1, 199, "%s", fileName.c_str());
		sprintf_s(model2, 199, "%s", acquiredModel);

		//Perform the match
		r0 = TestMatch(model1, model2);
		sprintf_s(msg, 199, "Matching result between 2 models: %f\n", r0);

		if (r0 > SimilarityThreshold)
		{

			std::string baseName = fileName.substr(0, fileName.find_last_of('.')); // Remove file extension
			std::string userName = baseName.substr(0, baseName.find('_')); // Get the first part (name)
			std::string userSurname = baseName.substr(baseName.find('_') + 1, baseName.find_last_of('_') - baseName.find('_') - 1); // Get the surname
			std::string cf = baseName.substr(baseName.find_last_of('_') + 1); // Get the ID

			// Modify the message to include user information
			std::string message = "User identified: welcome back " + userName + " " + userSurname + " (" + cf + ")";
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