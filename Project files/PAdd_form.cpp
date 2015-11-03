//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main_form.h"
#include "PAdd_form.h"

#include <inifiles.hpp>
#include <jpeg.hpp>
#include <DateUtils.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPAddForm *PAddForm;
//---------------------------------------------------------------------------
__fastcall TPAddForm::TPAddForm(TComponent* Owner)
        : TForm(Owner)
{
        // ��������� � DateTimePicker'�� ������� ����.

        DateTimePicker1->Date=Today();
        DateTimePicker2->Date=Today();
}
//---------------------------------------------------------------------------

String global_PFN; // ���������� ���������� ��������� ��� ����� ����� �����������

//---------------------------------------------------------------------------

// �������� �����

void __fastcall TPAddForm::Button2Click(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

// ���������� ������ � ��

void __fastcall TPAddForm::Button1Click(TObject *Sender)
{
        String AreaList; // ������ �� ���������� �������� �� ListBox.
        bool loc; // ���������� ��� �������� ���������� ������.
        TLocateOptions SearchOptions; // ����� ������.

        if (ListBox1->Items->Count>0) // �������� �� ������� � ListBox'e ��������� � ���� ��� ����...
        {
                for (int i=0; i<ListBox1->Items->Count; i++) // ������� ��������� ������.
                {
                        AreaList+=ListBox1->Items->Strings[i]+";"; // ������ ��������� ������ � ������ AreaList ����� ���� ";".
                }
                AreaList=AreaList.Delete(AreaList.Length(),1); // ������� �� ����� ������ ���� ";".
        }

        // ���������, �������� �� ��� ����� ����� � �������. ���� �� - ����� ��������� �� ������.

        loc=MainForm->ADOTable2->Locate("Address", Edit1->Text, SearchOptions);
        if (loc)
        {
                MessageDlg("����� ����� ��� ����������." ,mtError, TMsgDlgButtons()<<mbOK,0);
        }
        else
        {
                // ���������, ��������� �� ��� ����������� ����. ���� ��� - ����� ��������� �� ������.

                if (Edit1->Text=="" || AreaList=="" || Edit3->Text=="" || Edit4->Text=="")
                {
                        MessageDlg("���� �� ����� '�����', '������ ��������', '�����', '������� �����' �� ��������� !" ,mtError, TMsgDlgButtons()<<mbOK,0);
                }
                else
                {
                        MainForm->ADOQuery2->Close();
                        MainForm->ADOQuery2->SQL->Clear();
                        String s; // ���������� ��� ������ SQL-�������.

                        // ���������, �������� �� ���� �����������.

                        if (global_PFN!="")
                        {
                                // ���� ���� ��������, ��������� SQL-������ � ������ �����...

                                s="INSERT INTO PresentsTable (Address, Area, District, MetroStation, aDate, PFN, pDate) VALUES ('"+PAddForm->Edit1->Text+"','"+AreaList+"','"+PAddForm->Edit3->Text+"','"+PAddForm->Edit4->Text+"','"+PAddForm->DateTimePicker1->Date+"','"+global_PFN+"','"+PAddForm->DateTimePicker2->Date+"');";

                                // � �������� ���� ���� � ���������� � �������������.

                                TIniFile* iniFile;
                                String dirPath; // ���� � ���������� ���������� �����������
                                String iniFileName; // ��� ini-�����
                                String PresentFN=""; // ���(+����) ����� �����������

                                iniFileName=Application->ExeName+".ini"; // ������� ����� ����� - ��� ����� ���������� + ���������� ".ini".
                                iniFile=new TIniFile(iniFileName);
                                dirPath=iniFile->ReadString("data","dirPath",""); // ������������ ���������� dirPath �������� ����� "dirPath" �� ������ "data".

                                /* �� ���� �� ���������� � �����������, ����� ����� � ������������� �
                                   ����� ����� ����������� ����������� ���� ���������� ����� �����
                                   �����������, ������� ������������� ���������� PresentFN. */

                                PresentFN=dirPath+"presents\\"+PresentFN;

                                /* ����������� ���������� ����� � ���������� � � ������, ���������� � ���������� PresentFN.
                                   � ������, ���� ���� � ����� ������ ��� ����������, �� ����� �������. */

                                CopyFile(MainForm->OpenDialog1->FileName.c_str(),PresentFN.c_str(),false);
                        }
                        else
                        {
                                // ���� ���� �� ��������, ��������� SQL-������ � ������ �����...

                                s="INSERT INTO PresentsTable (Address, Area, District, MetroStation, aDate) VALUES ('"+PAddForm->Edit1->Text+"','"+AreaList+"','"+PAddForm->Edit3->Text+"','"+PAddForm->Edit4->Text+"','"+PAddForm->DateTimePicker1->Date+"');";
                        }

                        // ���������� SQL-������ � ��.

                        MainForm->ADOQuery2->SQL->Add(s);
                        MainForm->ADOQuery2->ExecSQL();

                        // ��������� �������

                        MainForm->ADOTable2->Close();
                        MainForm->ADOTable2->Open();

                        PAddForm->Close(); //��������� �����
                }
        }
}
//---------------------------------------------------------------------------

// ���������� ����� �����������

void __fastcall TPAddForm::SpeedButton1Click(TObject *Sender)
{
        do
        {
                if (MainForm->OpenDialog1->Execute()) // �������� ����������� ���� ������ ����� � � ������ ������� ������ "��"...
                {
                        bool loc; // ���������� ��� ���������� ������.
                        TLocateOptions SearchOptions; // ����� ������.

                        String PresentFN=ExtractFileName(MainForm->OpenDialog1->FileName); // � ���������� PresentFN ������������ ��� ���������� �����.
                        loc=MainForm->ADOTable2->Locate("PFN", PresentFN, SearchOptions); // ���� ����� ����� ����� � �������.
                        if (loc) // ���� ����� ��� �������, ����� ��������� � ������.
                        {
                               MessageDlg("����� ���� ��� ��������." ,mtError, TMsgDlgButtons()<<mbOK,0);
                        }
                        else
                        {
                                /* ���� ���������� �� �������, ���������� global_PFN ������������� ��� �����,
                                   ����������� �� ����� ����������� � ��������� Image1,
                                   ���������� �������� ��������� ����������� (������� �� ������, ��������� �����������) */

                                global_PFN=PresentFN;
                                SpeedButton1->Caption="�������� ����";
                                Image1->Picture->LoadFromFile(MainForm->OpenDialog1->FileName);
                                SpeedButton5->Visible=true;
                                Label3->Visible=true;
                                DateTimePicker2->Visible=true;
                        }
                }
                else // ���� � ���������� ���� ������ ������ "������", ����� �� �����.
                {
                        break;
                }
        }
        while (global_PFN==""); // ���� ��������� �������� �� ��� ���, ���� ���������� global_PFN �� ����� ��������� �������� ����� �����.
}
//---------------------------------------------------------------------------

// �������� ���������� ������ ��� �� ������ �����

void __fastcall TPAddForm::Edit1Change(TObject *Sender)
{
        bool loc; // ���������� ��� ���������� ������
        TLocateOptions SearchOptions;
        SearchOptions<<loCaseInsensitive; // ����� ������: ������������������ � ��������.

        loc=MainForm->ADOTable2->Locate("Address", Edit1->Text, SearchOptions); // ����� ��������� ������ � �������.
        if (loc) // ���� ����� ������: ���� ���� "�����" ��������� �� �������, ����������� ����������� ���������.
        {
                Edit1->Color=0x00C1C1FF;
                Edit1->Hint="����� ����� ��� ����������.";
                Edit1->ShowHint=true;
        }
        else // ���� ����� �� ������: ���� ���� "�����" ��������� �� ���� ����, ����������� ��������� ����������.
        {
                Edit1->Color=clWindow;
                Edit1->Hint="";
                Edit1->ShowHint=false;
        }
}
//---------------------------------------------------------------------------

// ���������� ������ �������� ������� � ������ �� ������� ������ "�������� � ������"

void __fastcall TPAddForm::SpeedButton2Click(TObject *Sender)
{
        if (Edit2->Text!="") // �������� �� ������� � ���� "�������" ������.
        {
                if (ListBox1->Items->Count>0) // �������� �� ������� � ListBoxe'e ���������
                {
                        int i; // ������� �����
                        for (i=0; i<ListBox1->Items->Count; i++) // ���������� ��-�� ListBox'a
                        {
                                /* ���� ���� ���������� ������� ��-�� ������ � ������� �� ���� "�������",
                                   ����� ��������� �� ������ � ����� �� �����. */

                                if (Edit2->Text==ListBox1->Items->Strings[i])
                                {
                                        MessageDlg("����� ������� ��� ����." ,mtError, TMsgDlgButtons()<<mbOK,0);
                                        break;
                                }
                        }
                        if (i==ListBox1->Items->Count) // ��������, ���� �� ��������� ��� ��-�� ������.
                        {
                                /* ���� ���� ��������� ��� ��-�� ������ � �� ���� ������� ����������
                                   � ������� �� ���� "�������", ���� ����� ����������� � ������,
                                   � ���� ���� ���������. */

                                ListBox1->Items->Add(Edit2->Text);
                                Edit2->Text="";
                        }
                }
                else // ���� ��������� ���, ����� ����������� �� ���� "�������" � ListBox, � ���� ���� ���������.
                {
                        ListBox1->Items->Add(Edit2->Text);
                        Edit2->Text="";
                }
        }
}
//---------------------------------------------------------------------------

// �������� ���������� ������ �� ������ �� ������� ������ "������� �� ������"

void __fastcall TPAddForm::SpeedButton3Click(TObject *Sender)
{
        if (ListBox1->ItemIndex==-1) // ��������, ������� �� �����-���� ��-� ������.
        {
                ShowMessage("�������� ��������� ��������.");
        }
        else
        {
                ListBox1->DeleteSelected(); // �������� ����������� ��������.
        }
}
//---------------------------------------------------------------------------

// ������� ������ �� ������� ������ "�������� ������"

void __fastcall TPAddForm::SpeedButton4Click(TObject *Sender)
{
        ListBox1->Clear();
}
//---------------------------------------------------------------------------

/* �������� ����� �����������. (�� ����� ���� �� ���������.
   ��������� ���� �������� ����������, ���������� ��� �����,
   � ���������� �������� ��������� �����������.) */

void __fastcall TPAddForm::SpeedButton5Click(TObject *Sender)
{
        global_PFN="";
        SpeedButton1->Caption="�������� ����";
        Image1->Picture=0;
        SpeedButton5->Visible=false;
        Label3->Visible=false;
        DateTimePicker2->Visible=false;
}
//---------------------------------------------------------------------------

