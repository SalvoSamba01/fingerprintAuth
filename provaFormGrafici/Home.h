#pragma once
#include "signup.h"
#include "login.h"
#include "edit.h"

namespace provaFormGrafici {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Riepilogo per Home
	/// </summary>
	public ref class Home : public System::Windows::Forms::Form
	{
	public:
		Home(void)
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
		~Home()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ registerButton;
	protected:
	private: System::Windows::Forms::Button^ loginButton;
	private: System::Windows::Forms::Button^ aboutButton;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ editButton;



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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Home::typeid));
			this->registerButton = (gcnew System::Windows::Forms::Button());
			this->loginButton = (gcnew System::Windows::Forms::Button());
			this->aboutButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->editButton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// registerButton
			// 
			this->registerButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->registerButton->Location = System::Drawing::Point(209, 339);
			this->registerButton->Name = L"registerButton";
			this->registerButton->Size = System::Drawing::Size(136, 50);
			this->registerButton->TabIndex = 0;
			this->registerButton->Text = L"Sign Up";
			this->registerButton->UseVisualStyleBackColor = true;
			this->registerButton->Click += gcnew System::EventHandler(this, &Home::registerButton_Click);
			// 
			// loginButton
			// 
			this->loginButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->loginButton->Location = System::Drawing::Point(508, 339);
			this->loginButton->Name = L"loginButton";
			this->loginButton->Size = System::Drawing::Size(141, 53);
			this->loginButton->TabIndex = 1;
			this->loginButton->Text = L"Login";
			this->loginButton->UseVisualStyleBackColor = true;
			this->loginButton->Click += gcnew System::EventHandler(this, &Home::loginButton_Click);
			// 
			// aboutButton
			// 
			this->aboutButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->aboutButton->Location = System::Drawing::Point(207, 438);
			this->aboutButton->Name = L"aboutButton";
			this->aboutButton->Size = System::Drawing::Size(138, 53);
			this->aboutButton->TabIndex = 2;
			this->aboutButton->Text = L"About";
			this->aboutButton->UseVisualStyleBackColor = true;
			this->aboutButton->Click += gcnew System::EventHandler(this, &Home::aboutButton_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Lucida Sans Typewriter", 19.8F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(160, 46);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(537, 38);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Fingerprint Detection Demo";
			this->label1->Click += gcnew System::EventHandler(this, &Home::label1_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(329, 98);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(195, 179);
			this->pictureBox1->TabIndex = 4;
			this->pictureBox1->TabStop = false;
			// 
			// editButton
			// 
			this->editButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->editButton->Location = System::Drawing::Point(511, 438);
			this->editButton->Name = L"editButton";
			this->editButton->Size = System::Drawing::Size(138, 53);
			this->editButton->TabIndex = 5;
			this->editButton->Text = L"Edit";
			this->editButton->UseVisualStyleBackColor = true;
			this->editButton->Click += gcnew System::EventHandler(this, &Home::editButton_Click);
			// 
			// Home
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(840, 573);
			this->Controls->Add(this->editButton);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->aboutButton);
			this->Controls->Add(this->loginButton);
			this->Controls->Add(this->registerButton);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Home";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Fingerprint SDK Demo - Home";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void registerButton_Click(System::Object^ sender, System::EventArgs^ e) {
		signup^ registerForm = gcnew signup();
		registerForm->ShowDialog();
	}
	private: System::Void aboutButton_Click(System::Object^ sender, System::EventArgs^ e) {
		about^ aboutForm = gcnew about();
		aboutForm->ShowDialog();
	}
	private: System::Void loginButton_Click(System::Object^ sender, System::EventArgs^ e) {
		login^ loginForm = gcnew login();
		loginForm->ShowDialog();
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void editButton_Click(System::Object^ sender, System::EventArgs^ e) {
		edit^ editForm = gcnew edit();
		editForm->ShowDialog();
	}
};
}
