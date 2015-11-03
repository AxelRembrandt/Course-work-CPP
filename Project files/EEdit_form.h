//---------------------------------------------------------------------------

#ifndef EEdit_formH
#define EEdit_formH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TEEditForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TEdit *Edit1;
        TEdit *Edit2;
        TEdit *Edit3;
        TMemo *Memo1;
        TButton *Button2;
        TDateTimePicker *DateTimePicker1;
        TButton *Button1;
        TEdit *Edit4;
        TEdit *Edit5;
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TEEditForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEEditForm *EEditForm;
//---------------------------------------------------------------------------
#endif
