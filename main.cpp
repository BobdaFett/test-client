#include "client.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace testclient;

[STAThread]
int main(array<String^>^ args) {

	// Create and run form.
	Application::Run(gcnew client());

	return 0;
}