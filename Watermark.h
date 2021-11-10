#pragma once
#include <stdio.h>
//#include <opencv2/core.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui.hpp>

#include "Threads.h"
#include <iostream>

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <stdint.h>


//using namespace cv;
using namespace std;
using namespace System;

#include "Learning.h"

#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>

int Parse_DataGrid(System::Object^ sender, LogoLearning* dt, int id);
int Parse_DataTable(System::Data::DataTable^ table, LogoLearning* dt, int id);

extern void Text_Learning(System::String^ size, LogoLearning* dt, int step);
extern string Image_Size_std;
namespace Watermark {


	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Globalization;
	using namespace System::Runtime::InteropServices;
	using namespace System::Collections::Generic;
	/// <summary>
	/// Summary for Watermark
	/// </summary>
	public ref class Watermark : public System::Windows::Forms::Form
	{
	public:
		Watermark(void)
		{
			InitializeComponent();
			//Image_Size = "1400x1120";
			//Image_Size_std = "1400x1120";
			//800x640
			//800x800
			//1200x960
			//1400x1120
			//1500x1200
#if (_DEBUG == 1)
			Image_Size = "800x640";
			Image_Size_std = "800x640";
			textBox_Learning_Size->Text = Image_Size;

			//folderName_In = R""""(D:\ABITANT\img_out\Image_Learn\1500x1200)"""";
			folderName_In = R""""(D:\ABITANT\img_out\Image_Learn\800x640)"""";
			label_Open_in->Text = folderName_In;
			Open_in = (TCHAR*)Marshal::StringToHGlobalUni(folderName_In).ToPointer();

			//folderName_Out = R""""(D:\ABITANT\img_out\Image_Learn\1200x960)"""";
			folderName_Out = "D:\\ABITANT\\img_out\\Image_Test\\800x640";
			//folderName_Out = R""""(D:\ABITANT\img_out\Image_Learn\1500x1200)"""";
			//folderName_Out = R""""(D:\ABITANT\Soft\Watermark\Watermark\Image_Out)"""";
			label_Open_out->Text = folderName_Out;
			Open_out = (TCHAR*)Marshal::StringToHGlobalUni(folderName_Out).ToPointer();

			button_Read_To_DataGrid_Click(button_Read_To_DataGrid, EventArgs::Empty);
#else
			button_Read_To_DataGrid->Visible = false;
			button_Save_DataGrid->Visible = false;
			button1->Visible = false;
			button_Training->Visible = false;
			dataGridView1->Visible = false;
			textBox_Learning_Size->Visible = false;
			textBox_JPEG_Compression->Visible = false;
			button_Copy_Image->Visible = false;
#endif



				//
				//TODO: Add the constructor code here
				//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Watermark()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog_In;
	protected:
	private: System::Windows::Forms::Button^ button_Open_in;
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

	public:
		System::String^ folderName_In;
		System::String^ folderName_Out;
		static System::String^ Image_Size = "";

	private: System::Windows::Forms::Label^ label_Open_in;
	public:
	private: System::Windows::Forms::Label^ label_Open_out;
	private: System::Windows::Forms::Button^ button_Open_out;
	private: System::Windows::Forms::Button^ button_Training;

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button_Processing_Images;

































	private: System::Windows::Forms::TextBox^ textBox_JPEG_Compression;
	private: System::Windows::Forms::Timer^ timer_display;
	private: System::Windows::Forms::Button^ button_Stop_Processing_Images;
	private: System::Windows::Forms::TextBox^ textBox_Learning_Size;






	private: System::Windows::Forms::DataGridView^ dataGridView1;






	private: System::Windows::Forms::Button^ button_Save_DataGrid;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	private: System::Windows::Forms::Button^ button_Read_To_DataGrid;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::Button^ button_Copy_Image;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ ID;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Color_Front;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Color_Back;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Window_Start;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Window_Size;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Image_Path;















#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Required method for Designer support - do not modify
		   /// the contents of this method with the code editor.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   this->folderBrowserDialog_In = (gcnew System::Windows::Forms::FolderBrowserDialog());
			   this->button_Open_in = (gcnew System::Windows::Forms::Button());
			   this->label_Open_in = (gcnew System::Windows::Forms::Label());
			   this->label_Open_out = (gcnew System::Windows::Forms::Label());
			   this->button_Open_out = (gcnew System::Windows::Forms::Button());
			   this->button_Training = (gcnew System::Windows::Forms::Button());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->button_Processing_Images = (gcnew System::Windows::Forms::Button());
			   this->textBox_JPEG_Compression = (gcnew System::Windows::Forms::TextBox());
			   this->timer_display = (gcnew System::Windows::Forms::Timer(this->components));
			   this->button_Stop_Processing_Images = (gcnew System::Windows::Forms::Button());
			   this->textBox_Learning_Size = (gcnew System::Windows::Forms::TextBox());
			   this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			   this->ID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->Color_Front = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->Color_Back = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->Window_Start = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->Window_Size = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->Image_Path = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->button_Save_DataGrid = (gcnew System::Windows::Forms::Button());
			   this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			   this->button_Read_To_DataGrid = (gcnew System::Windows::Forms::Button());
			   this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			   this->button_Copy_Image = (gcnew System::Windows::Forms::Button());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // button_Open_in
			   // 
			   this->button_Open_in->BackColor = System::Drawing::Color::Green;
			   this->button_Open_in->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Open_in->Location = System::Drawing::Point(12, 12);
			   this->button_Open_in->Name = L"button_Open_in";
			   this->button_Open_in->Size = System::Drawing::Size(130, 30);
			   this->button_Open_in->TabIndex = 227;
			   this->button_Open_in->Tag = L"Open_In";
			   this->button_Open_in->Text = L"Open In";
			   this->button_Open_in->UseVisualStyleBackColor = false;
			   this->button_Open_in->Click += gcnew System::EventHandler(this, &Watermark::button_Open_in_Click);
			   // 
			   // label_Open_in
			   // 
			   this->label_Open_in->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label_Open_in->ForeColor = System::Drawing::Color::Maroon;
			   this->label_Open_in->Location = System::Drawing::Point(148, 21);
			   this->label_Open_in->Name = L"label_Open_in";
			   this->label_Open_in->Size = System::Drawing::Size(505, 16);
			   this->label_Open_in->TabIndex = 287;
			   this->label_Open_in->Text = L"Выбирете папку";
			   // 
			   // label_Open_out
			   // 
			   this->label_Open_out->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label_Open_out->ForeColor = System::Drawing::Color::Maroon;
			   this->label_Open_out->Location = System::Drawing::Point(148, 57);
			   this->label_Open_out->Name = L"label_Open_out";
			   this->label_Open_out->Size = System::Drawing::Size(505, 16);
			   this->label_Open_out->TabIndex = 289;
			   this->label_Open_out->Text = L"Выбирете папку";
			   // 
			   // button_Open_out
			   // 
			   this->button_Open_out->BackColor = System::Drawing::Color::Green;
			   this->button_Open_out->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Open_out->Location = System::Drawing::Point(12, 48);
			   this->button_Open_out->Name = L"button_Open_out";
			   this->button_Open_out->Size = System::Drawing::Size(130, 30);
			   this->button_Open_out->TabIndex = 288;
			   this->button_Open_out->Tag = L"Open_Out";
			   this->button_Open_out->Text = L"Open Out";
			   this->button_Open_out->UseVisualStyleBackColor = false;
			   this->button_Open_out->Click += gcnew System::EventHandler(this, &Watermark::button_Open_out_Click);
			   // 
			   // button_Training
			   // 
			   this->button_Training->BackColor = System::Drawing::Color::Green;
			   this->button_Training->Enabled = false;
			   this->button_Training->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Training->Location = System::Drawing::Point(731, 67);
			   this->button_Training->Name = L"button_Training";
			   this->button_Training->Size = System::Drawing::Size(130, 30);
			   this->button_Training->TabIndex = 290;
			   this->button_Training->Tag = L"";
			   this->button_Training->Text = L"Training";
			   this->button_Training->UseVisualStyleBackColor = false;
			   this->button_Training->Click += gcnew System::EventHandler(this, &Watermark::button_Start_Click);
			   // 
			   // button1
			   // 
			   this->button1->BackColor = System::Drawing::Color::Green;
			   this->button1->Enabled = false;
			   this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button1->Location = System::Drawing::Point(731, 31);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(130, 30);
			   this->button1->TabIndex = 291;
			   this->button1->Tag = L"";
			   this->button1->Text = L"Learning";
			   this->button1->UseVisualStyleBackColor = false;
			   this->button1->Click += gcnew System::EventHandler(this, &Watermark::button1_Click);
			   // 
			   // button_Processing_Images
			   // 
			   this->button_Processing_Images->BackColor = System::Drawing::Color::Green;
			   this->button_Processing_Images->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold,
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->button_Processing_Images->Location = System::Drawing::Point(12, 84);
			   this->button_Processing_Images->Name = L"button_Processing_Images";
			   this->button_Processing_Images->Size = System::Drawing::Size(130, 30);
			   this->button_Processing_Images->TabIndex = 292;
			   this->button_Processing_Images->Tag = L"";
			   this->button_Processing_Images->Text = L"Start";
			   this->button_Processing_Images->UseVisualStyleBackColor = false;
			   this->button_Processing_Images->Click += gcnew System::EventHandler(this, &Watermark::button_Processing_Images_Click);
			   // 
			   // textBox_JPEG_Compression
			   // 
			   this->textBox_JPEG_Compression->Enabled = false;
			   this->textBox_JPEG_Compression->Location = System::Drawing::Point(536, 415);
			   this->textBox_JPEG_Compression->MaxLength = 4;
			   this->textBox_JPEG_Compression->Name = L"textBox_JPEG_Compression";
			   this->textBox_JPEG_Compression->Size = System::Drawing::Size(50, 20);
			   this->textBox_JPEG_Compression->TabIndex = 313;
			   this->textBox_JPEG_Compression->Text = L"40";
			   // 
			   // timer_display
			   // 
			   this->timer_display->Enabled = true;
			   this->timer_display->Tick += gcnew System::EventHandler(this, &Watermark::timer_display_Tick);
			   // 
			   // button_Stop_Processing_Images
			   // 
			   this->button_Stop_Processing_Images->BackColor = System::Drawing::Color::Green;
			   this->button_Stop_Processing_Images->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold,
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->button_Stop_Processing_Images->Location = System::Drawing::Point(12, 119);
			   this->button_Stop_Processing_Images->Name = L"button_Stop_Processing_Images";
			   this->button_Stop_Processing_Images->Size = System::Drawing::Size(130, 30);
			   this->button_Stop_Processing_Images->TabIndex = 314;
			   this->button_Stop_Processing_Images->Tag = L"";
			   this->button_Stop_Processing_Images->Text = L"Stop";
			   this->button_Stop_Processing_Images->UseVisualStyleBackColor = false;
			   this->button_Stop_Processing_Images->Click += gcnew System::EventHandler(this, &Watermark::button_Stop_Processing_Images_Click);
			   // 
			   // textBox_Learning_Size
			   // 
			   this->textBox_Learning_Size->Enabled = false;
			   this->textBox_Learning_Size->Location = System::Drawing::Point(448, 415);
			   this->textBox_Learning_Size->MaxLength = 4;
			   this->textBox_Learning_Size->Name = L"textBox_Learning_Size";
			   this->textBox_Learning_Size->Size = System::Drawing::Size(82, 20);
			   this->textBox_Learning_Size->TabIndex = 315;
			   this->textBox_Learning_Size->Text = L"1400_1120";
			   this->textBox_Learning_Size->TextChanged += gcnew System::EventHandler(this, &Watermark::textBox_Learning_Size_TextChanged);
			   // 
			   // dataGridView1
			   // 
			   this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			   this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(6) {
				   this->ID, this->Color_Front,
					   this->Color_Back, this->Window_Start, this->Window_Size, this->Image_Path
			   });
			   this->dataGridView1->Location = System::Drawing::Point(12, 174);
			   this->dataGridView1->Name = L"dataGridView1";
			   this->dataGridView1->Size = System::Drawing::Size(893, 235);
			   this->dataGridView1->TabIndex = 322;
			   this->dataGridView1->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Watermark::dataGridView1_CellContentClick);
			   // 
			   // ID
			   // 
			   this->ID->HeaderText = L"ID";
			   this->ID->Name = L"ID";
			   // 
			   // Color_Front
			   // 
			   this->Color_Front->HeaderText = L"Color_Front";
			   this->Color_Front->Name = L"Color_Front";
			   // 
			   // Color_Back
			   // 
			   this->Color_Back->HeaderText = L"Color_Back";
			   this->Color_Back->Name = L"Color_Back";
			   // 
			   // Window_Start
			   // 
			   this->Window_Start->HeaderText = L"Window_Start";
			   this->Window_Start->Name = L"Window_Start";
			   // 
			   // Window_Size
			   // 
			   this->Window_Size->HeaderText = L"Window_Size";
			   this->Window_Size->Name = L"Window_Size";
			   // 
			   // Image_Path
			   // 
			   this->Image_Path->HeaderText = L"Image_Path";
			   this->Image_Path->Name = L"Image_Path";
			   // 
			   // button_Save_DataGrid
			   // 
			   this->button_Save_DataGrid->BackColor = System::Drawing::Color::Green;
			   this->button_Save_DataGrid->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Save_DataGrid->Location = System::Drawing::Point(595, 67);
			   this->button_Save_DataGrid->Name = L"button_Save_DataGrid";
			   this->button_Save_DataGrid->Size = System::Drawing::Size(130, 30);
			   this->button_Save_DataGrid->TabIndex = 323;
			   this->button_Save_DataGrid->Tag = L"";
			   this->button_Save_DataGrid->Text = L"Save";
			   this->button_Save_DataGrid->UseVisualStyleBackColor = false;
			   this->button_Save_DataGrid->Click += gcnew System::EventHandler(this, &Watermark::button_Save_DataGrid_Click);
			   // 
			   // button_Read_To_DataGrid
			   // 
			   this->button_Read_To_DataGrid->BackColor = System::Drawing::Color::Green;
			   this->button_Read_To_DataGrid->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold,
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->button_Read_To_DataGrid->Location = System::Drawing::Point(595, 31);
			   this->button_Read_To_DataGrid->Name = L"button_Read_To_DataGrid";
			   this->button_Read_To_DataGrid->Size = System::Drawing::Size(130, 30);
			   this->button_Read_To_DataGrid->TabIndex = 324;
			   this->button_Read_To_DataGrid->Tag = L"";
			   this->button_Read_To_DataGrid->Text = L"Read";
			   this->button_Read_To_DataGrid->UseVisualStyleBackColor = false;
			   this->button_Read_To_DataGrid->Click += gcnew System::EventHandler(this, &Watermark::button_Read_To_DataGrid_Click);
			   // 
			   // openFileDialog1
			   // 
			   this->openFileDialog1->FileName = L"openFileDialog1";
			   // 
			   // button_Copy_Image
			   // 
			   this->button_Copy_Image->BackColor = System::Drawing::Color::Green;
			   this->button_Copy_Image->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button_Copy_Image->Location = System::Drawing::Point(620, 415);
			   this->button_Copy_Image->Name = L"button_Copy_Image";
			   this->button_Copy_Image->Size = System::Drawing::Size(130, 30);
			   this->button_Copy_Image->TabIndex = 325;
			   this->button_Copy_Image->Tag = L"";
			   this->button_Copy_Image->Text = L"Copy Image";
			   this->button_Copy_Image->UseVisualStyleBackColor = false;
			   this->button_Copy_Image->Click += gcnew System::EventHandler(this, &Watermark::button_Copy_Image_Click);
			   // 
			   // Watermark
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->AutoSize = true;
			   this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			   this->ClientSize = System::Drawing::Size(996, 457);
			   this->Controls->Add(this->button_Copy_Image);
			   this->Controls->Add(this->button_Read_To_DataGrid);
			   this->Controls->Add(this->button_Save_DataGrid);
			   this->Controls->Add(this->dataGridView1);
			   this->Controls->Add(this->textBox_Learning_Size);
			   this->Controls->Add(this->button_Stop_Processing_Images);
			   this->Controls->Add(this->textBox_JPEG_Compression);
			   this->Controls->Add(this->button_Processing_Images);
			   this->Controls->Add(this->button1);
			   this->Controls->Add(this->button_Training);
			   this->Controls->Add(this->label_Open_out);
			   this->Controls->Add(this->button_Open_out);
			   this->Controls->Add(this->label_Open_in);
			   this->Controls->Add(this->button_Open_in);
			   this->Name = L"Watermark";
			   this->Text = L"Watermark";
			   this->Load += gcnew System::EventHandler(this, &Watermark::Watermark_Load);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
	public: void Get_Settings(void)
	{
		compression = Convert::ToInt32(textBox_JPEG_Compression->Text, CultureInfo::InvariantCulture);
	}


