//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main_form.h"
#include "EAdd_form.h"

#include <DateUtils.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEAddForm *EAddForm;
//---------------------------------------------------------------------------
__fastcall TEAddForm::TEAddForm(TComponent* Owner)
        : TForm(Owner)
{
        DateTimePicker1->Date=Today(); // ��������� � DateTimePicker'a ������� ����.
}
//---------------------------------------------------------------------------

// �������� �����

void __fastcall TEAddForm::Button2Click(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

// ���������� ����� ������ � ��.

void __fastcall TEAddForm::Button1Click(TObject *Sender)
{
        bool loc; // ���������� ��� ���������� ������.
        TLocateOptions SearchOptions;
        SearchOptions<<loCaseInsensitive; // ����� ������: ������������������ � ��������.

        loc=MainForm->ADOTable1->Locate("Email", Edit1->Text, SearchOptions); // ����� ��������� E-mail'a � �������.
        if (loc) // ���� ����� E-mail ������, ����� ��������� � ������.
        {
                MessageDlg("����� E-mail ��� ��������." ,mtError, TMsgDlgButtons()<<mbOK,0);
        }
        else
        {
                // ���������, ��������� �� ��� ����������� ����. ���� ��� - ����� ��������� �� ������.

                if (Edit1->Text=="" || Edit2->Text=="")
                {
                        MessageDlg("�� ��������� ���� 'E-mail' ��� '�.�.�.'!" ,mtError, TMsgDlgButtons()<<mbOK,0);
                }
                else
                {
                        // ������������ � �������� SQL-������� � ��.

                        MainForm->ADOQuery1->Close();
                        MainForm->ADOQuery1->SQL->Clear();
                        String s="INSERT INTO EmailTable (Email, FIO, Company, Scope, Phone, eComment, eDate) VALUES ('"+EAddForm->Edit1->Text+"','"+EAddForm->Edit2->Text+"','"+EAddForm->Edit3->Text+"','"+EAddForm->Edit4->Text+"','"+EAddForm->Edit5->Text+"','"+EAddForm->Memo1->Text+"','"+EAddForm->DateTimePicker1->Date+"');";
                        MainForm->ADOQuery1->SQL->Add(s);
                        MainForm->ADOQuery1->ExecSQL();

                        // ���������� �������.

                        MainForm->ADOTable1->Close();
                        MainForm->ADOTable1->Open();

                        EAddForm->Close(); // �������� �����.
                }
        }
}
//---------------------------------------------------------------------------

// �������� ���������� E-mail'a ��� �� ������ �����

void __fastcall TEAddForm::Edit1Change(TObject *Sender)
{
        bool loc; // ���������� ��� ���������� ������.
        TLocateOptions SearchOptions;
        SearchOptions<<loCaseInsensitive; // ����� ������: ������������������ � ��������.

        loc=MainForm->ADOTable1->Locate("Email", Edit1->Text, SearchOptions); // ����� ��������� E-mail'a � �������.
        if (loc) // ���� E-mail ������: ���� ���� "E-mail" ��������� �� �������, ����������� ����������� ���������.
        {
                Edit1->Color=0x00C1C1FF;
                Edit1->Hint="����� E-mail ��� ��������.";
                Edit1->ShowHint=true;
        }
        else // ���� E-mail �� ������: ���� ���� "E-mail" ��������� �� ���� ����, ����������� ��������� ����������.
        {
                Edit1->Color=clWindow;
                Edit1->Hint="";
                Edit1->ShowHint=false;
        }
}
//---------------------------------------------------------------------------

