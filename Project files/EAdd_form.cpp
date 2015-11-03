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
        DateTimePicker1->Date=Today(); // Установка у DateTimePicker'a текущей даты.
}
//---------------------------------------------------------------------------

// Закрытие формы

void __fastcall TEAddForm::Button2Click(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

// Добавление новой записи в БД.

void __fastcall TEAddForm::Button1Click(TObject *Sender)
{
        bool loc; // Переменная для результата поиска.
        TLocateOptions SearchOptions;
        SearchOptions<<loCaseInsensitive; // Опции поиска: нечувствительность к регистру.

        loc=MainForm->ADOTable1->Locate("Email", Edit1->Text, SearchOptions); // Поиск вводимого E-mail'a в таблице.
        if (loc) // Если такой E-mail найден, вывод сообщения о ошибке.
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
                        String s="INSERT INTO EmailTable (Email, FIO, Company, Scope, Phone, eComment, eDate) VALUES ('"+EAddForm->Edit1->Text+"','"+EAddForm->Edit2->Text+"','"+EAddForm->Edit3->Text+"','"+EAddForm->Edit4->Text+"','"+EAddForm->Edit5->Text+"','"+EAddForm->Memo1->Text+"','"+EAddForm->DateTimePicker1->Date+"');";
                        MainForm->ADOQuery1->SQL->Add(s);
                        MainForm->ADOQuery1->ExecSQL();

                        // Обновление таблицы.

                        MainForm->ADOTable1->Close();
                        MainForm->ADOTable1->Open();

                        EAddForm->Close(); // Закрытие формы.
                }
        }
}
//---------------------------------------------------------------------------

// Проверка совпадения E-mail'a еще на стадии ввода

void __fastcall TEAddForm::Edit1Change(TObject *Sender)
{
        bool loc; // Переменная для результата поиска.
        TLocateOptions SearchOptions;
        SearchOptions<<loCaseInsensitive; // Опции поиска: нечувствительность к регистру.

        loc=MainForm->ADOTable1->Locate("Email", Edit1->Text, SearchOptions); // Поиск вводимого E-mail'a в таблице.
        if (loc) // Если E-mail найден: цвет поля "E-mail" сменяется на розовый, добавляется всплывающая подсказка.
        {
                Edit1->Color=0x00C1C1FF;
                Edit1->Hint="Такой E-mail уже добавлен.";
                Edit1->ShowHint=true;
        }
        else // Если E-mail не найден: цвет поля "E-mail" сменяется на цвет окна, всплывающая подсказка скрывается.
        {
                Edit1->Color=clWindow;
                Edit1->Hint="";
                Edit1->ShowHint=false;
        }
}
//---------------------------------------------------------------------------

