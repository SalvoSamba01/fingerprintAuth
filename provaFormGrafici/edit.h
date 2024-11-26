#pragma once
#include "fingerprintFunctions.h"
#include <msclr/marshal_cppstd.h>


namespace provaFormGrafici {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Riepilogo per edit
	/// </summary>
	public ref class edit : public System::Windows::Forms::Form
	{
	public:
		edit(void)
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
		~edit()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

	private: System::Windows::Forms::TextBox^ cf;
	private: System::Windows::Forms::Button^ editButton;
	private: System::Windows::Forms::Label^ error;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label1;


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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(edit::typeid));
			this->cf = (gcnew System::Windows::Forms::TextBox());
			this->editButton = (gcnew System::Windows::Forms::Button());
			this->error = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// cf
			// 
			this->cf->Location = System::Drawing::Point(257, 126);
			this->cf->Name = L"cf";
			this->cf->Size = System::Drawing::Size(100, 22);
			this->cf->TabIndex = 2;
			// 
			// editButton
			// 
			this->editButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->editButton->Location = System::Drawing::Point(203, 247);
			this->editButton->Name = L"editButton";
			this->editButton->Size = System::Drawing::Size(128, 53);
			this->editButton->TabIndex = 3;
			this->editButton->Text = L"Edit";
			this->editButton->UseVisualStyleBackColor = true;
			this->editButton->Click += gcnew System::EventHandler(this, &edit::editButton_Click);
			// 
			// error
			// 
			this->error->AutoSize = true;
			this->error->BackColor = System::Drawing::Color::Transparent;
			this->error->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->error->ForeColor = System::Drawing::Color::Red;
			this->error->Location = System::Drawing::Point(180, 182);
			this->error->Name = L"error";
			this->error->Size = System::Drawing::Size(0, 29);
			this->error->TabIndex = 4;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Lucida Sans Typewriter", 19.8F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic))));
			this->label4->Location = System::Drawing::Point(166, 44);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(197, 38);
			this->label4->TabIndex = 9;
			this->label4->Text = L"Edit user";
			this->label4->Click += gcnew System::EventHandler(this, &edit::label4_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(149, 122);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(70, 25);
			this->label1->TabIndex = 10;
			this->label1->Text = L"Tax ID";
			// 
			// edit
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(550, 365);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->error);
			this->Controls->Add(this->editButton);
			this->Controls->Add(this->cf);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"edit";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Fingerprint SDK Demo - Edit user";
			this->Load += gcnew System::EventHandler(this, &edit::edit_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void editButton_Click(System::Object^ sender, System::EventArgs^ e) {

		int err;
		if (cf->Text == "") {
			error->Text = "Insert Tax ID of the user you want to modify";
			return;
		}

		System::String^ vcf = cf->Text;

		std::string cfStdString = msclr::interop::marshal_as<std::string>(vcf);

		const char* cfChar = cfStdString.c_str();

		cf->Text = "";

		error->Text = "";

		err = editModel(cfChar);
		if(err==-1) {
			error->Text = "Error in searching file";
			return;
		}
		else if (err == -10) {
			error->Text = "User not found";
			return;
		}
		else if (err == 0) {
			error->Text = "Model updated";
			return;
		}

		else {
			const char* errorText = convertErrorToText(err);
			error->Text = gcnew System::String(errorText);
			return;
		}
		
		this->Close();

	}
	private: System::Void edit_Load(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void label4_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
