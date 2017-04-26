#include "Hauptfenster.h"
#include "Entry.h"

System::Void RelentlessDotNet::Hauptfenster::buttonWeiter_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (liste->Count > 0)
	{
		++sizeSpeicher;
		sizeSpeicher -= sizeSpeicher == liste->Count ? sizeSpeicher : 0;
		txtbox1->Text = liste[sizeSpeicher]->ToString();
		txtbox2->Text = (sizeSpeicher + 1).ToString() + " / " + liste->Count;
	}
	else { MessageBox::Show(this, "Es wurde keine Liste geladen", "Fehler", MessageBoxButtons::OK, MessageBoxIcon::Error); }
}

System::Void RelentlessDotNet::Hauptfenster::loadXMLwithDotNet(System::Object^sender, System::EventArgs ^e) {
	using namespace System::Xml;
	openFileDialog = gcnew OpenFileDialog;
	openFileDialog->InitialDirectory = IO::Directory::GetCurrentDirectory();
	openFileDialog->Filter = "xml files (*.xml)|*.xml";

	if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		try {
			//XML laden
			XmlDocument^ doc = gcnew XmlDocument;
			doc->Load(openFileDialog->FileName);
			XmlNodeList^ nodeList = doc->DocumentElement->SelectNodes("entry");
			for each (XmlNode^ node  in nodeList) { liste->Add(gcnew Entry(node->SelectSingleNode("title")->InnerText, float::Parse(node->SelectSingleNode("price")->InnerText->Replace(".", ",")))); }
			liste->Sort(gcnew Comparison<Entry^>(compareByPrice));
			txtbox1->Text = liste[sizeSpeicher]->ToString();
			txtbox2->Text = (sizeSpeicher + 1).ToString() + " / " + liste->Count;
			for each(Entry^ el in liste) { txtArea->AppendText(el->ToString() + "\n"); }
		}
		catch (Exception^ ex) { MessageBox::Show(this, "Fehler beim Laden des XML", "Fehler", MessageBoxButtons::OK, MessageBoxIcon::Error); }
	}
}

System::Void RelentlessDotNet::Hauptfenster::buttonFilter_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (liste->Count < 1) { MessageBox::Show(this, "Es wurde keine Liste geladen", "Fehler", MessageBoxButtons::OK, MessageBoxIcon::Error); }
	else if (String::IsNullOrEmpty(txtFilter->Text->Trim())) 
	{ 
		MessageBox::Show(this, "Der Filter ist leer", "Warnung", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		txtArea->Text = "";
		for each(Entry^ el in liste) { txtArea->AppendText(el->ToString() + "\n"); }
	}
	else
	{
		txtFilter->Text = txtFilter->Text->Trim();
		txtArea->Text = "";
		Regex^ rgx;
		float limit = 0.0f;
		if (rbPreis->Checked)
		{
			try { limit = float::Parse(txtFilter->Text); }
			catch (Exception^ ex) { MessageBox::Show(this, "Fehler beim parsen", "Fehler", MessageBoxButtons::OK, MessageBoxIcon::Error); }
		}
		else
		{
			rgx = gcnew Regex("^(" + txtFilter->Text + "*[a-zA-Z])");
		}
		for each (Entry^ e in liste) { txtArea->AppendText((rbPreis->Checked ? e->Price < limit ? e->ToString() + "\n" : "" : rgx->IsMatch(e->Title) ? e->ToString() + "\n" : "")); }
	}
}


System::Void RelentlessDotNet::Hauptfenster::shortCuts(System::Object ^ sender, System::Windows::Forms::KeyEventArgs ^ e)
{
	if (e->KeyCode == Keys::W && e->Alt) { buttonWeiter_Click(sender, e); }
	else if (e->KeyCode == Keys::O && e->Alt) { loadXMLwithDotNet(sender, e); }
	else if (e->KeyCode == Keys::F && e->Alt) { buttonFilter_Click(sender, e); }
	else if (e->KeyCode == Keys::X && e->Alt) { exitToolStripMenuItem_Click(sender, e); }
	else if (e->KeyCode == Keys::I && e->Alt) { infoToolStripMenuItem_Click(sender, e); }
}

System::Void RelentlessDotNet::Hauptfenster::exitToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e) { Application::Exit(); }
System::Void RelentlessDotNet::Hauptfenster::infoToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e) { MessageBox::Show(this, "All Rites reversed", "Licensed under GNU GPLv3", MessageBoxButtons::OK, MessageBoxIcon::Information); }
int compareByPrice(Entry^e1, Entry^e2) { return e1->Price < e2->Price ? e1->Price == e2->Price ? 0 : -1 : 1; }