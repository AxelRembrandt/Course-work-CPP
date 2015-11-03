//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main_form.h"
#include "EAdd_form.h"
#include "EEdit_form.h"
#include "PAdd_form.h"
#include "PEdit_form.h"

#include <inifiles.hpp>
#include <jpeg.hpp>
#include <DateUtils.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

// �������� ��� �������� ����� ����������

void __fastcall TMainForm::FormCreate(TObject *Sender)
{

// ��������� ���������

        TIniFile* iniFile;
        String iniFileName; // ��� ini-�����
        String dirPath; // ���� �� ����� ����������
        String host,port,username,password; // ��� �����, ����� �����, �����, ������

        iniFileName=Application->ExeName+".ini"; // ������� ����� ����� - ��� ����� ���������� + ���������� ".ini".
        iniFile=new TIniFile(iniFileName);

        /* ���������� �� ini-����� ����� �����, ������ �����, ������, ������ �
           ��������� ���� �������� � ��������������� ����������. */

        host=iniFile->ReadString("post","host","");
        port=iniFile->ReadString("post","port","");
        username=iniFile->ReadString("post","username","");
        password=iniFile->ReadString("post","password","");

        // ���� ������-�� �� ���� �������� ����, ��������� ��������� � �������.

        if (host=="" || port=="" || username=="" || password=="")
        {
                MessageDlg("������ ������ �� ����� " + iniFile->FileName + ". ���� �� ���������� �� ����� ��������." ,mtError, TMsgDlgButtons()<<mbOK,0);
        }
        else
        {
                /* ������ ����� �����, ������ �����, ������, ������ �
                   ��������������� �������� ���������� IdSMTP1. */

                IdSMTP1->Host=host;
                IdSMTP1->Port=StrToInt(port);
                IdSMTP1->UserId=username;
                IdSMTP1->Password=password;
        }

        Edit1->Text=username; // ������ ������ � ���� "�� ����".

// ���������� ����������2(�������� "������" ���� "����") ������� [E-mail �����]

        // ��������� � ���������� � �� SQL-������, ������������ ������� Email.

        ADOQuery1->Close();
        ADOQuery1->SQL->Clear();
        String s="SELECT Email FROM EmailTable";
        ADOQuery1->SQL->Add(s);
        ADOQuery1->Open();

        // ������� ��������� �� ������ �������, ������������ � ���������� �������.

        ADOQuery1->First();

        // ������� ���� ��������� � �� ���������� � ComboBox.

        while (!ADOQuery1->Eof)
        {
                ComboBox2->Items->Add(ADOQuery1->FieldByName("Email")->AsString);
                ADOQuery1->Next();
        }
        ADOQuery1->Close();

// ��������� � DateTimePicker'� ������� ����.

        DateTimePicker1->Date=Today();
}
//---------------------------------------------------------------------------

/* ��������� ���������� � �� ���, ����� ���������� ����������� ��
����� ���������� ��� �������, ��� �� � ����� � ������������� ��������� �
����� ���������� � �����������.*/

