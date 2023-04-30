#include "client.h"

using namespace System;
using namespace System::Text;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Threading;
using namespace testclient;

System::Void client::ServerConnect(System::Object^ sender, System::EventArgs^ e) {
	// Create pieces of server and connect to it.
	// May eventually accept data for where, when, and how to connect as well.
	ip = Dns::GetHostEntry("localhost")->AddressList[0];
	endpoint = gcnew IPEndPoint(ip, 2345);

	Console::Write("Attempting to connect to {0}... ", ip);

	clientSocket = gcnew Socket(ip->AddressFamily, SocketType::Stream, ProtocolType::Tcp);
	clientSocket->Connect(endpoint);  // attempts connection to the server at the specified IP.

	Console::WriteLine("Connected.");

	// Should this be successful, we create a NetworkStream for the data.
	netStream = gcnew NetworkStream(clientSocket);
	writer = gcnew BinaryWriter(netStream);
	reader = gcnew BinaryReader(netStream);

	connected = true;
}

System::Void client::ServerDisconnect(Object^ sender, EventArgs^ e) {
	clientSocket->Shutdown(SocketShutdown::Both);
	clientSocket->Close();
	netStream->Close();
}

System::Void client::SendThread(Object^ sender, EventArgs^ e) {
	Console::Write("Creating thread... ");
	Thread^ sendThread = gcnew Thread(gcnew ThreadStart(this, &client::SendData));
	Console::Write("Done.\nStarting thread... ");
	sendThread->Start();
	Console::WriteLine("Done.");
}

System::Void client::SendData() {
	// Send some sort of data to the server.
	String^ message = "hello there!";
	if (connected) {
		Console::WriteLine("Sending message... ");
		writer->Write(message);
		Console::WriteLine("Message sent.");

		String^ response = reader->ReadString();
		Console::WriteLine("Recieved {0}", response);
	}
	else {
		Console::WriteLine("Client is not connected. Please connect to a server first.");
	}
}

System::Void client::RequestSubtract(Object^ sender, EventArgs^ e) {
	if (connected) {
		// Create the message.
		String^ message = "SUBTRACT ";
		int num1 = Int32::Parse(textBox1->Text);
		int num2 = Int32::Parse(textBox2->Text);
		message += num1 + " " + num2;

		// Send the message.
		Console::Write("Sending message... ");
		writer->Write(message);
		Console::WriteLine("Done.");

		// Read the server's response.
		// TODO Send to another function or save in a variable somewhere. This will be the data that's worked on afterwards.
		Console::Write("Reading message... ");
		int response = reader->ReadInt32();
		Console::WriteLine("{0} - {1} = {2}", num1, num2, response);
	}
	else {
		Console::WriteLine("Client is not connected. Please connect to a server first.");
	}
}

System::Void client::RequestAdd(Object^ sender, EventArgs^ e) {
	if (connected) {
		// Create the message.
		String^ message = "ADD ";
		int num1 = Int32::Parse(textBox1->Text);
		int num2 = Int32::Parse(textBox2->Text);
		message += num1 + " " + num2;

		// Send the message.
		Console::Write("Sending message... ");
		writer->Write(message);
		Console::WriteLine("Done.");

		// Read the server's response.
		// TODO Send to another function or save in a variable somewhere. This will be the data that's worked on afterwards.
		Console::Write("Reading message... ");
		int response = reader->ReadInt32();
		Console::WriteLine("{0} + {1} = {2}", num1, num2, response);
	}
	else {
		Console::WriteLine("Client is not connected. Please connect to a server first.");
	}
}
