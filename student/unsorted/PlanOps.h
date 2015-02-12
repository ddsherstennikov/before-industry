//---------------------------------------------------------------------------

#ifndef PlanOpsH
#define PlanOpsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include <Graphics.hpp>
#include "AdvGrid.hpp"
#include "BaseGrid.hpp"
//---------------------------------------------------------------------------
class TPlanForm : public TForm
{
__published:	// IDE-managed Components
        TAdvStringGrid *AdvStringGrid1;
        TButton *Button1;
        TComboBox *ComboBox1;
        void __fastcall AdvStringGrid1DblClickCell(TObject *Sender,
          int ARow, int ACol);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TPlanForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPlanForm *PlanForm;
//---------------------------------------------------------------------------
#endif
