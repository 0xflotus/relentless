#pragma once
#include "Entry.h"

namespace RelentlessDotNet {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text::RegularExpressions; // fuer RegEx

	/// <summary>
	/// Zusammenfassung für Hauptfenster
	/// </summary>
	public ref class Hauptfenster : public System::Windows::Forms::Form
	{
	public:
		Hauptfenster(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
			liste = gcnew Generic::List<Entry^>;
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Hauptfenster()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  txtbox1;
	private: System::Windows::Forms::Button^  btnWeiter;

	private: System::Windows::Forms::TextBox^  txtbox2;

	private:
		//Attribute
		Generic::List<Entry^>^ liste;
		int sizeSpeicher = 0;


	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;


	private: System::Windows::Forms::TextBox^  txtArea;

	private: System::Windows::Forms::Button^  btnFilter;
	private: System::Windows::Forms::TextBox^  txtFilter;


	private: System::Windows::Forms::RadioButton^  rbPreis;

	private: System::Windows::Forms::ToolTip^  toolTipOpen;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  closeToolStripMenuItem;
	private: System::Windows::Forms::BindingSource^  bindingSource1;
	private: System::Windows::Forms::Label^  lblSeparator;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenu;

	private: System::Windows::Forms::ToolStripMenuItem^  weiterToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  infoToolStripMenuItem;



	private: System::Windows::Forms::RadioButton^  rbTitel;

			 //Methoden
	private: System::Void buttonWeiter_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void buttonFilter_Click(System::Object^  sender, System::EventArgs^  e);

	private: System::Void shortCuts(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
	private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void infoToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void loadXMLwithDotNet(System::Object^  sender, System::EventArgs^  e);

	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Hauptfenster::typeid));
			this->txtbox1 = (gcnew System::Windows::Forms::TextBox());
			this->contextMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->weiterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->btnWeiter = (gcnew System::Windows::Forms::Button());
			this->txtbox2 = (gcnew System::Windows::Forms::TextBox());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->txtArea = (gcnew System::Windows::Forms::TextBox());
			this->btnFilter = (gcnew System::Windows::Forms::Button());
			this->txtFilter = (gcnew System::Windows::Forms::TextBox());
			this->rbPreis = (gcnew System::Windows::Forms::RadioButton());
			this->rbTitel = (gcnew System::Windows::Forms::RadioButton());
			this->toolTipOpen = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->infoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->closeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bindingSource1 = (gcnew System::Windows::Forms::BindingSource(this->components));
			this->lblSeparator = (gcnew System::Windows::Forms::Label());
			this->contextMenu->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bindingSource1))->BeginInit();
			this->SuspendLayout();
			// 
			// txtbox1
			// 
			this->txtbox1->ContextMenuStrip = this->contextMenu;
			this->txtbox1->Location = System::Drawing::Point(12, 37);
			this->txtbox1->Name = L"txtbox1";
			this->txtbox1->Size = System::Drawing::Size(261, 20);
			this->txtbox1->TabIndex = 0;
			// 
			// contextMenu
			// 
			this->contextMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->weiterToolStripMenuItem });
			this->contextMenu->Name = L"contextMenuStrip1";
			this->contextMenu->Size = System::Drawing::Size(107, 26);
			// 
			// weiterToolStripMenuItem
			// 
			this->weiterToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"weiterToolStripMenuItem.Image")));
			this->weiterToolStripMenuItem->Name = L"weiterToolStripMenuItem";
			this->weiterToolStripMenuItem->Size = System::Drawing::Size(106, 22);
			this->weiterToolStripMenuItem->Text = L"weiter";
			this->weiterToolStripMenuItem->Click += gcnew System::EventHandler(this, &Hauptfenster::buttonWeiter_Click);
			// 
			// btnWeiter
			// 
			this->btnWeiter->Location = System::Drawing::Point(290, 73);
			this->btnWeiter->Name = L"btnWeiter";
			this->btnWeiter->Size = System::Drawing::Size(51, 23);
			this->btnWeiter->TabIndex = 1;
			this->btnWeiter->Text = L"weiter";
			this->toolTipOpen->SetToolTip(this->btnWeiter, L"\"Einen Datensatz weiter springen\"");
			this->btnWeiter->UseVisualStyleBackColor = true;
			this->btnWeiter->Click += gcnew System::EventHandler(this, &Hauptfenster::buttonWeiter_Click);
			this->btnWeiter->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Hauptfenster::shortCuts);
			// 
			// txtbox2
			// 
			this->txtbox2->ContextMenuStrip = this->contextMenu;
			this->txtbox2->Location = System::Drawing::Point(290, 37);
			this->txtbox2->Name = L"txtbox2";
			this->txtbox2->Size = System::Drawing::Size(51, 20);
			this->txtbox2->TabIndex = 2;
			// 
			// openFileDialog
			// 
			this->openFileDialog->FileName = L"openFileDialog1";
			// 
			// txtArea
			// 
			this->txtArea->Location = System::Drawing::Point(13, 199);
			this->txtArea->Multiline = true;
			this->txtArea->Name = L"txtArea";
			this->txtArea->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->txtArea->Size = System::Drawing::Size(328, 304);
			this->txtArea->TabIndex = 4;
			this->txtArea->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Hauptfenster::shortCuts);
			// 
			// btnFilter
			// 
			this->btnFilter->Location = System::Drawing::Point(290, 173);
			this->btnFilter->Name = L"btnFilter";
			this->btnFilter->Size = System::Drawing::Size(51, 20);
			this->btnFilter->TabIndex = 5;
			this->btnFilter->Text = L"filter";
			this->toolTipOpen->SetToolTip(this->btnFilter, L"\"Filtert die Ausgabe\"");
			this->btnFilter->UseVisualStyleBackColor = true;
			this->btnFilter->Click += gcnew System::EventHandler(this, &Hauptfenster::buttonFilter_Click);
			this->btnFilter->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Hauptfenster::shortCuts);
			// 
			// txtFilter
			// 
			this->txtFilter->Location = System::Drawing::Point(12, 173);
			this->txtFilter->Name = L"txtFilter";
			this->txtFilter->Size = System::Drawing::Size(261, 20);
			this->txtFilter->TabIndex = 6;
			this->txtFilter->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Hauptfenster::shortCuts);
			// 
			// rbPreis
			// 
			this->rbPreis->AutoSize = true;
			this->rbPreis->Checked = true;
			this->rbPreis->Location = System::Drawing::Point(13, 140);
			this->rbPreis->Name = L"rbPreis";
			this->rbPreis->Size = System::Drawing::Size(48, 17);
			this->rbPreis->TabIndex = 9;
			this->rbPreis->TabStop = true;
			this->rbPreis->Text = L"Preis";
			this->rbPreis->UseVisualStyleBackColor = true;
			this->rbPreis->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Hauptfenster::shortCuts);
			// 
			// rbTitel
			// 
			this->rbTitel->AutoSize = true;
			this->rbTitel->Location = System::Drawing::Point(77, 140);
			this->rbTitel->Name = L"rbTitel";
			this->rbTitel->Size = System::Drawing::Size(45, 17);
			this->rbTitel->TabIndex = 10;
			this->rbTitel->Text = L"Titel";
			this->rbTitel->UseVisualStyleBackColor = true;
			this->rbTitel->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Hauptfenster::shortCuts);
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::Control;
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(351, 24);
			this->menuStrip1->TabIndex = 11;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->openToolStripMenuItem,
					this->infoToolStripMenuItem, this->closeToolStripMenuItem
			});
			this->fileToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"fileToolStripMenuItem.Image")));
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(62, 20);
			this->fileToolStripMenuItem->Text = L"Datei";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"openToolStripMenuItem.Image")));
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->openToolStripMenuItem->Text = L"Oeffnen";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &Hauptfenster::loadXMLwithDotNet);
			// 
			// infoToolStripMenuItem
			// 
			this->infoToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"infoToolStripMenuItem.Image")));
			this->infoToolStripMenuItem->Name = L"infoToolStripMenuItem";
			this->infoToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->infoToolStripMenuItem->Text = L"Info";
			this->infoToolStripMenuItem->Click += gcnew System::EventHandler(this, &Hauptfenster::infoToolStripMenuItem_Click);
			// 
			// closeToolStripMenuItem
			// 
			this->closeToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"closeToolStripMenuItem.Image")));
			this->closeToolStripMenuItem->Name = L"closeToolStripMenuItem";
			this->closeToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->closeToolStripMenuItem->Text = L"Exit";
			this->closeToolStripMenuItem->Click += gcnew System::EventHandler(this, &Hauptfenster::exitToolStripMenuItem_Click);
			// 
			// lblSeparator
			// 
			this->lblSeparator->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->lblSeparator->Location = System::Drawing::Point(12, 114);
			this->lblSeparator->Name = L"lblSeparator";
			this->lblSeparator->Size = System::Drawing::Size(329, 2);
			this->lblSeparator->TabIndex = 12;
			this->lblSeparator->Text = L"label1";
			// 
			// Hauptfenster
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(351, 506);
			this->Controls->Add(this->lblSeparator);
			this->Controls->Add(this->rbTitel);
			this->Controls->Add(this->rbPreis);
			this->Controls->Add(this->txtFilter);
			this->Controls->Add(this->btnFilter);
			this->Controls->Add(this->txtArea);
			this->Controls->Add(this->txtbox2);
			this->Controls->Add(this->btnWeiter);
			this->Controls->Add(this->txtbox1);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"Hauptfenster";
			this->Text = L"Relentless.Net";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Hauptfenster::shortCuts);
			this->contextMenu->ResumeLayout(false);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bindingSource1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
};
}

auto compareByPrice(Entry^e1, Entry^e2) -> int;
