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

// Закрытие формы

void __fastcall TEEditForm::Button2Click(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

String global_e; // Объявление глобальной переменной для проверки E-mail'a.
int global_eid;  // Объявление глобальной переменной для корректного обновления строки таблицы.

// При создании формы заполним имеющиеся поля значениями из выбранной строки.

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

// Сохранение отредактированных данных в БД.

void __fastcall TEEditForm::Button1Click(TObject *Sender)
{
        bool loc; // Переменная для результата поиска
        TLocateOptions SearchOptions;
        SearchOptions<<loCaseInsensitive; // Опции поиска: нечувствительность к регистру.

        loc=MainForm->ADOTable1->Locate("Email", Edit1->Text, SearchOptions); // Поиск введенного E-mail'a в таблице.

        /* Если E-mail найден и он совпадает с E-mail'ом до изменений,
           осуществляется подмена значения результата поиска на противоположное. */

        if (loc==true && global_e==MainForm->ADOTable1->FieldByName("Email")->AsString)
        {
                loc=false;
        }

        /* Если E-mail найден и он не совпадает с E-mail'ом до изменений,
           выводится сообщение с ошибкой. */

        if (loc)
        {
                MessageDlg("Такой E-mail уже добавлен." ,mtError, TMsgDlgButtons()<<mbOK,0);
        }
        else
        {
                // Проверяем, заполнены ли все необходимые поля. Если нет - вывод сообщения об ошибке.

                if (Edit1->Text=="" || Edit2->Text=="")
                {
                        MessageDlg("Не заполнено поле 'E-mail' или 'Ф.И.О.'!" ,mtError, TMsgDlgButtons()<<mbOK,0);
                }
                else
                {
                        // Формирование и отправка SQL-запроса в БД.

                        MainForm->ADOQuery1->Close();
                        MainForm->ADOQuery1->SQL->Clear();
                        String s="UPDATE EmailTable SET Email='"+EEditForm->Edit1->Text+"', FIO='"+EEditForm->Edit2->Text+"', Company='"+EEditForm->Edit3->Text+"', Scope='"+EEditForm->Edit4->Text+"', Phone='"+EEditForm->Edit5->Text+"', eComment='"+EEditForm->Memo1->Text+"', eDate='"+EEditForm->DateTimePicker1->Date+"' WHERE eID="+global_eid+";";
                        MainForm->ADOQuery1->SQL->Add(s);
                        MainForm->ADOQuery1->ExecSQL();

                        // Обновление таблицы.

                        MainForm->ADOTable1->Close();
                        MainForm->ADOTable1->Open();
                        
                        EEditForm->Close(); // Закрытие формы.
                }
        }
}
//---------------------------------------------------------------------------

// Проверка совпадения E-mail'a еще на стадии ввода

void __fastcall TEEditForm::Edit1Change(TObject *Sender)
{
        bool loc; // Переменная для результата поиска
        TLocateOptions SearchOptions;
        SearchOptions<<loCaseInsensitive; // Опции поиска: нечувствительность к регистру.

        loc=MainForm->ADOTable1->Locate("Email", Edit1->Text, SearchOptions); // Поиск вводимого E-mail'a в таблице.

        /* Если E-mail найден и он совпадает с E-mail'ом до изменений,
           осуществляется подмена значения результата поиска на противоположное. */

        if (loc==true && global_e==MainForm->ADOTable1->FieldByName("Email")->AsString)
        {
                loc=false;
        }
        
        /* Если E-mail найден и он не совпадает с E-mail'ом до изменений,
           цвет поля "E-mail" сменяется на розовый, добавляется всплывающая подсказка. */

        if (loc)
        {
                Edit1->Color=0x00C1C1FF;
                Edit1->Hint="Такой E-mail уже добавлен.";
                Edit1->ShowHint=true;
        }
        else // Если адрес не найден: цвет поля "E-mail" сменяется на цвет окна, всплывающая подсказка скрывается.
        {
                Edit1->Color=clWindow;
                Edit1->Hint="";
                Edit1->ShowHint=false;
        }
}
//---------------------------------------------------------------------------

