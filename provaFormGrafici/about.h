#pragma once

namespace provaFormGrafici {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Riepilogo per about
	/// </summary>
	public ref class about : public System::Windows::Forms::Form
	{
	public:
		about(void)
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
		~about()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label1;


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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(about::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(364, 333);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(93, 38);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Close";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &about::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 45);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(769, 232);
			this->label1->TabIndex = 2;
			this->label1->Text = resources->GetString(L"label1.Text");
			this->label1->Click += gcnew System::EventHandler(this, &about::label1_Click);
			// 
			// about
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(818, 417);
			this->ControlBox = false;
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->DoubleBuffered = true;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"about";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Fingerprint SDK Demo - About";
			this->Load += gcnew System::EventHandler(this, &about::about_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		Form::Close();
	}

	private: System::Void about_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
