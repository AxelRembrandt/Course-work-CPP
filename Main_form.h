//---------------------------------------------------------------------------

#ifndef Main_formH
#define Main_formH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <ComCtrls.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdMessageClient.hpp>
#include <IdSMTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdMessage.hpp>
#include <DBCtrls.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TADOConnection *ADOConnection1;
        TADOQuery *ADOQuery1;
        TADOTable *ADOTable1;
        TDataSource *DataSource1;
        TDBGrid *DBGrid1;
        TDBGrid *DBGrid2;
        TDataSource *DataSource2;
        TADOTable *ADOTable2;
        TOpenDialog *OpenDialog1;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TMainMenu *MainMenu1;
        TPanel *Panel1;
        TMemo *Memo1;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TSpeedButton *SpeedButton3;
        TMenuItem *N1;
        TMenuItem *N2;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *Edit1;
        TMemo *Memo2;
        TPanel *Panel2;
        TSpeedButton *SpeedButton6;
        TSpeedButton *SpeedButton7;
        TTabSheet *TabSheet3;
        TPanel *Panel3;
        TLabel *Label5;
        TSpeedButton *SpeedButton9;
        TSpeedButton *SpeedButton11;
        TADOQuery *ADOQuery2;
        TSpeedButton *SpeedButton10;
        TCheckBox *CheckBox1;
        TComboBox *ComboBox1;
        TLabel *Label6;
        TDateTimePicker *DateTimePicker1;
        TLabel *Label7;
        TSpeedButton *SpeedButton8;
        TPanel *Panel4;
        TIdSMTP *IdSMTP1;
        TLabel *Label9;
        TLabel *Label10;
        TComboBox *ComboBox2;
        TLabel *Label11;
        TIdMessage *IdMessage1;
        TEdit *Edit2;
        TMenuItem *N4;
        TMenuItem *N5;
        TMenuItem *N6;
        TMenuItem *N7;
        TMenuItem *N8;
        TMenuItem *N9;
        TMenuItem *N10;
        TMenuItem *N11;
        TMenuItem *N12;
        TMenuItem *N13;
        TMenuItem *N14;
        TMenuItem *N16;
        TMenuItem *N17;
        TMenuItem *N18;
        TMenuItem *N22;
        TMenuItem *N23;
        TMenuItem *N24;
        TMenuItem *N25;
        TMenuItem *N26;
        TPopupMenu *PopupMenu1;
        TPopupMenu *PopupMenu2;
        TPopupMenu *PopupMenu3;
        TMenuItem *N28;
        TMenuItem *N29;
        TMenuItem *N30;
        TMenuItem *N31;
        TMenuItem *N32;
        TMenuItem *N33;
        TMenuItem *N34;
        TMenuItem *N35;
        TImageList *ImageList1;
        TAutoIncField *ADOTable1eID;
        TWideStringField *ADOTable1Email;
        TWideStringField *ADOTable1FIO;
        TWideStringField *ADOTable1Company;
        TWideStringField *ADOTable1Scope;
        TWideStringField *ADOTable1Phone;
        TMemoField *ADOTable1eComment;
        TDateTimeField *ADOTable1eDate;
        TAutoIncField *ADOTable2pID;
        TWideStringField *ADOTable2Address;
        TWideStringField *ADOTable2District;
        TWideStringField *ADOTable2MetroStation;
        TDateTimeField *ADOTable2aDate;
        TWideStringField *ADOTable2PFN;
        TDateTimeField *ADOTable2pDate;
        TIntegerField *ADOTable2pStat;
        TLabel *Label12;
        TImage *Image1;
        TWideStringField *ADOTable2Area;
        TImage *Image2;
        TLabel *Label8;
        TLabel *Label13;
        void __fastcall ADOConnection1BeforeConnect(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall N2Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall SpeedButton6Click(TObject *Sender);
        void __fastcall DBGrid1CellClick(TColumn *Column);
        void __fastcall SpeedButton9Click(TObject *Sender);
        void __fastcall SpeedButton11Click(TObject *Sender);
        void __fastcall SpeedButton10Click(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall SpeedButton8Click(TObject *Sender);
        void __fastcall Label10Click(TObject *Sender);
        void __fastcall SpeedButton7Click(TObject *Sender);
        void __fastcall ComboBox1DropDown(TObject *Sender);
        void __fastcall N14Click(TObject *Sender);
        void __fastcall N26Click(TObject *Sender);
        void __fastcall N11Click(TObject *Sender);
        void __fastcall N12Click(TObject *Sender);
        void __fastcall N13Click(TObject *Sender);
        void __fastcall DBGrid2CellClick(TColumn *Column);
        void __fastcall ComboBox1Select(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