void __fastcall TMainForm::ADOConnection1BeforeConnect(TObject *Sender)
{
        TIniFile* iniFile;
        String dirPath; // ���� � ���������� ���������� ��
        String conString1,conString2,cs; // ������ ����������
        String DBFileName; // ��� ����� ���� ������
        String iniFileName; // ��� ini-�����

        String AppName; // ��� ����� ����������
        int ind, cou; // ������� ��������� � ������, ���-�� �������� � ������.

        // ������ � ini-���� ���� �� ������� ���������� ����������

        iniFileName=Application->ExeName+".ini"; // ������� ����� ����� - ��� ����� ���������� + ���������� ".ini".
        iniFile=new TIniFile(iniFileName);
        AppName=ExtractFileName(Application->ExeName); // ������ ����� ����� ���������� � ���������� AppName.
        cou=AppName.Length(); // ������ ���-�� �������� � ����� ����� ���������� � ���������� cou.

        // ������ � ���������� ind ������� ��������� ����� ����� ���������� � ������, ���������� ���� � ����� ����������.

        ind=Application->ExeName.Pos(AppName);

        // �� ������, ���������� ���� � ����� ����������, ��������� ��� ����� � ���������� ���� ������� � ���������� dirPath.

        dirPath=Application->ExeName.Delete(ind, cou);

        // ���� � ����������, ����������� ����������, ������������ � ini-���� � ������ "data", ��� �������� ����� "dirPath".

        iniFile->WriteString("data","dirPath",dirPath);

        /* ���������� �� ini-����� ���� �� ���������� � �����������,
           2-� ������ ������ ���������� � ����� �� �
           ��������� ���� �������� � �������������� ����������. */

        dirPath=iniFile->ReadString("data","dirPath","");
        conString1=iniFile->ReadString("data","conString1","");
        DBFileName=iniFile->ReadString("data","DBFileName","");
        conString2=iniFile->ReadString("data","conString2","");

        // ���� ������-�� �� ���� �������� ����, ��������� ��������� � �������.

        if (dirPath=="" || conString1=="" || DBFileName=="" || conString2=="")
        {
                MessageDlg("������ ������ �� ����� " + iniFile->FileName + ". ���� �� ���������� �� ����� ��������." ,mtError, TMsgDlgButtons()<<mbOK,0);
        }
        else
        {
                // ������������ ������ ���������� � �� �� ��������� ������.

                cs=conString1+dirPath+DBFileName+conString2;

                // ��������� ������������ ������ � ��-�� ConnectionString ���������� ADOConnection1.

                ADOConnection1->ConnectionString = cs;
        }
}
//---------------------------------------------------------------------------

// �������� ����������

