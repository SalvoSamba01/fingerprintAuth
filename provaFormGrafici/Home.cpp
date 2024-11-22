#pragma once
#include "Home.h"
#include "fingerprintFunctions.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]

int main()
{
	int err;
	err = init();
	if (err)
		return err;

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	provaFormGrafici::Home form;
	Application::Run(% form);

	err = end();
}