	public: void Show_Settings(void)
	{
		textBox_JPEG_Compression->Text = Convert::ToString(compression, CultureInfo::InvariantCulture);
	}


	public: void Enable_Disable_All(bool state)
	{
		Enable_Disable_All_Button(state);
		textBox_JPEG_Compression->Enabled = state;
		textBox_Learning_Size->Enabled = state;

	}


	public: void Enable_Disable_All_Button(bool state)
	{
		Enable_Disable_Button(button_Open_in, state);
		Enable_Disable_Button(button_Open_out, state);
		Enable_Disable_Button(button_Processing_Images, state);
#if (_DEBUG == 1)
		Enable_Disable_Button(button_Training, state);
		Enable_Disable_Button(button1, state);
#endif
	}
	private: System::Void Enable_Disable_Button(System::Object^ sender, bool state) {
		System::Windows::Forms::Button^ button;
		button = (System::Windows::Forms::Button^) sender;

		if (state) {
			button->Enabled = true;
			button->BackColor = System::Drawing::Color::FromName("Green");
		}
		else {
			button->Enabled = false;
			button->BackColor = System::Drawing::Color::FromName("Gray");
		}

	}
	private: System::Void button_Open_in_Click(System::Object^ sender, System::EventArgs^ e) {
		// Show the FolderBrowserDialog.
		//folderBrowserDialog_In->ShowDialog();
		System::Windows::Forms::DialogResult result = folderBrowserDialog_In->ShowDialog();
		if (result == System::Windows::Forms::DialogResult::OK)
		{
			folderName_In = folderBrowserDialog_In->SelectedPath;
			label_Open_in->Text = folderName_In;
			Open_in = (TCHAR*)Marshal::StringToHGlobalUni(folderName_In).ToPointer();
			Console::WriteLine(folderName_In);
		}


	}
	private: System::Void button_Open_out_Click(System::Object^ sender, System::EventArgs^ e) {
		System::Windows::Forms::DialogResult result = folderBrowserDialog_In->ShowDialog();
		if (result == System::Windows::Forms::DialogResult::OK)
		{
			folderName_Out = folderBrowserDialog_In->SelectedPath;
			label_Open_out->Text = folderName_Out;
			Open_out = (TCHAR*)Marshal::StringToHGlobalUni(folderName_Out).ToPointer();
			Console::WriteLine(folderName_Out);
		}
		}
	private: System::Void Watermark_Load(System::Object^ sender, System::EventArgs^ e) {
#if (_DEBUG == 1)
		Enable_Disable_All(true);
#endif
#if (_TEST != 1)
		char* size = (char*)(void*)Marshal::StringToHGlobalAnsi(textBox_Learning_Size->Text);
#endif

	}
	private: System::Void button_Start_Click(System::Object^ sender, System::EventArgs^ e) {
		Enable_Disable_All_Button(false);
		Get_Settings();
		hThread_Watermark_Processing = CreateThread(NULL, 0, WatermarkProcessingThreadFunction, 0, 0, NULL);
		if (hThread_Watermark_Processing == NULL)
		{
			ErrorHandler(TEXT("CreateThread hThread_Watermark_Processing"));
			ExitProcess(3);
		}

		// now wait for thread to signal termination
		//WaitForSingleObject(hThread_Watermark_Processing, INFINITE);

		//Enable_Disable_All_Button(true);
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		Enable_Disable_All_Button(false);
		Get_Settings();
		LogoLearning dt[10];
		int step;

		step = Parse_DataGrid(dataGridView1, dt, 1);
		Shadow_Learning(dt, step);
		step = Parse_DataGrid(dataGridView1, dt, 2);
		Text_Learning(Image_Size, dt, step);

		//Save_White((char*)(void*)Marshal::StringToHGlobalAnsi(textBox_Learning_Size->Text));
		Enable_Disable_All_Button(true);
	}
	private: System::Void button_Processing_Images_Click(System::Object^ sender, System::EventArgs^ e) {
		enable_stop_processing_images = true;
		exit_image_processing = false;
		Enable_Disable_All_Button(false);
		Get_Settings();
		//Read_Shadow();

		if ((label_Open_in->Text == "Выбирете папку") || (label_Open_out->Text == "Выбирете папку")) {
			//path_in = "D:\\ABITANT\\img_in";
			//path_out = "D:\\ABITANT\\img_out";
			path_in = "D:\\ABITANT\\img_in\\Jonathan Charles Fine Furniture\\Jonathan Charles Fine Furniture";
			path_out = "D:\\ABITANT\\img_in\\Jonathan Charles Fine Furniture\\Jonathan Charles Fine Furniture Out";

		}
		else {
			path_in = (char*)(void*)Marshal::StringToHGlobalAnsi(label_Open_in->Text);
			path_out = (char*)(void*)Marshal::StringToHGlobalAnsi(label_Open_out->Text);
		}

		size_t convertedChars = 0;
		size_t newsize = strlen(path_in) + 1;
		wchar_t* wcstring_in = new wchar_t[newsize];
		mbstowcs_s(&convertedChars, wcstring_in, newsize, path_in, _TRUNCATE);
		newsize = strlen(path_out) + 1;
		wchar_t* wcstring_out = new wchar_t[newsize];
		mbstowcs_s(&convertedChars, wcstring_out, newsize, path_out, _TRUNCATE);

		hThread_Image_Processing = CreateThread(NULL, 0, ImageProcessingThreadFunction, 0, 0, NULL);
		if (hThread_Image_Processing == NULL)
		{
			ErrorHandler(TEXT("CreateThread hThread_Watermark_Processing"));
			ExitProcess(3);
		}

		//Image_Processing(wcstring_in, wcstring_out, process_contour_back, process_contour_front);
		//Enable_Disable_All_Button(true);
	}
	private: System::Void button_Settings_Save_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button_Settings_Open_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void timer_display_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (enable_all_button) {
			Enable_Disable_All_Button(true);
			enable_all_button = false;
		}
		if (enable_stop_processing_images) {
			Enable_Disable_Button(button_Stop_Processing_Images, true);
		}
		else {
			Enable_Disable_Button(button_Stop_Processing_Images, false);

		}
		timer_display->Enabled = true;
	}
	private: System::Void button_Stop_Processing_Images_Click(System::Object^ sender, System::EventArgs^ e) {
		exit_image_processing = true;
	}
	private: System::Void button_Learning_Shadow_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox_Learning_Size_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button_Learning_Artifact_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
	}

	private: System::Void button_Save_DataGrid_Click(System::Object^ sender, System::EventArgs^ e) {

		//saveFileDialog1->Title = "Save as Excel File";
		//saveFileDialog1->FileName = "";
		//saveFileDialog1->Filter = "Excel Files(2003)|*.xls|Excel Files(2007)|*.xlsx";
		//if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		//	Microsoft::Office::Interop::Excel::Application^ ExcelApp = gcnew Microsoft::Office::Interop::Excel::ApplicationClass();
		//	ExcelApp->Workbooks->Add(Type::Missing);
		//	for (int i = 1; i < dataGridView1->Columns->Count + 1; i++)
		//	{
		//		ExcelApp->Cells[1, i] = dataGridView1->Columns[i - 1]->HeaderText;
		//	}
		//	for (int i = 0; i < dataGridView1->Rows->Count; i++)
		//	{
		//		for (int j = 0; j < dataGridView1->Columns->Count; j++)
		//		{
		//			ExcelApp->Cells[i + 2, j + 1] = dataGridView1->Rows[i]->Cells[j]->Value;
		//			safe_cast<Range^>(ExcelApp->Cells[i + 2, j + 1]);
		//		}
		//	}
		//	ExcelApp->ActiveWorkbook->SaveCopyAs(saveFileDialog1->FileName->ToString());
		//	ExcelApp->ActiveWorkbook->Saved = true;
		//	ExcelApp->Quit();
		//}


		saveFileDialog1->Title = "Save as Excel File";
		saveFileDialog1->FileName = "";
		saveFileDialog1->Filter = "DAT Files | *.dat";
		//if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			//String^ filename = openFileDialog1->FileName;
		String^ filename = "D:\\ABITANT\\Soft\\Watermark\\Watermark\\Settings\\" + Image_Size + ".dat";
		List<System::String^>^ list_rows = gcnew List<System::String^>();
		//List<System::String^>^ list_colls = gcnew List<System::String^>();
		//for (int i = 1; i < dataGridView1->Columns->Count + 1; i++)
		//{
		//	list_colls->Add(dataGridView1->Columns[i - 1]->HeaderText + "|");
		//}
		//for (int idx = 0; idx < list_colls->Count; idx++) temp += list_colls[idx];
		//list_rows->Add(temp);
		System::String^ temp;
		for (int i = 0; i < dataGridView1->Rows->Count; i++)
		{
			List<System::String^>^ list_colls = gcnew List<System::String^>();
			temp = "";
			if (dataGridView1->Rows[i]->Cells[0]->Value == nullptr) {
				//Console::WriteLine("SSSSSSS");
				continue;
			}
			for (int j = 0; j < dataGridView1->Columns->Count; j++)
			{
				list_colls->Add(dataGridView1->Rows[i]->Cells[j]->Value + "|");
				//ExcelApp->Cells[i + 2, j + 1] = dataGridView1->Rows[i]->Cells[j]->Value;
				//safe_cast<Range^>(ExcelApp->Cells[i + 2, j + 1]);
			}
			for (int idx = 0; idx < list_colls->Count; idx++) temp += list_colls[idx];
			list_rows->Add(temp);
		}

		System::String^ path = filename;
		// This text is added only once to the file.
		if (File::Exists(path))
		{
			File::WriteAllLines(path, list_rows);
		}

		//}


	}



	private: System::Void button_Read_To_DataGrid_Click(System::Object^ sender, System::EventArgs^ e) {
		//using namespace Microsoft::Office::Interop::Excel;
		//openFileDialog1->Title = "Open Excel File";
		//openFileDialog1->FileName = "";
		//openFileDialog1->Filter = "Excel Files(2003)|*.xls|Excel Files(2007)|*.xlsx";
		//openFileDialog1->InitialDirectory = "Desktop"; //define the initial directory
		////if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		//	//String^ filename = openFileDialog1->FileName;
		//String^ filename = "D:\\ABITANT\\Soft\\Watermark\\Watermark\\Settings\\" + Image_Size + ".xls";
		//Microsoft::Office::Interop::Excel::Application^ ExcelApp = gcnew Microsoft::Office::Interop::Excel::ApplicationClass();
		//Workbook^ wb = ExcelApp->Workbooks->Open(filename, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing);
		//Worksheet^ Sheet = (Microsoft::Office::Interop::Excel::Worksheet^)ExcelApp->ActiveSheet;
		//Microsoft::Office::Interop::Excel::Range^ Range;
		//Microsoft::Office::Interop::Excel::Range^ Cell;
		//Range = Sheet->Cells;
		//String^ value;
		////ExcelApp->Workbooks->Open("D:\\1.xls");
		//for (int i = 1; i < dataGridView1->Columns->Count + 1; i++)
		//{
		//	//dataGridView1->Columns[i - 1]->HeaderText = ExcelApp->Cells[1, i];
		//}

		//int count_rows = dataGridView1->Rows->Count;
		//for (int i = 0; i < count_rows - 1; i++)
		//{
		//	dataGridView1->Rows->RemoveAt(0);
		//}
		//int x = 0;
		//do {
		//	Cell = (Microsoft::Office::Interop::Excel::Range^)Range->Item[x + 2, 1];
		//	x++;
		//	if (Cell->Value[nullptr] != nullptr)
		//	{
		//		dataGridView1->Rows->Add();
		//	}
		//} while (Cell->Value[nullptr] != nullptr);

		//for (int i = 0; i < dataGridView1->Rows->Count - 1; i++)
		//{
		//	for (int j = 0; j < dataGridView1->Columns->Count; j++)
		//	{
		//		Cell = (Microsoft::Office::Interop::Excel::Range^)Range->Item[i + 2, j + 1];
		//		if (Cell->Value[nullptr] != nullptr)
		//		{
		//			//contain value
		//			value = Cell->Value[nullptr]->ToString();
		//			value = Cell->Value2->ToString();
		//			dataGridView1->Rows[i]->Cells[j]->Value = value;
		//		}
		//	}
		//}
		//ExcelApp->Quit();
		//dataGridView1->Refresh();
		////}


		openFileDialog1->Title = "Open DAT File";
		openFileDialog1->FileName = "";
		openFileDialog1->Filter = "DAT Files | *.dat";
		openFileDialog1->InitialDirectory = "Desktop"; //define the initial directory
		//if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		//String^ filename = openFileDialog1->FileName;
		String^ filename = "D:\\ABITANT\\Soft\\Watermark\\Watermark\\Settings\\" + Image_Size + ".dat";
		String^ value;
		int count_rows = dataGridView1->Rows->Count;
		for (int i = 0; i < count_rows - 1; i++)
		{
			dataGridView1->Rows->RemoveAt(0);
		}

		cli::array<System::String^>^ list_rows;
		cli::array<System::String^>^ list_colls;
		// Open the file to read from.
		list_rows = File::ReadAllLines(filename);
		dataGridView1->Rows->Add(list_rows->Length); //первую строку с названием столбцов не включаем

		for (int i = 0; i < list_rows->Length; i++)
		{
			list_colls = list_rows[i]->Split('|');
			for (int j = 0; j < dataGridView1->Columns->Count; j++)
			{
				String^ Cell = list_colls[j];
				dataGridView1->Rows[i]->Cells[j]->Value = Cell;
			}
		}
		dataGridView1->Refresh();
		//}

	}
	private: System::Void button_Copy_Image_Click(System::Object^ sender, System::EventArgs^ e) {

		path_in = (char*)(void*)Marshal::StringToHGlobalAnsi(label_Open_in->Text);
		path_out = (char*)(void*)Marshal::StringToHGlobalAnsi(label_Open_out->Text);


		hThread_CopyImage = CreateThread(NULL, 0, CopyImageThreadFunction, 0, 0, NULL);
		if (hThread_CopyImage == NULL)
		{
			ErrorHandler(TEXT("CreateThread hThread_CopyImage"));
			ExitProcess(3);
		}
	}
	};
	}


