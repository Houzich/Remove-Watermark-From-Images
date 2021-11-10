#include "Watermark.h"
#include "Watermark_Processing.h"
#include "Learning.h"
#include <iostream>
#include <conio.h>

#include <stdlib.h>
#include <string.h>
#include <msclr\marshal_cppstd.h>


using std::vector;



using namespace System;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace msclr::interop;
using namespace System::IO;
using namespace System::Collections::Generic;

#include <limits.h>


//float shadow[LOGO_HEIGHT][LOGO_WIDTH][3];
//float artifact[LOGO_HEIGHT][LOGO_WIDTH][3];

int compression;
bool enable_all_button;
char *path_in;
char *path_out;
bool exit_image_processing = false;
bool enable_stop_processing_images = false;
TCHAR* Open_in;
TCHAR* Open_out;
string Image_Size_std;


//template<char delimiter>
//class WordDelimitedBy : public std::string{};
//std::vector<std::string> split(std::string str) {
//	std::istringstream iss(str);
//	std::vector<std::string> results((std::istream_iterator<WordDelimitedBy<','>>(iss)),
//	std::istream_iterator<WordDelimitedBy<','>>());
//	return results;
//}


vector<string> split(string str) {
	vector<string> result;
	stringstream s_stream(str); //create string stream from the string
	while (s_stream.good()) {
		string substr;
		getline(s_stream, substr, ';'); //get first string delimited by comma
		result.push_back(substr);
	}
	return result;
}

[STAThreadAttribute]
void Main(void) {

	if (sizeof(float) * CHAR_BIT != 32) {
		printf("ERROR FLOAT\n");
		return;
	}
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Watermark::Watermark form;
	Application::Run(%form);
}


int Parse_DataGrid(System::Object^ sender, LogoLearning* dt, int id) {
	System::Windows::Forms::DataGridView^ datagrid;
	datagrid = (System::Windows::Forms::DataGridView^) sender;
	string str[5];
	int step = 0;
	for (int i = 0; i < datagrid->Rows->Count - 1; i++)
	{
		string id_str = marshal_as<std::string>(datagrid->Rows[i]->Cells["ID"]->Value->ToString());
		int id_int = atoi(id_str.c_str());
		if (((id == 1)&&(id_int == 1))||((id == 2) && (id_int == 2))) {

			str[0] = marshal_as<std::string>(datagrid->Rows[i]->Cells["Color_Front"]->Value->ToString());
			str[1] = marshal_as<std::string>(datagrid->Rows[i]->Cells["Color_Back"]->Value->ToString());
			str[2] = marshal_as<std::string>(datagrid->Rows[i]->Cells["Window_Start"]->Value->ToString());
			str[3] = marshal_as<std::string>(datagrid->Rows[i]->Cells["Window_Size"]->Value->ToString());
			str[4] = marshal_as<std::string>(datagrid->Rows[i]->Cells["Image_Path"]->Value->ToString());

			std::vector<std::string> color;
			//color.reserve(3);

			color = split(str[0]);
			dt[step].color_front[0] = (float)atof(color[0].c_str());
			dt[step].color_front[1] = (float)atof(color[1].c_str());
			dt[step].color_front[2] = (float)atof(color[2].c_str());

			color = split(str[1]);
			dt[step].color_back[0] = (float)atof(color[0].c_str());
			dt[step].color_back[1] = (float)atof(color[1].c_str());
			dt[step].color_back[2] = (float)atof(color[2].c_str());

			std::vector<std::string> coordinate;
			coordinate = split(str[2]);
			dt[step].window_col_start = atoi(coordinate[0].c_str());
			dt[step].window_row_start = atoi(coordinate[1].c_str());

			coordinate = split(str[3]);
			dt[step].window_width = atoi(coordinate[0].c_str());
			dt[step].window_height = atoi(coordinate[1].c_str());

			if (dt[step].window_col_start + dt[step].window_width > LOGO_WIDTH) printf("ERROR SIZE!!!!\r\n");
			if (dt[step].window_row_start + dt[step].window_height > LOGO_HEIGHT) printf("ERROR SIZE!!!!\r\n");

			dt[step].imageName = str[4];
			step++;
		}

	}
	return step;
}

