//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <string>

#include "Unit1.h"
#include "IntroOps.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
#include <vector.h>
#include <string.h>
#include <sysutils.hpp>

vector<string> v;

//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormCreate(TObject *Sender)
{
        ComboBoxSelectTable->Items->Add("SHIPS");
        ComboBoxSelectTable->Items->Add("GATEWAYS");
        ComboBoxSelectTable->Items->Add("PLACES");
        ComboBoxSelectTable->Items->Add("PLACEMENT");
        ComboBoxSelectTable->Items->Add("SCHEDULE");
        ComboBoxSelectTable->Items->Add("SITES");
}
//---------------------------------------------------------------------------
//`load` button 
void __fastcall TFormMain::ButtonLoadClick(TObject *Sender)
{
        IBQuery1->Active = false;
        DataSource1->DataSet = IBTable1;

        ComboBoxSelectTable->SetFocus();
        AnsiString s = ComboBoxSelectTable->SelText;
        if(s != "select table")
        {
                IBTable1->Active = false;
                IBTransactionMain->Active = false;
                IBTable1->TableName = s;
                IBTable1->Open();
                IBTransactionMain->Active = true;
         }
        else throw Exception("select table");
}
//---------------------------------------------------------------------------
//кнопка "Выполнить запрос"
void __fastcall TFormMain::ButtonExecuteClick(TObject *Sender)
{
        //подготавливаем запрос
        IBQuery1->Active = false;
        IBQuery1->SQL->Clear();
        AnsiString Q = MemoEnterQuery->Text;
        IBQuery1->SQL->Append(Q);
        DataSource1->DataSet = IBQuery1;

        //в зависимости от контекста, по-разному обрабатываем запрос
        string* stmp = new string(Q.c_str());
        unsigned int it1;
        it1 = stmp->find("SELECT", 0);
        if(it1 < stmp->length()) IBQuery1->Open();
        else
        {
            IBQuery1->ExecSQL();
            IBTransactionMain->Commit();
        }
        delete stmp;

        //отображаем результаты запроса (если есть)
        IBTransactionMain->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonReserveClick(TObject *Sender)
{
	IBStoredProcReserve->Active = false;
    DlgReserve->ShowModal();

    //Устанавливаем параметры
    TParam* tmpParam = new TParam(NULL);

    tmpParam = IBStoredProcReserve->Params->ParamByName("ARRIVAL_DATE");
    tmpParam->AsDate = StrToDate(DlgReserve->EditArrival->Text);
    tmpParam = IBStoredProcReserve->Params->ParamByName("DEPARTURE_DATE");
    tmpParam->AsDate = StrToDate(DlgReserve->EditDeparture->Text);
    tmpParam = IBStoredProcReserve->Params->ParamByName("FREE_PLACES_LOWER_LIM");
    tmpParam->AsInteger = StrToIntDef(DlgReserve->EditLimit->Text, -1);
	tmpParam = IBStoredProcReserve->Params->ParamByName("HEIGHT");
    tmpParam->AsFloat = StrToFloat(DlgReserve->EditHeight->Text);
    tmpParam = IBStoredProcReserve->Params->ParamByName("LENGTH");
    tmpParam->AsFloat = StrToFloat(DlgReserve->EditLength->Text);
    tmpParam = IBStoredProcReserve->Params->ParamByName("WIDTH");
    tmpParam->AsFloat = StrToFloat(DlgReserve->EditWidth->Text);
    tmpParam = IBStoredProcReserve->Params->ParamByName("SHAPE");
    tmpParam->AsString = DlgReserve->EditShape->Text;
    tmpParam = IBStoredProcReserve->Params->ParamByName("NEEDS_SERVICE");
    tmpParam->AsString = DlgReserve->EditService->Text;
    tmpParam = IBStoredProcReserve->Params->ParamByName("GATEWAYID");
    tmpParam->AsInteger = StrToIntDef(DlgReserve->EditGatewayID->Text, -1);
    tmpParam = IBStoredProcReserve->Params->ParamByName("NAME");
    tmpParam->AsString = DlgReserve->EditName->Text;

    //Запускаем
    IBStoredProcReserve->Prepare();
    IBStoredProcReserve->ExecProc();
    IBTransactionMain->Commit();
    tmpParam = IBStoredProcReserve->Params->ParamByName("ANSWER");
    AnsiString sAnswer = tmpParam->AsString;

    //Вывод информации
    Application->MessageBox(sAnswer.c_str(), "Answer", MB_OK);

    //Завершение, очистка
  	IBStoredProcReserve->UnPrepare();
    tmpParam = NULL;
    delete tmpParam;

}
//---------------------------------------------------------------------------


void __fastcall TFormMain::ButtonCloseClick(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormShow(TObject *Sender)
{
	IntroForm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonCancelClick(TObject *Sender)
{
	IBStoredProcCancel->Active = false;

    if(this->EditShipName->Text != "Введите имя корабля")
    {
    	//Устанавливаем параметры
    	TParam* tmpParam = new TParam(NULL);
    	tmpParam = IBStoredProcCancel->Params->ParamByName("SHIPNAME");
    	tmpParam->AsString = this->EditShipName->Text;

   	    //Запускаем
   		IBStoredProcCancel->Prepare();
    	IBStoredProcCancel->ExecProc();
    	IBTransactionMain->Commit();

    	//Завершение, очистка
  		IBStoredProcCancel->UnPrepare();
    	tmpParam = NULL;
    	delete tmpParam;
    }
    else Application->MessageBox("Введите имя корабля!", "Answer", MB_OK);

}
//---------------------------------------------------------------------------
void __fastcall TFormMain::DBNavigator1Click(TObject *Sender, TNavigateBtn Button)
{
  	if (Button == nbPost)
    {
    	IBTransactionMain->Commit();
    	IBTable1->Open();
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonArrivalClick(TObject *Sender)
{
	IBStoredProcReserve->Active = false;
    DlgReserve->ShowModal();
    DlgReserve->EditLimit->Visible = false;

    //Устанавливаем параметры
    TParam* tmpParam = new TParam(NULL);

    tmpParam = IBStoredProcReserve->Params->ParamByName("ARRIVAL_DATE");
    tmpParam->AsDate = StrToDate(DlgReserve->EditArrival->Text);
    tmpParam = IBStoredProcReserve->Params->ParamByName("DEPARTURE_DATE");
    tmpParam->AsDate = StrToDate(DlgReserve->EditDeparture->Text);
	tmpParam = IBStoredProcReserve->Params->ParamByName("HEIGHT");
    tmpParam->AsFloat = StrToFloat(DlgReserve->EditHeight->Text);
    tmpParam = IBStoredProcReserve->Params->ParamByName("LENGTH");
    tmpParam->AsFloat = StrToFloat(DlgReserve->EditLength->Text);
    tmpParam = IBStoredProcReserve->Params->ParamByName("WIDTH");
    tmpParam->AsFloat = StrToFloat(DlgReserve->EditWidth->Text);
    tmpParam = IBStoredProcReserve->Params->ParamByName("SHAPE");
    tmpParam->AsString = DlgReserve->EditShape->Text;
    tmpParam = IBStoredProcReserve->Params->ParamByName("NEEDS_SERVICE");
    tmpParam->AsString = DlgReserve->EditService->Text;
    tmpParam = IBStoredProcReserve->Params->ParamByName("GATEWAYID");
    tmpParam->AsInteger = StrToIntDef(DlgReserve->EditGatewayID->Text, -1);
    tmpParam = IBStoredProcReserve->Params->ParamByName("NAME");
    tmpParam->AsString = DlgReserve->EditName->Text;
    tmpParam = IBStoredProcReserve->Params->ParamByName("FREE_PLACES_LOWER_LIM");
    tmpParam->AsInteger = StrToIntDef("-1", -1);

    //Запускаем
    IBStoredProcReserve->Prepare();
    IBStoredProcReserve->ExecProc();
    IBTransactionMain->Commit();
    tmpParam = IBStoredProcReserve->Params->ParamByName("ANSWER");
    AnsiString sAnswer = tmpParam->AsString;

    //Вывод информации
    Application->MessageBox(sAnswer.c_str(), "Answer", MB_OK);

    //Завершение, очистка
  	IBStoredProcReserve->UnPrepare();
    tmpParam = NULL;
    delete tmpParam;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ButtonDepartureClick(TObject *Sender)
{
	IBStoredProcCancel->Active = false;

    if(this->EditShipName->Text != "Введите имя корабля")
    {
    	//Устанавливаем параметры
    	TParam* tmpParam = new TParam(NULL);
    	tmpParam = IBStoredProcCancel->Params->ParamByName("SHIPNAME");
    	tmpParam->AsString = this->EditShipName->Text;

   	    //Запускаем
   		IBStoredProcCancel->Prepare();
    	IBStoredProcCancel->ExecProc();
    	IBTransactionMain->Commit();

    	//Завершение, очистка
  		IBStoredProcCancel->UnPrepare();
    	tmpParam = NULL;
    	delete tmpParam;
    }
    else Application->MessageBox("Введите имя корабля!", "Answer", MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonTimeClick(TObject *Sender)
{
	IBStoredProcTimeTax->Active = false;

    //Устанавливаем параметры
    TParam* tmpParam = new TParam(NULL);

	tmpParam = IBStoredProcTimeTax->Params->ParamByName("DAILYTAX");
    tmpParam->AsFloat = StrToFloat(this->EditTax->Text);
    tmpParam = IBStoredProcTimeTax->Params->ParamByName("SHIPNAME");
    tmpParam->AsString = this->EditShipName->Text;

    //Запускаем
    IBStoredProcTimeTax->Prepare();
    IBStoredProcTimeTax->ExecProc();
    IBTransactionMain->Commit();
    tmpParam = IBStoredProcTimeTax->Params->ParamByName("PARKINGTIME");
    int time = tmpParam->AsInteger;
    tmpParam = IBStoredProcTimeTax->Params->ParamByName("PARKINGTAX");
    float tax = tmpParam->AsFloat;

    AnsiString sAnswer = "Такса: ";
    sAnswer += AnsiString::FormatFloat("0.00", (const long double)tax);
    sAnswer += "; количество дней: ";
    sAnswer += AnsiString(time);

    //Вывод информации
    Application->MessageBox(sAnswer.c_str(), "Answer", MB_OK);

    //Завершение, очистка
  	IBStoredProcTimeTax->UnPrepare();
    tmpParam = NULL;
    delete tmpParam;
}
//---------------------------------------------------------------------------

