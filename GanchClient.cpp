// Listing 2
#using "system.dll"
using namespace System;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Threading;

int main(array<String^>^ argv)
{
    int port = 0;
	int messageCount = 0;
	if (argv->Length != 2) {//use defaults
		                  // e.g., when program started from Visual Studio
        port = 9999;	  //this program's default port
		messageCount = 4; //default number of messages sent
    }
	else{ //program started with command-line arguments
          //for port and message-count
		try {
			port = Int32::Parse(argv[0]); 
		}
		catch (FormatException^ e){
			Console::WriteLine("Port number {0} is ill-formed", argv[0]);
			Environment::Exit(2);
		}
		try	{
			messageCount = Int32::Parse(argv[1]);
		}
		catch (FormatException^ e)	{
			Console::WriteLine("Message count {0} is ill-formed", argv[1]);
			Environment::Exit(4);
		}	
	}
	// The range of valid ports for this system, usually 0-65535
    if (port < IPEndPoint::MinPort || port > IPEndPoint::MaxPort) {
        Console::WriteLine("Port number must be in the range {0}-{1}",
                            IPEndPoint::MinPort, IPEndPoint::MaxPort);
        Environment::Exit(3);
    }
    IPAddress^ ipAddress = nullptr;
    try
    {
/*1*/   // three possible ways to set the IP address 
		//ipAddress = Dns::GetHostEntry(Dns::GetHostName())->AddressList[0];
		//ipAddress=Dns::GetHostEntry("localhost")->AddressList[0]; 
		ipAddress = (IPAddress^)Dns::GetHostEntry("127.0.0.1")->AddressList[0];
/*2*/    IPEndPoint^ ipEndpoint = gcnew IPEndPoint(ipAddress, port);

/*3*/    // TCP/IP is connection-oriented: using streams
		 Socket^ clientSocket = gcnew Socket(ipAddress -> AddressFamily,
								SocketType::Stream, ProtocolType::Tcp);

/*4*/    clientSocket->Connect(ipEndpoint);

        NetworkStream^ netStream = gcnew NetworkStream(clientSocket);		
        BinaryReader^ br = gcnew BinaryReader(netStream);
        BinaryWriter^ bw = gcnew BinaryWriter(netStream);

        int value1, value2;
        int result;

        Random^ random = gcnew Random;
        for (int i = 1; i <= messageCount; ++i)
        {
/*5*/         value1 = static_cast<int>(random->NextDouble() * 100);
/*6*/         value2 = static_cast<int>(random->NextDouble() * 100);

/*7*/         bw->Write(value1);
/*8*/         bw->Write(value2);
              Console::Write("Sent values {0,3} and {1,3}",
                  value1, value2);

/*9*/         result = br->ReadInt32(); 			  
              Console::WriteLine(", received result {0,3}", result);
/*10*/        Thread::Sleep(8000);
         } //end for

/*11*/   clientSocket->Shutdown(SocketShutdown::Both);
		 Console::WriteLine("Notified server we're shutting down");
/*12*/   clientSocket->Close();
/*13*/   netStream->Close();
         Console::WriteLine("Shutting down client");
       } // end try
/*14*/ catch (SocketException^ e) {
          Console::WriteLine("Request to connect to {0} on port {1} failed"
                            + "\nbecause of {2}", ipAddress, port, e);
          Environment::Exit(5);
       }
} // end main

