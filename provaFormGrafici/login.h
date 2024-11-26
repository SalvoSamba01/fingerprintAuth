#pragma once
#include "fingerprintFunctions.h"
#include <string.h>
using namespace std;

#define INIZIALIZATION_ERROR 112
#define AUTHENTICATION_ERROR 113

namespace provaFormGrafici {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Riepilogo per login
	/// </summary>
	public ref class login : public System::Windows::Forms::Form
	{
	public:
		login(void)
		{
			InitializeComponent();
			//
			//TODO: aggiungere qui il codice del costruttore.
			//
		}

	protected:
		/// <summary>
		/// Pulire le risorse in uso.
		/// </summary>
		~login()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ loginButton;
	protected:
	private: System::Windows::Forms::Label^ user;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ message;



	private:
		/// <summary>
		/// Variabile di progettazione necessaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metodo necessario per il supporto della finestra di progettazione. Non modificare
		/// il contenuto del metodo con l'editor di codice.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(login::typeid));
			this->loginButton = (gcnew System::Windows::Forms::Button());
			this->user = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->message = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// loginButton
			// 
			this->loginButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->loginButton->Location = System::Drawing::Point(211, 168);
			this->loginButton->Name = L"loginButton";
			this->loginButton->Size = System::Drawing::Size(127, 41);
			this->loginButton->TabIndex = 0;
			this->loginButton->Text = L"Login";
			this->loginButton->UseVisualStyleBackColor = true;
			this->loginButton->Click += gcnew System::EventHandler(this, &login::loginButton_Click);
			// 
			// user
			// 
			this->user->AutoEllipsis = true;
			this->user->AutoSize = true;
			this->user->BackColor = System::Drawing::Color::Transparent;
			this->user->Enabled = false;
			this->user->Location = System::Drawing::Point(268, 140);
			this->user->Name = L"user";
			this->user->Size = System::Drawing::Size(0, 16);
			this->user->TabIndex = 1;
			this->user->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Lucida Sans Typewriter", 19.8F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(221, 29);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(117, 38);
			this->label4->TabIndex = 10;
			this->label4->Text = L"Login";
			this->label4->Click += gcnew System::EventHandler(this, &login::label4_Click);
			// 
			// message
			// 
			this->message->AutoSize = true;
			this->message->BackColor = System::Drawing::Color::Transparent;
			this->message->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->message->Location = System::Drawing::Point(186, 92);
			this->message->Name = L"message";
			this->message->Size = System::Drawing::Size(181, 25);
			this->message->TabIndex = 11;
			this->message->Text = L"Click button to login";
			this->message->Click += gcnew System::EventHandler(this, &login::message_Click);
			// 
			// login
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(553, 248);
			this->Controls->Add(this->message);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->user);
			this->Controls->Add(this->loginButton);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"login";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Fingerprint SDK Demo - Login";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
    private: System::Void loginButton_Click(System::Object^ sender, System::EventArgs^ e) {
						
						int err = authenticate();

						char errorType[100];
						switch(err){
							case -1:
								strcpy(errorType, "User not identified");
								break;
							case 0:
								strcpy(errorType, "Login Successful");
								break;
							case 16:
								strcpy(errorType, "Operation aborted");
								break;
							case 112:
								strcpy(errorType, "Initialization Failure");
								break;
							case 113:
								strcpy(errorType, "Setting failure");
								break;
							case 114:
								strcpy(errorType, "Grabbing failure");
								break;
							case 115:
								strcpy(errorType, "UnInizialization Error");
								break;
							case 116:
								strcpy(errorType, "Show error");
								break;
							case 117:
								strcpy(errorType, "Timer error");
								break;
							case 118:
								strcpy(errorType, "Invalid parameters");
								break;
							case 120:
								strcpy(errorType, "No Online Capability");
								break;
							case 121:
								strcpy(errorType, "Invalid Fingerprint Image");
								break;
							case 122:
								strcpy(errorType, "Invalid Latent");
								break;
							case 123:
								strcpy(errorType, "Invalid Liveness");
								break;
							case 124:
								strcpy(errorType, "Feature Not Available");
								break;
							case 125:
								strcpy(errorType, "Communication error");
								break;
							case 126:
								strcpy(errorType, "File Permission Error");
								break;
							case 127:
								strcpy(errorType, "Filesystem Error");
								break;
							case 404:
								strcpy(errorType, "No user enrolled");
								break;
							default:
								strcpy(errorType, "Unknown error");
								break;
							}
							if (err == 0 || err == -1 || err==16)
								this->message->Text = gcnew String(errorType);
							else if (err == 404)
								this->message->Text = "Error: " + gcnew String(errorType);
							else
								this->message->Text = "Error " + err + ": " + gcnew String(errorType);
						
					}
	private: System::Void label4_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void message_Click(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