//try
//{
//	OpenFileDialog openFileDialog1 = new OpenFileDialog();  //create openfileDialog Object
//	openFileDialog1.Filter = "XML Files (*.xml; *.xls; *.xlsx; *.xlsm; *.xlsb) |*.xml; *.xls; *.xlsx; *.xlsm; *.xlsb";//open file format define Excel Files(.xls)|*.xls| Excel Files(.xlsx)|*.xlsx| 
//	openFileDialog1.FilterIndex = 3;
//
//	openFileDialog1.Multiselect = false;        //not allow multiline selection at the file selection level
//	openFileDialog1.Title = "Open Text File-R13";   //define the name of openfileDialog
//	openFileDialog1.InitialDirectory = @"Desktop"; //define the initial directory
//
//		if (openFileDialog1.ShowDialog() == DialogResult.OK)        //executing when file open
//		{
//			string pathName = openFileDialog1.FileName;
//			fileName = System.IO.Path.GetFileNameWithoutExtension(openFileDialog1.FileName);
//			DataTable tbContainer = new DataTable();
//			string strConn = string.Empty;
//			string sheetName = fileName;
//
//			FileInfo file = new FileInfo(pathName);
//			if (!file.Exists) { throw new Exception("Error, file doesn't exists!"); }
//			string extension = file.Extension;
//			switch (extension)
//			{
//			case ".xls":
//				strConn = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + pathName + ";Extended Properties='Excel 8.0;HDR=Yes;IMEX=1;'";
//				break;
//			case ".xlsx":
//				strConn = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=" + pathName + ";Extended Properties='Excel 12.0;HDR=Yes;IMEX=1;'";
//				break;
//			default:
//				strConn = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + pathName + ";Extended Properties='Excel 8.0;HDR=Yes;IMEX=1;'";
//				break;
//			}
//			OleDbConnection cnnxls = new OleDbConnection(strConn);
//			OleDbDataAdapter oda = new OleDbDataAdapter(string.Format("select * from [{0}$]", sheetName), cnnxls);
//			oda.Fill(tbContainer);
//
//			dtGrid.DataSource = tbContainer;
//		}
//
//}
//catch (Exception)
//{
//	MessageBox.Show("Error!");
//}