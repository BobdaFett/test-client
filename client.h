#pragma once

namespace testclient {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Net;
	using namespace System::Net::Sockets;

	/// A testing client which will simply send some numbers to a server at your localhost
	public ref class client : public System::Windows::Forms::Form {
	private:
		IPAddress^ ip;
		IPEndPoint^ endpoint;
		Socket^ clientSocket;

		NetworkStream^ netStream;
		BinaryReader^ reader;
		BinaryWriter^ writer;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;

		bool connected = false;

		/// Connects the client to the server at "localhost".
		/// This eventually will be called from a modal window that appears upon running the application.
		System::Void ServerConnect(Object^, EventArgs^);

		/// Disconnects the client from the server.
		/// This will eventually be called as a button event.
		System::Void ServerDisconnect(Object^, EventArgs^);

		/// Creates a thread to send data to the server, assuming that it connected.
		/// Parameters are due to the fact that this function is called as an event, and must have them for the event function template.
		System::Void SendThread(Object^, EventArgs^);

		/// Sends a message to the server. Do not use - simply for easy debugging.
		System::Void SendData();

		/// Generates a command SUBTRACT to send to the server.
		/// Will check for values inside of text boxes in the user interface.
		/// This is sent as an event from a button.
		System::Void RequestSubtract(Object^, EventArgs^);

		/// Generates a command ADD to send to the server.
		/// Will check for values inside of text boxes in the user interface.
		/// This is sent as an event from a button.
		System::Void RequestAdd(Object^, EventArgs^);

	public:
		client(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~client()
		{
			ServerDisconnect(nullptr, nullptr);
			if (components)
			{
				delete components;
			}
			
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(155, 160);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(117, 38);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Subtract";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &client::RequestSubtract);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(72, 12);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(135, 38);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Connect";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &client::ServerConnect);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(134, 79);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 2;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(134, 105);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 20);
			this->textBox2->TabIndex = 3;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(12, 160);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(117, 38);
			this->button3->TabIndex = 4;
			this->button3->Text = L"Add";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &client::RequestAdd);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(31, 82);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(56, 13);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Number 1:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(31, 108);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(56, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Number 2:";
			// 
			// client
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 216);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"client";
			this->Text = L"client";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
};
}
