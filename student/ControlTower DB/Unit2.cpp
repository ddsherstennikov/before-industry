//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDlgReserve *DlgReserve;
//---------------------------------------------------------------------------
__fastcall TDlgReserve::TDlgReserve(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDlgReserve::ButtonConfirmReservationClick(TObject *Sender)
{
	this->Close();	
}
//---------------------------------------------------------------------------

