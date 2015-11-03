//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main_form.h"
#include "PEdit_form.h"

#include <inifiles.hpp>
#include <jpeg.hpp>
#include <DateUtils.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPEditForm *PEditForm;
//---------------------------------------------------------------------------
__fastcall TPEditForm::TPEditForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

// ���������� ���������� ����������

String global_adr; // ����� �� ���������.
String global_pfn;  // ��� ����� �� ���������.
String global_pfp ; // ���� � ������������ ����� (+��� �����).
int global_pid;  // ���������� ���������� ���������� ��� ����������� ���������� ������ �������.

TIniFile* iniFile;
String dirPath; // ���� � ���������� ���������� �����������
String iniFileName; // ��� ini-�����
String PresentFN; // ���(+����) ����� ����������� (��������������� ����������)

//---------------------------------------------------------------------------

// ���������� ��������� ����� � ���������� ���������� ���������� �� ��������� ������ ��� �������� �����.

void __fastcall TPEditForm::FormCreate(TObject *Sender)
{
        global_adr=MainForm->ADOTable2->FieldByName("Address")->AsString;
        global_pfn=MainForm->ADOTable2->FieldByName("PFN")->AsString;
        global_pid=MainForm->ADOTable2->FieldByName("pID")->AsInteger;

        PEditForm->Edit1->Text=MainForm->ADOTable2->FieldByName("Address")->AsString;
        PEditForm->Edit3->Text=MainForm->ADOTable2->FieldByName("District")->AsString;
        PEditForm->Edit4->Text=MainForm->ADOTable2->FieldByName("MetroStation")->AsString;
        PEditForm->DateTimePicker1->Date=MainForm->ADOTable2->FieldByName("aDate")->AsString;

        // ���������� ListBox'a � ���������

        String Areas; // ������ �� ���������� ��������.
        int ind=1; // ������� ��������� � ������
        int cou; // ���-�� �������� � ������

        Areas=MainForm->ADOTable2->FieldByName("Area")->AsString+";";
        do
        {
                // ���������� cou ������������� �������� ������� ������� ��������� ������� ";" � ������ Areas ����� �������.

                cou=Areas.Pos(";")-1;

                /* ���������� � ������ ������ �������� �� ��������� ��������� "cou" � ������� ind,
                   ������������ � ������ Areas. (�������� ������� ��� ����� ";".) */

                ListBox1->Items->Add(Areas.SubString(ind, cou));

                /* �������� ��������� ��������� "cou+1" � ������� ind, ������������ � ������ Areas.
                   (�������� ������� �� ������ ";".) */

                Areas.Delete(ind, cou+1);
        }
        while(!Areas.IsEmpty()); // ���� ��������� ��������, ���� ������ Areas �� �����.

        // �������� ������ � �����������

        iniFileName=Application->ExeName+".ini"; // ������� ����� ����� - ��� ����� ���������� + ���������� ".ini".
        iniFile=new TIniFile(iniFileName);
        dirPath=iniFile->ReadString("data","dirPath",""); // ������������ ���������� dirPath �������� ����� "dirPath" �� ������ "data".

        if (global_pfn!="") // �������� ������� ����� �����. ���� ��� ����...
        {
                /* �� ���� �� ���������� � �����������, ����� ����� � ������������� �
                   ����� ����� ����������� ����������� ���� � ����������� ����� �����
                   �����������, ������� ������������� ���������� PresentFN. */

                PresentFN=dirPath+"presents\\"+global_pfn;
                PEditForm->Image1->Picture->LoadFromFile(PresentFN); // ����������� �� ����� ����������� � ��������� Image1.

                /* �������� Date ���������� DateTimePicker2 ������������� �������� ���� "pDate" �� ��������� ������.
                   (���� ���������� �����������.) */

                PEditForm->DateTimePicker2->Date=MainForm->ADOTable2->FieldByName("pDate")->AsString;

                // ����� ���������� �������� ��������� ����������� (������� �� ������, ��������� �����������).

                SpeedButton1->Caption="�������� ����";
                SpeedButton5->Visible=true;
                Label3->Visible=true;
                DateTimePicker2->Visible=true;
        }
        else // ���� ����� ����...
        {
                /* �� ���� �� ���������� � �����������, ����� ����� � ������������� �
                   ����� �����-�������� ����������� ���� � �����-��������,
                   ������� (����) ������������� ���������� PresentFN. */

                PresentFN=dirPath+"presents\\"+"not_found.jpg";
                PEditForm->Image1->Picture->LoadFromFile(PresentFN); // ����������� �� ����� ����������� � ��������� Image1.

                // �������� Date ���������� DateTimePicker2 ������������� �������� ������� ����.

                PEditForm->DateTimePicker2->Date=Today();

                // ����� ���������� �������� ��������� ����������� (������� �� ������, ��������� �����������).

                SpeedButton1->Caption="�������� ����";
                SpeedButton5->Visible=false;
                Label3->Visible=false;
                DateTimePicker2->Visible=false;
        }

        /* ����� ���� �������� �������� ���������� PresentFN �������� ������ �
           ���������� ������� � ���� ��� ����� �����. �� ��� ���������� ���������� �
           ��� �������� � ������� ����������, ����� ��� ��������� ���� ��� �����.
           �������� �� �������� ����� ����� �� ���������. */

        PresentFN=global_pfn;
}
//---------------------------------------------------------------------------

