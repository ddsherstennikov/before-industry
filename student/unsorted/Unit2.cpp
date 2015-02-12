//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector.h>
#include <string>
#pragma hdrstop

vector<string> v;

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button1Click(TObject *Sender)
{
        v.push_back(string(Edit1->Text.c_str()));
        v.push_back(string(Edit2->Text.c_str()));
        v.push_back(string(Edit3->Text.c_str()));
        v.push_back(string(Edit4->Text.c_str()));
        v.push_back(string(Edit5->Text.c_str()));
        v.push_back(string(Edit6->Text.c_str()));
        v.push_back(string(Edit7->Text.c_str()));
        v.push_back(string(Edit8->Text.c_str()));
        v.push_back(string(Edit9->Text.c_str()));
        v.push_back(string(Edit10->Text.c_str()));
        Close();
}
//---------------------------------------------------------------------------
