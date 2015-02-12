//---------------------------------------------------------------------------

#ifndef FileOpsH
#define FileOpsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <stdio.h>
//---------------------------------------------------------------------------
#include <DB.hpp>
#include <IBDatabase.hpp>
#include <IBCustomDataSet.hpp>
#include <IBTable.hpp>
#include <DBTables.hpp>
#include <IBBlob.hpp>
#include <DBLogDlg.hpp>
#include <IBServices.hpp>
#include <IBUpdateSQL.hpp>
#include <OleCtnrs.hpp>
#include <DBCtrls.hpp>
#include <IBQuery.hpp>
#include <SysUtils.hpp>
#include <ExtCtrls.hpp>
#include <System.hpp>
#include <process.h>
//---------------------------------------------------------------------------
class TFileForm : public TForm
{
__published:	// IDE-managed Components
        TIBDatabase *IBDatabase1;
        TIBTransaction *IBTransaction1;
        TButton *Button1;
        TIBTable *IBTable1;
        TIBUpdateSQL *IBUpdateSQL1;
        TButton *Button2;
        TButton *Button3;
        TIBQuery *IBQuery1;
        TEdit *Edit1;
        TEdit *Edit2;
        TEdit *Edit3;
        TIntegerField *IBQuery1FL_ID;
        TIBStringField *IBQuery1NAME;
        TIBStringField *IBQuery1DESCR;
        TIntegerField *IBQuery1PRT_ID;
        TBlobField *IBQuery1FILE_OBJ;
        TIntegerField *IBTable1FL_ID;
        TIBStringField *IBTable1NAME;
        TIBStringField *IBTable1DESCR;
        TIntegerField *IBTable1PRT_ID;
        TBlobField *IBTable1FILE_OBJ;
        TButton *Button5;
        TIBTransaction *IBTransaction2;
        TButton *Button4;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        AnsiString data;
        __fastcall TFileForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFileForm *FileForm;
//---------------------------------------------------------------------------
#endif