int Parse_DataTable(System::Data::DataTable ^table, LogoLearning* dt, int id) {
	string str[5];
	int step = 0;
	for (int i = 0; i < table->Rows->Count; i++)
	{
		//row = table->Rows[i]);
		string id_str = marshal_as<std::string>((System::String^)((DataRow^)(table->Rows[i]))["ID"]);
		int id_int = atoi(id_str.c_str());
		if (((id == 1) && (id_int == 1)) || ((id == 2) && (id_int == 2))) {

			str[0] = marshal_as<std::string>((System::String^)((DataRow^)(table->Rows[i]))["Color_Front"]);
			str[1] = marshal_as<std::string>((System::String^)((DataRow^)(table->Rows[i]))["Color_Back"]);
			str[2] = marshal_as<std::string>((System::String^)((DataRow^)(table->Rows[i]))["Window_Start"]);
			str[3] = marshal_as<std::string>((System::String^)((DataRow^)(table->Rows[i]))["Window_Size"]);
			str[4] = marshal_as<std::string>((System::String^)((DataRow^)(table->Rows[i]))["Image_Path"]);

			std::vector<std::string> color;
			//color.reserve(3);

			color = split(str[0]);
			dt[step].color_front[0] = (float)atof(color[0].c_str());
			dt[step].color_front[1] = (float)atof(color[1].c_str());
			dt[step].color_front[2] = (float)atof(color[2].c_str());

			color = split(str[1]);
			dt[step].color_back[0] = (float)atof(color[0].c_str());
			dt[step].color_back[1] = (float)atof(color[1].c_str());
			dt[step].color_back[2] = (float)atof(color[2].c_str());

			std::vector<std::string> coordinate;
			coordinate = split(str[2]);
			dt[step].window_col_start = atoi(coordinate[0].c_str());
			dt[step].window_row_start = atoi(coordinate[1].c_str());

			coordinate = split(str[3]);
			dt[step].window_width = atoi(coordinate[0].c_str());
			dt[step].window_height = atoi(coordinate[1].c_str());

			if (dt[step].window_col_start + dt[step].window_width > LOGO_WIDTH) printf("ERROR SIZE!!!!\r\n");
			if (dt[step].window_row_start + dt[step].window_height > LOGO_HEIGHT) printf("ERROR SIZE!!!!\r\n");

			dt[step].imageName = str[4];
			step++;
		}

	}
	return step;
}

//void Read_Settings(String^ size, LogoLearning* dt1, LogoLearning* dt2, int *step1, int* step2) {
//		using namespace Microsoft::Office::Interop::Excel;
//
//		String^ filename = "D:\\ABITANT\\Soft\\Watermark\\Watermark\\Settings\\" + size + ".xls";
//		Microsoft::Office::Interop::Excel::Application^ ExcelApp = gcnew Microsoft::Office::Interop::Excel::ApplicationClass();
//		Workbook^ wb = ExcelApp->Workbooks->Open(filename, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing, Type::Missing);
//		Worksheet^ Sheet = (Microsoft::Office::Interop::Excel::Worksheet^)ExcelApp->ActiveSheet;
//		Microsoft::Office::Interop::Excel::Range^ Range;
//		Microsoft::Office::Interop::Excel::Range^ Cell;
//		Range = Sheet->Cells;
//		String^ value;
//
//		System::Data::DataTable data;
//		int x = 1;
//		do {
//			Cell = (Microsoft::Office::Interop::Excel::Range^)Range->Item[1, x++];
//			if (Cell->Value[nullptr] != nullptr)
//			{
//				//value = Cell->Value2->ToString();
//				data.Columns->Add(Cell->Value2->ToString());
//			}
//		} while (Cell->Value[nullptr] != nullptr);
//		
//		x = 2;
//		do {
//			Cell = (Microsoft::Office::Interop::Excel::Range^)Range->Item[x++, 1];
//			if (Cell->Value[nullptr] != nullptr)
//			{
//				data.Rows->Add();
//			}
//		} while (Cell->Value[nullptr] != nullptr);
//
//		for (int i = 0; i < data.Rows->Count; i++)
//		{
//			for (int j = 0; j < data.Columns->Count; j++)
//			{
//				Cell = (Microsoft::Office::Interop::Excel::Range^)Range->Item[i + 2, j + 1];
//				if (Cell->Value[nullptr] != nullptr)
//				{
//					value = Cell->Value2->ToString();
//					DataRow ^row = data.Rows[i];
//					row[j] = value;
//				}
//			}
//		}
//		ExcelApp->Quit();
//		*step1 = Parse_DataTable(data.Copy(), dt1, 1);
//		*step2 = Parse_DataTable(data.Copy(), dt2, 2);
//}



void Read_Settings(String^ size, LogoLearning* dt1, LogoLearning* dt2, int* step1, int* step2) {
#if (_DEBUG == 1)
	String^ filename = "D:\\ABITANT\\Soft\\Watermark\\Watermark\\Settings\\" + size + ".dat";
#else
	String^ filename = "Settings\\" + size + ".dat";
#endif
	
	//String^ filename = "D:\\ABITANT\\Soft\\Watermark\\Watermark\\Settings\\800x640.dat";
	System::Data::DataTable data;
	cli::array<System::String^>^ list_rows;
	cli::array<System::String^>^ list_colls;
	// Open the file to read from.
	list_rows = File::ReadAllLines(filename);
	list_colls = list_rows[0]->Split('|');
	data.Columns->Add("ID");
	data.Columns->Add("Color_Front");
	data.Columns->Add("Color_Back");
	data.Columns->Add("Window_Start");
	data.Columns->Add("Window_Size");
	data.Columns->Add("Image_Path");
	for (int i = 0; i < list_rows->Length; i++)data.Rows->Add();
	for (int i = 0; i < data.Rows->Count; i++)
	{
		list_colls = list_rows[i]->Split('|');
		for (int j = 0; j < data.Columns->Count; j++)
		{
			String^ value = list_colls[j];
			DataRow^ row = data.Rows[i];
			row[j] = value;
		}
	}
	*step1 = Parse_DataTable(data.Copy(), dt1, 1);
	*step2 = Parse_DataTable(data.Copy(), dt2, 2);
}