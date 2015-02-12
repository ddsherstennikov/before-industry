//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "IntroOps.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TIntroForm *IntroForm;
//---------------------------------------------------------------------------
__fastcall TIntroForm::TIntroForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TIntroForm::FormPaint(TObject *Sender)
{
 FormMain->Hide();
 Timer1->Enabled = TRUE;
}
//---------------------------------------------------------------------------
void __fastcall TIntroForm::Timer1Timer(TObject *Sender)
{
 Timer1->Enabled = FALSE;
 FormMain->Show();
 IntroForm->Close();
}
//---------------------------------------------------------------------------

