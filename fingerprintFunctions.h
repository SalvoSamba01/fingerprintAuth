
#pragma once
// TestFxISO.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include <string.h>
#include "fxISOdll.h"
#include "fxISOenrdlg.h" 
#include <tchar.h>
#include <windows.h>
#include <string>

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


	sprintf_s(model1, 199, "%s.ist", first);
	sprintf_s(model2, 199, "%s.ist", second);

	//Load Multiple model in MMslot
	err = FxISO_Mem_LoadBufferFromFile(model1, &gModel);
	err = FxISO_MM_LoadFromMemory(&gModel, ISOFORMAT_STANDARD);
	if (err)
		return 0.0;

	//Load model in SMslot
	err = FxISO_Mem_LoadBufferFromFile(model2, &gModel);
	err = FxISO_SM_LoadFromMemory(&gModel, ISOFORMAT_STANDARD);
	if (err)
		return 0.0;

	//Match
	err = FxISO_Eng_Matching(0.6f, &sim);
	if (err)
		return 0.0;

	return sim;
}

#define SimilarityThreshold 0.5

int Work()
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
		char model[] = "MultiM.ist";
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

		DeleteFile(_T("Test.tif"));	//usually images are not recorded for privacy protection

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

int work()
{
	int err;


	err = FxISO_Init();
	if (err)
		return -1;

	err = FxISO_Mem_NewBuffer(&gImage);
	err = FxISO_Mem_NewBuffer(&gModel);

	err = Work();
	if (err)
		MessageBoxW(NULL, _T("Error Working with FxISO"), _T("Result"), MB_OK);


	err = FxISO_Mem_DeleteBuffer(&gImage);
	err = FxISO_Mem_DeleteBuffer(&gModel);

	err = FxISO_End();

	return 0;
}

