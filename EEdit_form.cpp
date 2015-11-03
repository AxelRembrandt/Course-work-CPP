//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main_form.h"
#include "EEdit_form.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEEditForm *EEditForm;
//---------------------------------------------------------------------------
__fastcall TEEditForm::TEEditForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

// �������� �����

void __fastcall TEEditForm::Button2Click(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

String global_e; // ���������� ���������� ���������� ��� �������� E-mail'a.
int global_eid;  // ���������� ���������� ���������� ��� ����������� ���������� ������ �������.

// ��� �������� ����� �������� ��������� ���� ���������� �� ��������� ������.

void __fastcall TEEditForm::FormCreate(TObject *Sender)
{
        global_e=MainForm->ADOTable1->FieldByName("Email")->AsString;
        global_eid=MainForm->ADOTable1->FieldByName("eID")->AsInteger;
        EEditForm->Edit1->Text=MainForm->ADOTable1->FieldByName("Email")->AsString;
        EEditForm->Edit2->Text=MainForm->ADOTable1->FieldByName("FIO")->AsString;
        EEditForm->Edit3->Text=MainForm->ADOTable1->FieldByName("Company")->AsString;
        EEditForm->Edit4->Text=MainForm->ADOTable1->FieldByName("Scope")->AsString;
        EEditForm->Edit5->Text=MainForm->ADOTable1->FieldByName("Phone")->AsString;
        EEditForm->Memo1->Text=MainForm->ADOTable1->FieldByName("eComment")->AsString;
        EEditForm->DateTimePicker1->Date=MainForm->ADOTable1->FieldByName("eDate")->AsString;
}
//---------------------------------------------------------------------------

// ���������� ����������������� ������ � ��.

void __fastcall TEEditForm::Button1Click(TObject *Sender)
{
        bool loc; // ���������� ��� ���������� ������
        TLocateOptions SearchOptions;
        SearchOptions<<loCaseInsensitive; // ����� ������: ������������������ � ��������.

        loc=MainForm->ADOTable1->Locate("Email", Edit1->Text, SearchOptions); // ����� ���������� E-mail'a � �������.

        /* ���� E-mail ������ � �� ��������� � E-mail'�� �� ���������,
           �������������� ������� �������� ���������� ������ �� ���������������. */

        if (loc==true && global_e==MainForm->ADOTable1->FieldByName("Email")->AsString)
        {
                loc=false;
        }

        /* ���� E-mail ������ � �� �� ��������� � E-mail'�� �� ���������,
           ��������� ��������� � �������. */

        if (loc)
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
                        String s="UPDATE EmailTable SET Email='"+EEditForm->Edit1->Text+"', FIO='"+EEditForm->Edit2->Text+"', Company='"+EEditForm->Edit3->Text+"', Scope='"+EEditForm->Edit4->Text+"', Phone='"+EEditForm->Edit5->Text+"', eComment='"+EEditForm->Memo1->Text+"', eDate='"+EEditForm->DateTimePicker1->Date+"' WHERE eID="+global_eid+";";
                        MainForm->ADOQuery1->SQL->Add(s);
                        MainForm->ADOQuery1->ExecSQL();

                        // ���������� �������.

                        MainForm->ADOTable1->Close();
                        MainForm->ADOTable1->Open();
                        
                        EEditForm->Close(); // �������� �����.
                }
        }
}
//---------------------------------------------------------------------------

// �������� ���������� E-mail'a ��� �� ������ �����

void __fastcall TEEditForm::Edit1Change(TObject *Sender)
{
        bool loc; // ���������� ��� ���������� ������
        TLocateOptions SearchOptions;
        SearchOptions<<loCaseInsensitive; // ����� ������: ������������������ � ��������.

        loc=MainForm->ADOTable1->Locate("Email", Edit1->Text, SearchOptions); // ����� ��������� E-mail'a � �������.

        /* ���� E-mail ������ � �� ��������� � E-mail'�� �� ���������,
           �������������� ������� �������� ���������� ������ �� ���������������. */

        if (loc==true && global_e==MainForm->ADOTable1->FieldByName("Email")->AsString)
        {
                loc=false;
        }
        
        /* ���� E-mail ������ � �� �� ��������� � E-mail'�� �� ���������,
           ���� ���� "E-mail" ��������� �� �������, ����������� ����������� ���������. */

        if (loc)
        {
                Edit1->Color=0x00C1C1FF;
                Edit1->Hint="����� E-mail ��� ��������.";
                Edit1->ShowHint=true;
        }
        else // ���� ����� �� ������: ���� ���� "E-mail" ��������� �� ���� ����, ����������� ��������� ����������.
        {
                Edit1->Color=clWindow;
                Edit1->Hint="";
                Edit1->ShowHint=false;
        }
}
//---------------------------------------------------------------------------

