#pragma once
#include "fingerprintFunctions.h"
#include <string.h>
#include <filesystem>
#include <fstream>
#include <sstream>
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
	private: System::Windows::Forms::PictureBox^ fingerImage;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;




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
			this->fingerImage = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fingerImage))->BeginInit();
			this->SuspendLayout();
			// 
			// loginButton
			// 
			this->loginButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->loginButton->Location = System::Drawing::Point(338, 77);
			this->loginButton->Margin = System::Windows::Forms::Padding(2);
			this->loginButton->Name = L"loginButton";
			this->loginButton->Size = System::Drawing::Size(95, 33);
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
			this->user->Location = System::Drawing::Point(201, 114);
			this->user->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->user->Name = L"user";
			this->user->Size = System::Drawing::Size(0, 13);
			this->user->TabIndex = 1;
			this->user->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Lucida Sans Typewriter", 19.8F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(333, 7);
			this->label4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(94, 31);
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
			this->message->Location = System::Drawing::Point(313, 46);
			this->message->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->message->Name = L"message";
			this->message->Size = System::Drawing::Size(147, 20);
			this->message->TabIndex = 11;
			this->message->Text = L"Click button to login";
			this->message->Click += gcnew System::EventHandler(this, &login::message_Click);
			// 
			// fingerImage
			// 
			this->fingerImage->BackColor = System::Drawing::Color::Transparent;
			this->fingerImage->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->fingerImage->Location = System::Drawing::Point(74, 129);
			this->fingerImage->Margin = System::Windows::Forms::Padding(2);
			this->fingerImage->Name = L"fingerImage";
			this->fingerImage->Size = System::Drawing::Size(500, 500);
			this->fingerImage->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->fingerImage->TabIndex = 12;
			this->fingerImage->TabStop = false;
			this->fingerImage->Visible = false;
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(628, 175);
			this->button1->Margin = System::Windows::Forms::Padding(2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(95, 75);
			this->button1->TabIndex = 13;
			this->button1->Text = L"Extract minutiae (TXT)";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Visible = false;
			this->button1->Click += gcnew System::EventHandler(this, &login::button1_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(628, 291);
			this->button2->Margin = System::Windows::Forms::Padding(2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(95, 75);
			this->button2->TabIndex = 14;
			this->button2->Text = L"Extract minutiae (Draw)";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Visible = false;
			this->button2->Click += gcnew System::EventHandler(this, &login::button2_Click);
			// 
			// login
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(760, 645);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->fingerImage);
			this->Controls->Add(this->message);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->user);
			this->Controls->Add(this->loginButton);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"login";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Fingerprint SDK Demo - Login";
			this->Load += gcnew System::EventHandler(this, &login::login_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fingerImage))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
    private: System::Void loginButton_Click(System::Object^ sender, System::EventArgs^ e) {
						
						int err = authenticate();
						fingerImage->Visible = true;
						fingerImage->ImageLocation = "./acquiredFingerprint.tif";
						button1->Visible = true;
						button2->Visible = true;
						if (err == -1) {
							message->Text = "User not identified";
							return;
						}
						else if (err == 0) {
							message->Text = "Login succesfull";
							return;
						}

						else {
							const char* errorText = convertErrorToText(err);
							message->Text = gcnew System::String(errorText);
							return;
						}
					}
	private: System::Void label4_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void message_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void login_Load(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	int err = extractMinutiaeTXT();
	if (err == 0) {
		message->Text = "Minutiae extracted succesfully";
	}
	else {
		message->Text = "Error in minutiae extraction";
	}
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	System::Drawing::Pen^ p;
	Graphics^ g = fingerImage->CreateGraphics();

	int err = extractMinutiaeTXT();
	if (err == 0) {
		message->Text = "Minutiae extracted succesfully";
	}
	else {
		message->Text = "Error in minutiae extraction";
	}

	std::ifstream file("./minutiae_info.txt");
	if (!file.is_open()) {
		message->Text = "Error in minutiae extraction";
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		if (line.find("Position:") != std::string::npos) {
			size_t start = line.find("(") + 1;
			size_t end = line.find(")");
			std::string coordinates = line.substr(start, end - start);

			std::istringstream coordStream(coordinates);
			int x, y;
			char comma; 
			coordStream >> x >> comma >> y;
			std::getline(file, line); 
			size_t qualityPos = line.find("Quality:") + 9;
			int quality = std::stoi(line.substr(qualityPos, line.find("/") - qualityPos));

			if (quality < 70) {
				p = gcnew System::Drawing::Pen(Color::Red, 2);
			}
			else if (quality <= 85) {
				p = gcnew System::Drawing::Pen(Color::Yellow, 2);
			}
			else {
				p = gcnew System::Drawing::Pen(Color::Green, 2);
			}

			g->DrawEllipse(p, x-4, y-4, 8, 8);
		}
	}

	file.close();
}
};
}
