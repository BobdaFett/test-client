#include "client.h"

using namespace System;
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
	clientSocket->Connect(endpoint);  // sends connection to the server at the specified IP.

	Console::WriteLine("Connected.");

	// Should this be successful, we create a NetworkStream for the data.
	netStream = gcnew NetworkStream(clientSocket);
	writer = gcnew BinaryWriter(netStream);
	reader = gcnew BinaryReader(netStream);
}

System::Void client::SendThread(Object^ sender, EventArgs^ e) {
	Thread^ sendThread = gcnew Thread(gcnew ThreadStart(this, &client::SendData));
	Console::Write("Created thread. Starting... ");
	sendThread->Start();
	Console::WriteLine("Started.");
}

System::Void client::SendData() {
	// Send some sort of data to the server.
	Random^ rand = gcnew Random();

	// Should send 5 packets with random numbers.
	for (int i = 0; i < 5; i++) {
		// Sends data.
		Console::Write("Sending number... ");
		writer->Write(rand->Next());
		Console::WriteLine("Done.");

		// Reads response from server.
		Console::Write("Reading result... ");
		int result = reader->ReadInt32();
		Console::WriteLine("Read {0}.", result);
	}
}