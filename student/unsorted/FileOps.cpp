//---------------------------------------------------------------------------
#include "DB.hpp"
#include <vcl.h>
#pragma hdrstop

#include "FileOps.h"
#include "PlanOps.h"
#include "SubjOps.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFileForm *FileForm;
//---------------------------------------------------------------------------
__fastcall TFileForm::TFileForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFileForm::FormCreate(TObject *Sender)
{
 IBDatabase1->Open();
 if(!IBTransaction1->Active) IBTransaction1->StartTransaction();
 IBTable1->Open();
}
//---------------------------------------------------------------------------
void __fastcall TFileForm::Button1Click(TObject *Sender)
{
 TFileStream *stream1;
 TBlobField *field1;
 AnsiString flname_input;
 int flkey_input;

 flkey_input = Edit1->Text.ToInt();
 flname_input = Edit2->Text;

 if(!IBTransaction1->Active) IBTransaction1->StartTransaction();
 IBTable1->Open();
 IBTable1->Insert();

 IBTable1->FieldByName("fl_id")->AsInteger = flkey_input;
 IBTable1->FieldByName("name")->AsString = flname_input;

 stream1 = new TFileStream(flname_input, bmReadWrite);
 field1 = (TBlobField*)IBTable1->FieldByName("file_obj");
 field1->LoadFromStream(stream1);

 IBTable1->Post();
 IBTransaction1->Commit();
}
//---------------------------------------------------------------------------
void __fastcall TFileForm::Button3Click(TObject *Sender)
{
 if(!IBTransaction2->Active) IBTransaction2->StartTransaction();
 IBQuery1->Params->Items[0]->AsString = Edit3->Text;
 IBQuery1->Open();
}
//---------------------------------------------------------------------------
void __fastcall TFileForm::Button2Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------
void __fastcall TFileForm::Button4Click(TObject *Sender)
{
 TBlobField* field1;

 ChDir("TMP");
 data = IBQuery1->FieldByName("name")->AsString;
 field1 = (TBlobField*)IBQuery1->FieldByName("file_obj");
 field1->SaveToFile(data);
}
//---------------------------------------------------------------------------
void __fastcall TFileForm::Button5Click(TObject *Sender)
{
 char* Path;

 Path = "C:\\Program Files\\Microsoft Office\\OFFICE11\\WINWORD.EXE";
 spawnlp(P_WAIT, Path, Path, data.c_str(), NULL);
}
//---------------------------------------------------------------------------


