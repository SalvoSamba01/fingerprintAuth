#pragma once
#include "fingerprintFunctions.h"
#include "about.h"
#include <msclr/marshal_cppstd.h>
#include <string.h>

namespace provaFormGrafici {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Riepilogo per signup
	/// </summary>
	public ref class signup : public System::Windows::Forms::Form
	{
	public:
		signup(void)
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
		~signup()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ acquisition;
	private: System::Windows::Forms::TextBox^ cf;
	private: System::Windows::Forms::TextBox^ surname;
	private: System::Windows::Forms::TextBox^ name;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ error;
	private: System::Windows::Forms::Label^ label4;
	protected:

	protected:

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(signup::typeid));
			this->acquisition = (gcnew System::Windows::Forms::Button());
			this->cf = (gcnew System::Windows::Forms::TextBox());
			this->surname = (gcnew System::Windows::Forms::TextBox());
			this->name = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->error = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// acquisition
			// 
			this->acquisition->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->acquisition->Location = System::Drawing::Point(257, 300);
			this->acquisition->Name = L"acquisition";
			this->acquisition->Size = System::Drawing::Size(96, 42);
			this->acquisition->TabIndex = 0;
			this->acquisition->Text = L"Enroll";
			this->acquisition->UseVisualStyleBackColor = true;
			this->acquisition->Click += gcnew System::EventHandler(this, &signup::acquisition_Click);
			// 
			// cf
			// 
			this->cf->Location = System::Drawing::Point(257, 218);
			this->cf->Name = L"cf";
			this->cf->Size = System::Drawing::Size(211, 22);
			this->cf->TabIndex = 1;
			// 
			// surname
			// 
			this->surname->Location = System::Drawing::Point(257, 164);
			this->surname->Name = L"surname";
			this->surname->Size = System::Drawing::Size(211, 22);
			this->surname->TabIndex = 2;
			// 
			// name
			// 
			this->name->Location = System::Drawing::Point(257, 104);
			this->name->Name = L"name";
			this->name->Size = System::Drawing::Size(211, 22);
			this->name->TabIndex = 3;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(129, 104);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(64, 25);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Name";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(129, 161);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(92, 25);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Surname";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(129, 214);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(70, 25);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Tax ID";
			// 
			// error
			// 
			this->error->AutoSize = true;
			this->error->BackColor = System::Drawing::Color::Transparent;
			this->error->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->error->ForeColor = System::Drawing::Color::Red;
			this->error->Location = System::Drawing::Point(216, 253);
			this->error->Name = L"error";
			this->error->Size = System::Drawing::Size(0, 20);
			this->error->TabIndex = 7;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Lucida Sans Typewriter", 19.8F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic))));
			this->label4->Location = System::Drawing::Point(224, 28);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(157, 38);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Sign up";
			// 
			// signup
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(608, 386);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->error);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->name);
			this->Controls->Add(this->surname);
			this->Controls->Add(this->cf);
			this->Controls->Add(this->acquisition);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"signup";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Fingerprint SDK Demo - Sign Up";
			this->Load += gcnew System::EventHandler(this, &signup::signup_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void acquisition_Click(System::Object^ sender, System::EventArgs^ e) {
		if (name->Text == "" || surname->Text == "" || cf->Text == "") {
			error->Text = "Fill out all the fields";
			return;
		}

		int err;
		System::String^ vname = name->Text; // dove nameTextBox è il tuo controllo TextBox
		System::String^ vsurname = surname->Text; // e così via per surname
		System::String^ vcf = cf->Text;

		// Conversione di System::String^ in std::string
		std::string nameStdString = msclr::interop::marshal_as<std::string>(vname);
		std::string surnameStdString = msclr::interop::marshal_as<std::string>(vsurname);
		std::string cfStdString = msclr::interop::marshal_as<std::string>(vcf);

		// Ora puoi ottenere un char*
		const char* nameChar = nameStdString.c_str();
		const char* surnameChar = surnameStdString.c_str();
		const char* cfChar = cfStdString.c_str();

		name->Text = "";
		surname->Text = "";
		cf->Text = "";

		error->Text = "";

		err = createUserModel(nameChar, surnameChar, cfChar);
		if (err == -1) {
			error->Text = "User already enrolled";
			return;
		}

		else if (err == 0)
			this->Close();

		else {
			const char* errorText = convertErrorToText(err);
			error->Text = gcnew System::String(errorText);
			return;
		}



	}
private: System::Void signup_Load(System::Object^ sender, System::EventArgs^ e) {
}
};
}
