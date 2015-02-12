//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <IBCustomDataSet.hpp>
#include <IBDatabase.hpp>
#include <IBTable.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <IBQuery.hpp>
#include <IBStoredProc.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
        TIBDatabase *IBDatabase1;
        TIBTable *IBTable1;
	TIBTransaction *IBTransactionMain;
        TDataSource *DataSource1;
        TDBGrid *DBGrid1;
        TDBNavigator *DBNavigator1;
	TComboBox *ComboBoxSelectTable;
	TButton *ButtonLoad;
        TIBQuery *IBQuery1;
	TButton *ButtonExecute;
	TMemo *MemoEnterQuery;
	TIBStoredProc *IBStoredProcReserve;
	TButton *ButtonReserve;
	TButton *ButtonClose;
	TButton *ButtonCancel;
	TEdit *EditShipName;
	TIBStoredProc *IBStoredProcCancel;
	TButton *ButtonArrival;
	TButton *ButtonDeparture;
	TButton *ButtonTime;
	TIBStoredProc *IBStoredProcTimeTax;
	TEdit *EditTax;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall ButtonLoadClick(TObject *Sender);
        void __fastcall ButtonExecuteClick(TObject *Sender);
	void __fastcall ButtonReserveClick(TObject *Sender);
	void __fastcall ButtonCloseClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ButtonCancelClick(TObject *Sender);
	void __fastcall DBNavigator1Click(TObject *Sender, TNavigateBtn Button);
	void __fastcall ButtonArrivalClick(TObject *Sender);
	void __fastcall ButtonDepartureClick(TObject *Sender);
	void __fastcall ButtonTimeClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
