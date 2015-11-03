//---------------------------------------------------------------------------

#ifndef PEdit_formH
#define PEdit_formH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TPEditForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label3;
        TSpeedButton *SpeedButton1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TImage *Image1;
        TSpeedButton *SpeedButton2;
        TSpeedButton *SpeedButton3;
        TSpeedButton *SpeedButton4;
        TDateTimePicker *DateTimePicker1;
        TButton *Button1;
        TButton *Button2;
        TEdit *Edit1;
        TEdit *Edit2;
        TEdit *Edit3;
        TEdit *Edit4;
        TDateTimePicker *DateTimePicker2;
        TListBox *ListBox1;
        TSpeedButton *SpeedButton5;
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall SpeedButton4Click(TObject *Sender);
        void __fastcall SpeedButton5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TPEditForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPEditForm *PEditForm;
//---------------------------------------------------------------------------
#endif
