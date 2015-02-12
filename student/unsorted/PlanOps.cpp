//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FileOps.h"
#include "PlanOps.h"
#include "SubjOps.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGrid"
#pragma link "BaseGrid"
#pragma link "AdvGrid"
#pragma link "AdvGrid"
#pragma link "BaseGrid"
#pragma resource "*.dfm"
TPlanForm *PlanForm;
//---------------------------------------------------------------------------
__fastcall TPlanForm::TPlanForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPlanForm::AdvStringGrid1DblClickCell(TObject *Sender,
      int ARow, int ACol)
{
 Graphics::TBitmap *Bitmap1 = new Graphics::TBitmap();

 if ((ARow>AdvStringGrid1->FixedRows-1)&&(ACol>AdvStringGrid1->FixedCols-1))
     {if ( !AdvStringGrid1->GetBitmap(ACol, ARow) )
         {Bitmap1->LoadFromFile("C:\\Program Files\\Borland\\CBuilder6\\Projects\\IS_Primat\\PlanOps\\dot.bmp");
          AdvStringGrid1->AddBitmap(ACol, ARow, Bitmap1, FALSE, haCenter, vaCenter);}
      else AdvStringGrid1->RemoveBitmap(ACol, ARow);
     }
 else SubjForm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TPlanForm::Button1Click(TObject *Sender)
{
 ComboBox1->Visible;
 ComboBox1->Items->Add(SubjForm->TreeView1->Items->Item[0]->Text);
}
//---------------------------------------------------------------------------


