//---------------------------------------------------------------------------

#ifndef SubjOpsH
#define SubjOpsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ActnList.hpp>
#include <ListActns.hpp>
//---------------------------------------------------------------------------
class TSubjForm : public TForm
{
__published:	// IDE-managed Components
        TImageList *ImageList1;
        TTreeView *TreeView1;
private:	// User declarations
public:		// User declarations
        __fastcall TSubjForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSubjForm *SubjForm;
//---------------------------------------------------------------------------
#endif
