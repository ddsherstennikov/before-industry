//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TDlgReserve : public TForm
{
__published:	// IDE-managed Components
	TEdit *EditName;
	TEdit *EditLimit;
	TEdit *EditHeight;
	TEdit *EditLength;
	TEdit *EditWidth;
	TEdit *EditShape;
	TEdit *EditGatewayID;
	TEdit *EditService;
	TButton *ButtonConfirmReservation;
	TEdit *EditArrival;
	TEdit *EditDeparture;
	void __fastcall ButtonConfirmReservationClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TDlgReserve(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDlgReserve *DlgReserve;
//---------------------------------------------------------------------------
#endif