void __fastcall TMainForm::N2Click(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

// �������� ����� ���������� ������ ��������

void __fastcall TMainForm::SpeedButton1Click(TObject *Sender)
{
        Application->CreateForm(__classid(TEAddForm), &EAddForm);
        EAddForm->ShowModal();
        EAddForm->Free();
}
//---------------------------------------------------------------------------

// �������� ����� �������������� ���������� ������ (��������)

void __fastcall TMainForm::SpeedButton2Click(TObject *Sender)
{
        Application->CreateForm(__classid(TEEditForm), &EEditForm);
        EEditForm->ShowModal();
        EEditForm->Free();
}
//---------------------------------------------------------------------------

// �������� ���������� ������ (��������)

void __fastcall TMainForm::SpeedButton3Click(TObject *Sender)
{
        if (MessageBox(0,"�� ������������� ������ ������� ���������� ������?","����������� ��������",MB_YESNO)==IDYES);
        {
                ADOQuery1->Close();
                ADOQuery1->SQL->Clear();
                String s="DELETE * FROM EmailTable WHERE Email='"+ADOTable1->FieldByName("Email")->AsString+"';";
                ADOQuery1->SQL->Add(s);
                ADOQuery1->ExecSQL();
                ADOTable1->Close();
                ADOTable1->Open();
        }
}
//---------------------------------------------------------------------------

// ����������� ���������� � ������ (��������) �� ����� �� ������

void __fastcall TMainForm::DBGrid1CellClick(TColumn *Column)
{
        Memo1->Lines->Clear(); // ������� ���������� ������ �� ���������� Memo1.

        // �������� ���� "eComment" �� ������� � ��� ������.

        if (ADOTable1->FieldByName("eComment")->AsString!="")
        {
                // ���� ���� "eComment" �� ������, ��� ���������� ���������� � Memo1.

                Memo1->Text=ADOTable1->FieldByName("eComment")->AsString;
        }
        else
        {
                // ���� ���� "eComment" ������, � Memo1 ������������� ��������� �� ����.

                Memo1->Text="� ���� ������ ��� ����������.";
        }
}

//---------------------------------------------------------------------------

// ����������� ����������� (������� �����������) �� ����� �� ������

void __fastcall TMainForm::DBGrid2CellClick(TColumn *Column)
{
        TIniFile* iniFile;
        String dirPath; // ���� � ���������� ���������� �����������
        String iniFileName; // ��� ini-�����
        String PresentFN; // ���(+����) ����� �����������

        iniFileName=Application->ExeName+".ini"; // ������� ����� ����� - ��� ����� ���������� + ���������� ".ini".
        iniFile=new TIniFile(iniFileName);
        dirPath=iniFile->ReadString("data","dirPath",""); // ���������� �� ini-����� ���� � ���������� � �����������.

        // �����������, ���� �� ��� ����������� � ���� "PFN".

        if (ADOTable2->FieldByName("PFN")->AsString!="")
        {
                /* �� ���� �� ���������� � �����������, ����� ����� � ������������� �
                   ����� ����� ����������� ����������� ���� � ����������� ����� �����
                   �����������, ������� ������������� ���������� PresentFN. */

                PresentFN=ADOTable2->FieldByName("PFN")->AsString;
                PresentFN=dirPath + "presents\\" + PresentFN;
        }
        else // ���� ����� ����..
        {
                /* �� ���� �� ���������� � �����������, ����� ����� � ������������� �
                   ����� �����-�������� ����������� ���� � �����-��������,
                   ������� (����) ������������� ���������� PresentFN. */

                PresentFN=dirPath+"presents\\"+"not_found.jpg";
        }
        Image1->Picture->LoadFromFile(PresentFN); // ����������� �� ����� ����������� � ��������� Image1.
}
//---------------------------------------------------------------------------

// �������� ����� ���������� �����������

void __fastcall TMainForm::SpeedButton9Click(TObject *Sender)
{
        Application->CreateForm(__classid(TPAddForm), &PAddForm);
        PAddForm->ShowModal();
        PAddForm->Free();
}
//---------------------------------------------------------------------------

// �������� ����� ��������� �����������

void __fastcall TMainForm::SpeedButton10Click(TObject *Sender)
{
        Application->CreateForm(__classid(TPEditForm), &PEditForm);
        PEditForm->ShowModal();
        PEditForm->Free();
}
//---------------------------------------------------------------------------

// �������� ���������� ������ ������ � ����������� �� �� � ����� ����� �� ���������� � �������������

void __fastcall TMainForm::SpeedButton11Click(TObject *Sender)
{
        if (MessageBox(0,"�� ������������� ������ ������� ���������� ������ � ����� ����� �����������?","����������� ��������",MB_YESNO)==IDYES);
        {
                // �����������, ���� �� ��� ����������� � ���� "PFN".

                if (ADOTable2->FieldByName("PFN")->AsString!="")
                {
                        TIniFile* iniFile;
                        String dirPath; // ���� � ���������� ���������� �����������
                        String iniFileName; // ��� ini-�����
                        String PresentFN=ADOTable2->FieldByName("PFN")->AsString; // ���(+����) ����� �����������

                        iniFileName=Application->ExeName+".ini"; // ������� ����� ����� - ��� ����� ���������� + ���������� ".ini".
                        iniFile=new TIniFile(iniFileName);
                        dirPath=iniFile->ReadString("data","dirPath",""); // ���������� �� ini-����� ���� � ���������� � �����������.

                        /* �� ���� �� ���������� � �����������, ����� ����� � ������������� �
                           ����� ����� ����������� ����������� ���� � ����������� ����� �����
                           �����������, ������� ������������� ���������� PresentFN. */

                        PresentFN=dirPath+"presents\\"+PresentFN;
                        DeleteFile(PresentFN); // �������� ��������� ����� ����� �� ����� � �������������.
                }

                // ������������ SQL-�������, ����������� ��� � �� � ���������� �������.

                ADOQuery2->Close();
                ADOQuery2->SQL->Clear();
                String s="DELETE * FROM PresentsTable WHERE Address='"+ADOTable2->FieldByName("Address")->AsString+"';";
                ADOQuery2->SQL->Add(s);
                ADOQuery2->ExecSQL();
                ADOTable2->Close();
                ADOTable2->Open();
        }
}
//---------------------------------------------------------------------------

// ����������� ������

void __fastcall TMainForm::SpeedButton6Click(TObject *Sender)
{
        // �������� ������������� ����� "����" � "����� ������".

        if (ComboBox2->Text=="" || Memo2->Text=="")
        {
                // ���� ���� �� ���� ����� �� ���������, ����� ��������� � �������.

                MessageDlg("���� �� ����� �� ���������!" ,mtError, TMsgDlgButtons()<<mbOK,0);
        }
        else
        {
                if (MessageBox(0,"�� �������, ��� ������ ��������� ������?","����������� �������� ������",MB_YESNO)==IDYES);
                {
                        // ���������� ������� ���������� IdMessage1.

                        IdMessage1->From->Text = Edit1->Text;
                        IdMessage1->Recipients->EMailAddresses = ComboBox2->Text;
                        IdMessage1->Subject = Edit2->Text;
                        IdMessage1->Body->Text = Memo2->Text;

                        IdSMTP1->Connect(); // �������� ���������� � �������� ��������.
                        if (IdSMTP1->Connected()) // ���� ���������� ������ �������...
                        {
                                bool SendInd=0; // "����������-���������" ������������� ������.
                                try
                                {
                                        IdSMTP1->Send(IdMessage1); // �������� ������.
                                        SendInd=1;
                                }
                                catch(...)
                                {
                                        // ���� �� �����-���� ������� ������ �� ���� ����������, ����� ��������� � �������.

                                        MessageDlg("��������� ������! ������ �� ����������." ,mtError, TMsgDlgButtons()<<mbOK,0);
                                        SendInd=0;
                                }
                                if (SendInd) // ���� ������ ���� ����������...
                                {
                                        // ��������, ���� �� ����������� �����������. (��� �������� ����������.)

                                        if(CheckBox1->Checked==true && ComboBox1->Text!="")
                                        {
                                                // ����� ��� ����� ����������� �� ComboBox1->Text, ���� ��� � �������.

                                                TLocateOptions SearchOptions;
                                                bool loc=MainForm->ADOTable2->Locate("PFN", ComboBox1->Text, SearchOptions);
                                                if (loc) // ���� ��� ���� �������...
                                                {
                                                        /* �������� ��������� ������, ���������
                                                           ��������, ������������ � ���� "pStat". */

                                                        int pst=ADOTable2->FieldByName("pStat")->AsInteger;
                                                        pst++; // ����������� ��� �������� �� �������.

                                                        /* ��������� � ���������� � �� SQL-������, ����������� ���� "pStat".
                                                           ��������� �������. */

                                                        ADOQuery2->Close();
                                                        ADOQuery2->SQL->Clear();
                                                        String s="UPDATE PresentsTable SET pStat=";
                                                        s+=pst;
                                                        s+=" WHERE PFN='"+ADOTable2->FieldByName("PFN")->AsString+"';";
                                                        ADOQuery2->SQL->Add(s);
                                                        ADOQuery2->ExecSQL();
                                                        ADOTable2->Close();
                                                        ADOTable2->Open();
                                                }
                                        }
                                        MessageDlg("������ ������� ����������." ,mtInformation, TMsgDlgButtons()<<mbOK,0);
                                }
                        }
                        IdSMTP1->Disconnect(); // �������� ���������� � �������� ��������.
                }
        }
}
//---------------------------------------------------------------------------

/* ����� ������������� ������������ ����������� ��� ����� �� ����� ������
        � ��������� �� ���� ����������� ��� ������� ��������� ���������� */

void __fastcall TMainForm::CheckBox1Click(TObject *Sender)
{
        N14->Checked=CheckBox1->Checked;
        if(CheckBox1->Checked==true)
        {
                Panel4->Visible=true;
                Image2->Visible=true;
        }
        else
        {
                Panel4->Visible=false;
                Image2->Visible=false;
        }
}
//---------------------------------------------------------------------------

// ������� �� ������� "�����������" �� ������� �� ������������.

void __fastcall TMainForm::Label10Click(TObject *Sender)
{
        PageControl1->ActivePage=TabSheet3;
}
//---------------------------------------------------------------------------

/* ���������� ����������� �������, ������������ ��� ������������ �����������,
        �� ������� ������ "���������� � ������" �� �������� ����������� */

void __fastcall TMainForm::SpeedButton8Click(TObject *Sender)
{
        /* ������� CheckBox'a � ��������� "�������",
           �� ��������� ������ ��������� � ���� ��������:
           "�����������" - ����� ����� �����������;
           "���� ���������� �����������" - ���� ���������� �����������. */

        CheckBox1->Checked=true;
        ComboBox1->Text=ADOTable2->FieldByName("PFN")->AsString;
        DateTimePicker1->Date=ADOTable2->FieldByName("pDate")->AsString;

        TIniFile* iniFile;
        String dirPath; // ���� � ���������� ���������� �����������
        String iniFileName; // ��� ini-�����
        String PresentFN; // ���(+����) ����� �����������

        iniFileName=Application->ExeName+".ini"; // ������� ����� ����� - ��� ����� ���������� + ���������� ".ini".
        iniFile=new TIniFile(iniFileName);
        dirPath=iniFile->ReadString("data","dirPath",""); // ���������� �� ini-����� ���� � ���������� � �����������.

        PresentFN=ComboBox1->Text; // ������������ ���������� PresentFN ����� �����.

        /* �� ���� �� ���������� � �����������, ����� ����� � ������������� �
           ����� ����� ����������� ����������� ���� � ����������� ����� �����
           �����������, ������� ������������� ���������� PresentFN. */

        PresentFN=dirPath + "presents\\" + PresentFN;

        // ����������� �� ����� ����������� � ��������� Image1.

        Image2->Picture->LoadFromFile(PresentFN);

        /* ����� ���������� ������������ � ������� ������� �� ������� "������" �
           �������� ������ ���� "�����������". */

        PageControl1->ActivePage=TabSheet1;
        ComboBox1->SetFocus();
}
//---------------------------------------------------------------------------

// ����������� ����������� ��� �� ������ �� ComboBox'a.

void __fastcall TMainForm::ComboBox1Select(TObject *Sender)
{
        TIniFile* iniFile;
        String dirPath; // ���� � ���������� ���������� �����������
        String iniFileName; // ��� ini-�����
        String PresentFN; // ���(+����) ����� �����������

        iniFileName=Application->ExeName+".ini"; // ������� ����� ����� - ��� ����� ���������� + ���������� ".ini".
        iniFile=new TIniFile(iniFileName);
        dirPath=iniFile->ReadString("data","dirPath",""); // ���������� �� ini-����� ���� � ���������� � �����������.

        PresentFN=ComboBox1->Text; // ������������ ���������� PresentFN ����� �����.

        /* �� ���� �� ���������� � �����������, ����� ����� � ������������� �
           ����� ����� ����������� ����������� ���� � ����������� ����� �����
           �����������, ������� ������������� ���������� PresentFN. */

        PresentFN=dirPath + "presents\\" + PresentFN;

        // ����������� �� ����� ����������� � ��������� Image1.

        Image2->Picture->LoadFromFile(PresentFN);
}
//---------------------------------------------------------------------------

// �������� ��� �����, ����� "�� ����", �� �������� "������"

void __fastcall TMainForm::SpeedButton7Click(TObject *Sender)
{
        if (MessageBox(0,"�� �������, ��� ������ �������� ����?","����������� �������",MB_YESNO)==IDYES);
        {
                ComboBox2->Text="";
                Edit2->Text="";
                Memo2->Lines->Clear();  
                ComboBox1->Text="";
                CheckBox1->Checked=false;
                ComboBox1->Items->Clear();
                DateTimePicker1->Date=Today();
                Image2->Picture=0;
        }
}
//---------------------------------------------------------------------------

/* ���������� ����������1(�������� "������" ���� "���������� �����������")
������� [��� ����� �����������] � ����������� �� ������ ������������� ����.*/

void __fastcall TMainForm::ComboBox1DropDown(TObject *Sender)
{
        ComboBox1->Items->Clear(); // ������� ����������� ������ ComboBox'a

        /* ������������ � �������� � �� SQL-�������, ������������� ��������
           ����� "PFN", ���� �������� ���� "pDate" ��������� � ���������
           ������������� �����. */

        ADOQuery2->Close();
        ADOQuery2->SQL->Clear();
        String s="SELECT PFN FROM PresentsTable WHERE pDate LIKE '"+DateTimePicker1->Date+"';";
        ADOQuery2->SQL->Add(s);
        ADOQuery2->Open();

        // ������� ��������� �� ������ �������, ������������ � ���������� �������.

        ADOQuery2->First();

        // ������� ���� ��������� � �� ���������� � ComboBox.

        while (!ADOQuery2->Eof)
        {
                ComboBox1->Items->Add(ADOQuery2->FieldByName("PFN")->AsString);
                ADOQuery2->Next();
        }
        ADOQuery2->Close();
}
//---------------------------------------------------------------------------

// ��������� "���������� �����������" ����� ����.

void __fastcall TMainForm::N14Click(TObject *Sender)
{
        CheckBox1->Checked=!CheckBox1->Checked;
}
//---------------------------------------------------------------------------

/* �������/����������� �������� �� �������. (�� ����� ���������� ��������� ��������
   ����� ������ � �� ��������.) */

void __fastcall TMainForm::N26Click(TObject *Sender)
{
        N26->Checked=!N26->Checked;

        if (N26->Checked)
        {
                SpeedButton1->Width=132;
                SpeedButton2->Width=158;
                SpeedButton3->Width=126;
                SpeedButton6->Width=92;
                SpeedButton7->Width=110;
                SpeedButton8->Width=145;
                SpeedButton9->Width=124;
                SpeedButton10->Width=129;
                SpeedButton11->Width=121;

                SpeedButton8->Left=944;
        }
        else
        {
                SpeedButton1->Width=23;
                SpeedButton2->Width=23;
                SpeedButton3->Width=23;
                SpeedButton6->Width=23;
                SpeedButton7->Width=23;
                SpeedButton8->Width=23;
                SpeedButton9->Width=23;
                SpeedButton10->Width=23;
                SpeedButton11->Width=23;

                SpeedButton8->Left=1064;
        }

        SpeedButton2->Left=SpeedButton1->Left+SpeedButton1->Width+10;
        SpeedButton3->Left=SpeedButton2->Left+SpeedButton2->Width+10;
        SpeedButton7->Left=SpeedButton6->Left+SpeedButton6->Width+10;
        SpeedButton10->Left=SpeedButton9->Left+SpeedButton9->Width+10;
        SpeedButton11->Left=SpeedButton10->Left+SpeedButton10->Width+10;

}
//---------------------------------------------------------------------------

// ������� ������ ���� "������->�������������->��������"

void __fastcall TMainForm::N11Click(TObject *Sender)
{
        Memo2->CutToClipboard();
}
//---------------------------------------------------------------------------

// ������� ������ ���� "������->�������������->����������"

void __fastcall TMainForm::N12Click(TObject *Sender)
{
        Memo2->CopyToClipboard();
}
//---------------------------------------------------------------------------

// ������� ������ ���� "������->�������������->��������"

void __fastcall TMainForm::N13Click(TObject *Sender)
{
        Memo2->PasteFromClipboard();
}
//---------------------------------------------------------------------------

