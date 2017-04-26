#include "Hauptfenster.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	RelentlessDotNet::Hauptfenster^ mainFrame = gcnew RelentlessDotNet::Hauptfenster;
	Application::Run(mainFrame);
}