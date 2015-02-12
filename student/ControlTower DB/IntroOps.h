//---------------------------------------------------------------------------

#ifndef IntroOpsH
#define IntroOpsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TIntroForm : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TLabel *Label1;
        TLabel *Label2;
        TTimer *Timer1;
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TIntroForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TIntroForm *IntroForm;
//---------------------------------------------------------------------------
#endif
