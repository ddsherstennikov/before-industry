//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <string>

#include "Unit2.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
#include <vector.h>
#include <string.h>

extern vector<string> v;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
        Button2->Visible = false;
        ComboBox1->Items->Add("Text");
        ComboBox1->Items->Add("Volume");
        ComboBox1->Items->Add("Vol_Text");
        ComboBox1->Items->Add("Authors");
        ComboBox1->Items->Add("Au_Text");
        ComboBox1->Items->Add("Locat");
        ComboBox1->Items->Add("Vol_Loc");
        ComboBox1->Items->Add("Reader");
        ComboBox1->Items->Add("Reader_Vol");
        ComboBox1->Items->Add("Key_Word");

}
//---------------------------------------------------------------------------
//`load` button 
void __fastcall TForm1::Button1Click(TObject *Sender)
{
        IBQuery1->Active = false;
        DataSource1->DataSet = IBTable1;
        //IBTable1->Active = true;
        //IBTransaction1->Active = true;
        //IBQuery1->Active = true;

        ComboBox1->SetFocus();
        AnsiString s = ComboBox1->SelText;
        if(s != "select table")
        {
                IBTable1->Active = false;
                IBTransaction1->Active = false;
                IBTable1->TableName = s;
                IBTable1->Open();
                IBTransaction1->Active = true;
                if(s == "Volume") Button2->Visible = true;
                else Button2->Visible = false;
         }
        else throw Exception("select table");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
        Form2->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
        AnsiString s_id(v[0].c_str());
        AnsiString s_name(v[1].c_str());
        AnsiString s_num(v[2].c_str());
        AnsiString s_publ(v[3].c_str());
        AnsiString s_year(v[4].c_str());
        AnsiString s_n_all(v[5].c_str());
        AnsiString s_n_reader(v[6].c_str());
        AnsiString s_n_res(v[7].c_str());

        Memo1->Lines->Add(s_id);
        Memo1->Lines->Add(s_name);
        Memo1->Lines->Add(s_num);
        Memo1->Lines->Add(s_publ);
        Memo1->Lines->Add(s_year);
        Memo1->Lines->Add(s_n_all);
        Memo1->Lines->Add(s_n_reader);
        Memo1->Lines->Add(s_n_res);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
        AnsiString s_id(v[0].c_str());
        AnsiString s_name(v[1].c_str());
        AnsiString s_num(v[2].c_str());
        AnsiString s_publ(v[3].c_str());
        AnsiString s_year(v[4].c_str());
        AnsiString s_n_all(v[5].c_str());
        AnsiString s_n_reader(v[6].c_str());
        AnsiString s_n_res(v[7].c_str());
        AnsiString s_sys_idl(v[8].c_str());
        AnsiString s_sys_idt(v[9].c_str());

        IBQuery1->Active = false;
        IBQuery1->SQL->Clear();
        AnsiString Q = "INSERT INTO volume values (" +
                        s_id + ", '" + s_name + "', '" + s_num + "', '" + s_publ + "', " +
                        s_year + ", " + s_n_all + ", " + s_n_reader + ", " + s_n_res + ")";
        IBQuery1->SQL->Append(Q);
        AnsiString s1 = IBQuery1->SQL->Strings[0];
        Memo1->Lines->Add(s1);
        IBQuery1->ExecSQL();

        IBQuery1->Active = false;
        IBQuery1->SQL->Clear();
        Q = "INSERT INTO vol_loc values (" + s_id + ", " + s_sys_idl + ")";
        IBQuery1->SQL->Append(Q);
        s1 = IBQuery1->SQL->Strings[0];
        Memo1->Lines->Add(s1);
        IBQuery1->ExecSQL();

        IBQuery1->Active = false;
        IBQuery1->SQL->Clear();
        Q = "INSERT INTO vol_text values (" + s_sys_idt + ", " + s_id + ")";
        IBQuery1->SQL->Append(Q);
        s1 = IBQuery1->SQL->Strings[0];
        Memo1->Lines->Add(s1);
        IBQuery1->ExecSQL();

        IBTransaction1->Commit();
        IBTransaction1->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::IBTable1AfterDelete(TDataSet *DataSet)
{
        IBTransaction1->Commit();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
        IBTransaction1->Commit();

        IBQuery1->Active = false;
        IBQuery1->SQL->Clear();
        AnsiString Q;
        Q = "SELECT volume.sys_id, volume.vol_name, locat.sys_id, locat.room, locat.rack, locat.shelf FROM volume, locat, vol_loc WHERE vol_loc.sys_idv = volume.sys_id AND vol_loc.sys_idl = locat.sys_id";
        IBQuery1->SQL->Append(Q);
        AnsiString s1 = IBQuery1->SQL->Strings[0];
        Memo1->Lines->Add(s1);
        DataSource1->DataSet = IBQuery1;
        IBQuery1->Open();

        IBTransaction1->Active = true;;

}
//---------------------------------------------------------------------------