// �������� �����

void __fastcall TPEditForm::Button2Click(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

// ���������� ����� �����������

void __fastcall TPEditForm::SpeedButton1Click(TObject *Sender)
{
        do
        {
                if (MainForm->OpenDialog1->Execute()) // �������� ����������� ���� ������ ����� � � ������ ������� ������ "��"...
                {
                        bool loc; // ���������� ��� ���������� ������.
                        TLocateOptions SearchOptions; // ����� ������.
                        
                        PresentFN=ExtractFileName(MainForm->OpenDialog1->FileName); // � ���������� PresentFN ������������ ��� ���������� �����.
                        loc=MainForm->ADOTable2->Locate("PFN", PresentFN, SearchOptions); // ���� ����� ����� ����� � �������.

                        /* ���� ����� ��� ������� � ��� ��������� � ������ ����� �� ���������,
                           �������������� ������� �������� ���������� ������ �� ���������������. */

                        if (loc==true && global_pfn==MainForm->ADOTable2->FieldByName("PFN")->AsString)
                        {
                                loc=false;
                        }

                        /* ���� ����� ��� ������� � ��� �� ��������� � ������ ����� �� ���������,
                           ��������� ��������� �� ������. */

                        if (loc)
                        {
                               MessageDlg("����� ���� ��� ��������." ,mtError, TMsgDlgButtons()<<mbOK,0);
                        }
                        else // � ��������� ������...
                        {
                                /* ���������� global_pfp ������������� ������ ���� ��
                                   ���������� ����� ������ � ������ �����. */

                                global_pfp=MainForm->OpenDialog1->FileName;

                                /* ���� ���������� ����������� �� ����, ���������� global_pfn
                                   ������������� ��� ���������� �����. */

                                if (global_pfn=="")
                                {
                                        global_pfn=PresentFN;
                                }

                                // ����������� �� ���������� ����� ����������� � ��������� Image1.

                                Image1->Picture->LoadFromFile(global_pfp);

                                // �������� Date ���������� DateTimePicker2 ������������� �������� ������� ����.

                                DateTimePicker2->Date=Today();

                                // ����� ���������� �������� ��������� ����������� (������� �� ������, ��������� �����������).

                                SpeedButton1->Caption="�������� ����";
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
        while (global_pfp==""); // ���� ��������� �������� �� ��� ���, ���� ���������� global_pfp �� ����� ��������� �������� ���� �� �����.
}
//---------------------------------------------------------------------------

// ���������� ����������������� ������ � ��.

void __fastcall TPEditForm::Button1Click(TObject *Sender)
{
        bool loc; // ���������� ��� �������� ���������� ������.
        TLocateOptions SearchOptions;
        SearchOptions<<loCaseInsensitive; // ����� ������: ������������������ � ��������.
        String Areas; // ������ �� ���������� �������� �� ListBox.

        if (ListBox1->Items->Count>0) // �������� �� ������� � ListBox'e ��������� � ���� ��� ����...
        {
                for (int i=0; i<ListBox1->Items->Count; i++) // ������� ��������� ������.
                {
                        Areas+=ListBox1->Items->Strings[i]+";"; // ������ ��������� ������ � ������ Areas ����� ���� ";".
                }
                Areas.Delete(Areas.Length(),1); // ������� �� ����� ������ ���� ";".
        }

        loc=MainForm->ADOTable2->Locate("Address", Edit1->Text, SearchOptions); // ����� ���������� ������ � �������.

        /* ���� ����� ����� ������ � �� ��������� � ������� �� ���������,
           �������������� ������� �������� ���������� ������ �� ���������������. */

        if (loc==true && global_adr==MainForm->ADOTable2->FieldByName("Address")->AsString)
        {
                loc=false;
        }

        /* ���� ����� ����� ������ � �� �� ��������� � ������� �� ���������,
           ��������� ��������� � �������. */

        if (loc)
        {
                MessageDlg("����� ����� ��� ����������." ,mtError, TMsgDlgButtons()<<mbOK,0);
        }
        else
        {
                // ���������, ��������� �� ��� ����������� ����. ���� ��� - ����� ��������� �� ������.

                if (Edit1->Text=="" || ListBox1->Items->Text=="" || Edit3->Text=="" || Edit4->Text=="")
                {
                        MessageDlg("���� �� ����� '�����', '������ ��������', '�����', '������� �����' �� ��������� !" ,mtError, TMsgDlgButtons()<<mbOK,0);
                }
                else
                {
                        MainForm->ADOQuery2->Close();
                        MainForm->ADOQuery2->SQL->Clear();
                        String s;// ���������� ��� ������ SQL-�������.

                        // ���������, �������� �� ���� �����������.

                        if (global_pfn!="")
                        {
                                // ���� ���� ��������, ��������� SQL-������ � ������ �����...

                                s="UPDATE PresentsTable SET Address='"+PEditForm->Edit1->Text+"', Area='"+Areas+"', District='"+PEditForm->Edit3->Text+"', MetroStation='"+PEditForm->Edit4->Text+"', aDate='"+PEditForm->DateTimePicker1->Date+"', PFN='"+PresentFN+"', pDate='"+PEditForm->DateTimePicker2->Date+"' WHERE pID="+global_pid+";";

                                // � �������� ������ ����� ����� ����������� �����.

                                iniFileName=Application->ExeName+".ini"; // ������� ����� ����� - ��� ����� ���������� + ���������� ".ini".
                                iniFile=new TIniFile(iniFileName);
                                dirPath=iniFile->ReadString("data","dirPath",""); // ������������ ���������� dirPath �������� ����� "dirPath" �� ������ "data".

                                /* �� ���� �� ���������� � �����������, ����� ����� � ������������� �
                                   ����� ����� ����������� ����������� ���� � ������ ����� �����
                                   �����������, ������� ������������� ���������� global_pfn. */

                                global_pfn=dirPath+"presents\\"+global_pfn;
                                DeleteFile(global_pfn); // �������� ������ ����� �����.

                                /* �� ���� �� ���������� � �����������, ����� ����� � ������������� �
                                   ����� ����� ����������� ����������� ���� ���������� ����� �����
                                   �����������, ������� ������������� ���������� PresentFN. */

                                PresentFN=dirPath+"presents\\"+PresentFN;

                                /* ����������� ���������� ����� � ���������� � � ������, ���������� � ���������� PresentFN.
                                   � ������, ���� ���� � ����� ������ ��� ����������, �� ����� �������. */

                                CopyFile(global_pfp.c_str(),PresentFN.c_str(),false);
                        }
                        else
                        {
                                // ���� ���� �� ��������, ��������� SQL-������ � ������ �����...

                                s="UPDATE PresentsTable SET Address='"+PEditForm->Edit1->Text+"', Area='"+Areas+"', District='"+PEditForm->Edit3->Text+"', MetroStation='"+PEditForm->Edit4->Text+"', aDate='"+PEditForm->DateTimePicker1->Date+"', PFN=NULL, pDate=NULL WHERE pID="+global_pid+";";
                        }

                        // ���������� SQL-������ � ��.

                        MainForm->ADOQuery2->SQL->Add(s);
                        MainForm->ADOQuery2->ExecSQL();

                        // ��������� �������

                        MainForm->ADOTable2->Close();
                        MainForm->ADOTable2->Open();

                        PEditForm->Close(); // ��������� �����.
                }
        }
}
//---------------------------------------------------------------------------

// �������� ���������� ������ ��� �� ������ �����

void __fastcall TPEditForm::Edit1Change(TObject *Sender)
{
        bool loc; // ���������� ��� ���������� ������.
        TLocateOptions SearchOptions;
        SearchOptions<<loCaseInsensitive; // ����� ������: ������������������ � ��������.
        
        loc=MainForm->ADOTable2->Locate("Address", Edit1->Text, SearchOptions); // ����� ��������� ������ � �������.

        /* ���� ����� ������ � �� ��������� � ������� �� ���������,
           �������������� ������� �������� ���������� ������ �� ���������������. */

        if (loc==true && global_adr==MainForm->ADOTable2->FieldByName("Address")->AsString)
        {
                loc=false;
        }

        /* ���� ����� ������ � �� �� ��������� � ������� �� ���������,
           ���� ���� "�����" ��������� �� �������, ����������� ����������� ���������. */

        if (loc)
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

void __fastcall TPEditForm::SpeedButton2Click(TObject *Sender)
{
        if (Edit2->Text!="") // �������� �� ������� � ���� "�������" ������.
        {
                if (ListBox1->Items->Count>0) // �������� �� ������� � ListBoxe'e ���������
                {
                        int i; // ������� �����
                        for (i=0; i<ListBox1->Items->Count; i++) // ���������� ��-�� ������
                        {
                                /* ���� ���� ���������� ������� ��-�� ������ � ������� �� ���� "�������",
                                   ����� ��������� �� ������ � ����� �� �����. */

                                if (Edit2->Text==ListBox1->Items->Strings[i])
                                {
                                        MessageDlg("����� ������� ��� ����." ,mtError, TMsgDlgButtons()<<mbOK,0);
                                        break;
                                }
                        }
                        if (i==ListBox1->Items->Count) // ��������, ���� �� ��������� ��� �������� ������.
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

void __fastcall TPEditForm::SpeedButton3Click(TObject *Sender)
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

void __fastcall TPEditForm::SpeedButton4Click(TObject *Sender)
{
        ListBox1->Clear();
}
//---------------------------------------------------------------------------

// �������� ����� �����������

void __fastcall TPEditForm::SpeedButton5Click(TObject *Sender)
{
        if (MessageBox(0,"�� ������������� ������ ������� ����� ����� �����������?","����������� ��������",MB_YESNO)==IDYES);
        {
                iniFileName=Application->ExeName+".ini"; // ������� ����� ����� - ��� ����� ���������� + ���������� ".ini".
                iniFile=new TIniFile(iniFileName);
                dirPath=iniFile->ReadString("data","dirPath",""); // ������������ ���������� dirPath �������� ����� "dirPath" �� ������ "data".

                /* �� ���� �� ���������� � �����������, ����� ����� � ������������� �
                   ����� ����� ����������� ����������� ���� � ����������� ����� �����
                   �����������, ������� ������������� ���������� global_pfn. */

                global_pfn=dirPath+"presents\\"+global_pfn;
                DeleteFile(global_pfn); // �������� ����� ����� �����������

                /* �� ���� �� ���������� � �����������, ����� ����� � ������������� �
                   ����� �����-�������� ����������� ���� � �����-��������,
                   ������� (����) ������������� ���������� PresentFN. */

                PresentFN=dirPath+"presents\\"+"not_found.jpg";
                PEditForm->Image1->Picture->LoadFromFile(PresentFN); // ����������� �� �����-�������� ����������� � ��������� Image1.

                /* ����� ���� �������� �������� ���������� global_pfn � PresentFN �������� ������ �
                   ����������� �������� � ��� ��� ���� ������. ������, �������������� �����
                   ����������� ������ ���, ������������� ���� ���������� ���� ��������� �������� ������ ������. */

                global_pfn="";
                PresentFN="";

                // ��������� � ��������� SQL-������ � ��, ��������� �������.

                MainForm->ADOQuery2->Close();
                MainForm->ADOQuery2->SQL->Clear();
                String s="UPDATE PresentsTable SET PFN='"+PresentFN+"', pDate=NULL WHERE pID="+global_pid+";";
                MainForm->ADOQuery2->SQL->Add(s);
                MainForm->ADOQuery2->ExecSQL();
                MainForm->ADOTable2->Close();
                MainForm->ADOTable2->Open();

                // ����� ���������� �������� ��������� ����������� (������� �� ������, ��������� �����������).

                SpeedButton1->Caption="�������� ����";
                SpeedButton5->Visible=false;
                Label3->Visible=false;
                DateTimePicker2->Visible=false;
        }
}
//---------------------------------------------------------------------------

