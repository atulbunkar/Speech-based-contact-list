#pragma once
 #include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "vector"
#include "iostream"
#include <stdlib.h> 
#include <conio.h>
#include <sstream>
#include "tchar.h"
#include <list>
#include <stdio.h>
#include <Windows.h>

#include "sp_project.h";

const char *temp[10] = { "Pranjal","Parul","Ishita","Mukund","Virat","Sarthak","Madhuri","Priyansh","Rohan","Kirti" } ;

const char *mail[10] = { "pj12@gmail.com","parul.bb66@gmail.com","ishi44@gmail.com","mukku97@gmail.com","vir.at64@gmail.com","stk4u@gmail.com","madhu97@gmail.com","priyansh98@gmail.com","rohan.kj21@gmail.com","kkirti9@gmail.com" } ;

const char *pnum[10] = {"99818781272","998142243242","942376423422","99815466672","99835642552","9952532472","99446255255","99634643662","97425245622","95235262662" } ;


namespace contact {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class myform : public System::Windows::Forms::Form
	{
		
	public:
		myform(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			CheckForIllegalCrossThreadCalls=false; //to copy

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~myform()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  Rec;
	private: System::Windows::Forms::Label^  Name;
	private: System::Windows::Forms::Label^  pno;

	private: System::Windows::Forms::Label^  Email;

	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label3;

	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Label^  label8;

	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Label^  label15;






	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
		



#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->Rec = (gcnew System::Windows::Forms::Button());
			this->Name = (gcnew System::Windows::Forms::Label());
			this->pno = (gcnew System::Windows::Forms::Label());
			this->Email = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Tomato;
			this->label1->Font = (gcnew System::Drawing::Font(L"Montserrat", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label1->Location = System::Drawing::Point(166, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(585, 49);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Speech Based Contact List";
			this->label1->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->label1->Click += gcnew System::EventHandler(this, &myform::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)), 
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(41, 154);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(291, 25);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Click REC to Search Contact list";
			// 
			// Rec
			// 
			this->Rec->BackColor = System::Drawing::Color::MediumTurquoise;
			this->Rec->Cursor = System::Windows::Forms::Cursors::Default;
			this->Rec->Font = (gcnew System::Drawing::Font(L"Montserrat", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->Rec->ForeColor = System::Drawing::SystemColors::Desktop;
			this->Rec->Location = System::Drawing::Point(111, 191);
			this->Rec->Name = L"Rec";
			this->Rec->Size = System::Drawing::Size(129, 56);
			this->Rec->TabIndex = 2;
			this->Rec->Text = L"Rec";
			this->Rec->UseVisualStyleBackColor = false;
			this->Rec->Click += gcnew System::EventHandler(this, &myform::Rec_Click);
			// 
			// Name
			// 
			this->Name->AutoSize = true;
			this->Name->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Name->Location = System::Drawing::Point(53, 315);
			this->Name->Name = L"Name";
			this->Name->Size = System::Drawing::Size(59, 17);
			this->Name->TabIndex = 6;
			this->Name->Text = L"Name :";
			// 
			// pno
			// 
			this->pno->AutoSize = true;
			this->pno->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->pno->Location = System::Drawing::Point(53, 351);
			this->pno->Name = L"pno";
			this->pno->Size = System::Drawing::Size(94, 17);
			this->pno->TabIndex = 7;
			this->pno->Text = L"Phone No. :";
			// 
			// Email
			// 
			this->Email->AutoSize = true;
			this->Email->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Email->Location = System::Drawing::Point(55, 390);
			this->Email->Name = L"Email";
			this->Email->Size = System::Drawing::Size(57, 17);
			this->Email->TabIndex = 8;
			this->Email->Text = L"Email :";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(106, 268);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(144, 25);
			this->label6->TabIndex = 9;
			this->label6->Text = L"Contact Details";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(220, 311);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(20, 17);
			this->label3->TabIndex = 10;
			this->label3->Text = L"...";
			this->label3->Click += gcnew System::EventHandler(this, &myform::label3_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(220, 390);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(20, 17);
			this->label5->TabIndex = 12;
			this->label5->Text = L"...";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::MediumTurquoise;
			this->button1->Font = (gcnew System::Drawing::Font(L"Perpetua Titling MT", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->button1->ForeColor = System::Drawing::SystemColors::Desktop;
			this->button1->Location = System::Drawing::Point(576, 191);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(142, 56);
			this->button1->TabIndex = 13;
			this->button1->Text = L"TNN";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &myform::button1_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(735, 456);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(20, 17);
			this->label4->TabIndex = 14;
			this->label4->Text = L"...";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::SystemColors::ControlLight;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(211, 452);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(244, 29);
			this->label7->TabIndex = 15;
			this->label7->Text = L"Contact list Directory :";
			// 
			// comboBox1
			// 
			this->comboBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->comboBox1->ForeColor = System::Drawing::Color::Black;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(459, 451);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(172, 26);
			this->comboBox1->TabIndex = 17;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(511, 316);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(167, 29);
			this->label8->TabIndex = 18;
			this->label8->Text = L"Name Added :";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(697, 316);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(21, 20);
			this->label9->TabIndex = 19;
			this->label9->Text = L"...";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(691, 268);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(27, 25);
			this->label10->TabIndex = 20;
			this->label10->Text = L"...";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label11->Location = System::Drawing::Point(626, 96);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(179, 32);
			this->label11->TabIndex = 21;
			this->label11->Text = L"Live Training";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(105, 96);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(169, 32);
			this->label12->TabIndex = 22;
			this->label12->Text = L"Live Testing";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->BackColor = System::Drawing::Color::Gainsboro;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label13->Location = System::Drawing::Point(584, 154);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(259, 25);
			this->label13->TabIndex = 23;
			this->label13->Text = L"Click TNN to train new name";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(220, 351);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(20, 17);
			this->label14->TabIndex = 24;
			this->label14->Text = L"...";
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::Turquoise;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->button2->ForeColor = System::Drawing::Color::DarkMagenta;
			this->button2->Location = System::Drawing::Point(265, 484);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(115, 57);
			this->button2->TabIndex = 25;
			this->button2->Text = L"CLICK TO SEE";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &myform::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(738, 191);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 26;
			this->button3->Text = L"Live Training";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label15->Location = System::Drawing::Point(653, 452);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(76, 25);
			this->label15->TabIndex = 27;
			this->label15->Text = L"Count :";
			// 
			// myform
			// 
			this->AccessibleName = L"hh";
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->ClientSize = System::Drawing::Size(906, 591);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->Email);
			this->Controls->Add(this->pno);
			this->Controls->Add(this->Name);
			this->Controls->Add(this->Rec);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->ForeColor = System::Drawing::SystemColors::ControlText;
//			this->Name = L"myform";
			this->ResumeLayout(false);
			this->PerformLayout();
		}




#pragma endregion

	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void Rec_Click(System::Object^  sender, System::EventArgs^  e) {

			comboBox1->Items->Clear();
			vector<string> names(10);
	
			for(int i =0 ; i<=trained_words ;i++){
				names[i] = temp[i];
				String^ str=gcnew String(names[i].c_str());
				comboBox1->Items->Add(str);
			}
	
			int result = testing(3);	
			String^ str3=gcnew String(names[result].c_str());
			label3 -> Text = str3 ;
	}

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

			 label10 ->Text = L"Training New Name....";
			
			 comboBox1->Items->Clear();

			 testing(1);
			 
			 String^ str2= System::Convert::ToString(trained_words+1) ;
			 label4 -> Text = str2 ;

			vector<string> names(10);
	
			for(int i =0 ; i<=trained_words ;i++){
				names[i] = temp[i];
				String^ str=gcnew String(names[i].c_str());
				comboBox1->Items->Add(str);
			}
			
			String^ str5=gcnew String(names[trained_words].c_str());
			label9-> Text = str5;

		 }


private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

			 testing(2);

			 String^ str2= System::Convert::ToString(trained_words+1) ;
			 label4 -> Text = str2 ;

			comboBox1->Items->Clear();
			vector<string> names(10);
	
			for(int i =0 ; i<=trained_words ;i++){
				names[i] = temp[i];
				String^ str=gcnew String(names[i].c_str());
				comboBox1->Items->Add(str);
			}
		 }
};
}
