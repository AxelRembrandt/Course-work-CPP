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
        // Устанавка у DateTimePicker'ов текущей даты.

        DateTimePicker1->Date=Today();
        DateTimePicker2->Date=Today();
}
//---------------------------------------------------------------------------

String global_PFN; // Объявление глобальной пременной для имени файла презентации

//---------------------------------------------------------------------------

// Закрытие формы

void __fastcall TPAddForm::Button2Click(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

// Добавление записи в БД

void __fastcall TPAddForm::Button1Click(TObject *Sender)
{
        String AreaList; // Строка со значениями площадей из ListBox.
        bool loc; // Переменная для значения результата поиска.
        TLocateOptions SearchOptions; // Опции поиска.

        if (ListBox1->Items->Count>0) // Проверка на наличие в ListBox'e элементов и если они есть...
        {
                for (int i=0; i<ListBox1->Items->Count; i++) // Перебор элементов списка.
                {
                        AreaList+=ListBox1->Items->Strings[i]+";"; // Запись элементов списка в строку AreaList через знак ";".
                }
                AreaList=AreaList.Delete(AreaList.Length(),1); // Удаляем из конца строки знак ";".
        }

        // Проверяем, добавлен ли уже такой адрес в таблицу. Если да - вывод сообщения об ошибке.

        loc=MainForm->ADOTable2->Locate("Address", Edit1->Text, SearchOptions);
        if (loc)
        {
                MessageDlg("Такой адрес уже существует." ,mtError, TMsgDlgButtons()<<mbOK,0);
        }
        else
        {
                // Проверяем, заполнены ли все необходимые поля. Если нет - вывод сообщения об ошибке.

                if (Edit1->Text=="" || AreaList=="" || Edit3->Text=="" || Edit4->Text=="")
                {
                        MessageDlg("Одно из полей 'Адрес', 'Список площадей', 'Район', 'Станция метро' не заполнено !" ,mtError, TMsgDlgButtons()<<mbOK,0);
                }
                else
                {
                        MainForm->ADOQuery2->Close();
                        MainForm->ADOQuery2->SQL->Clear();
                        String s; // Переменная для строки SQL-запроса.

                        // Проверяем, добавлен ли файл презентации.

                        if (global_PFN!="")
                        {
                                // Если файл добавлен, формируем SQL-запрос с учетом этого...

                                s="INSERT INTO PresentsTable (Address, Area, District, MetroStation, aDate, PFN, pDate) VALUES ('"+PAddForm->Edit1->Text+"','"+AreaList+"','"+PAddForm->Edit3->Text+"','"+PAddForm->Edit4->Text+"','"+PAddForm->DateTimePicker1->Date+"','"+global_PFN+"','"+PAddForm->DateTimePicker2->Date+"');";

                                // И копируем этот файл в директорию с презентациями.

                                TIniFile* iniFile;
                                String dirPath; // Путь к директории размещения презентаций
                                String iniFileName; // Имя ini-файла
                                String PresentFN=""; // Имя(+путь) файла презентации

                                iniFileName=Application->ExeName+".ini"; // Задание имени файла - имя файла приложения + расширение ".ini".
                                iniFile=new TIniFile(iniFileName);
                                dirPath=iniFile->ReadString("data","dirPath",""); // Присваивание переменной dirPath значения ключа "dirPath" из секции "data".

                                /* Из пути до директории с приложением, имени папки с презентациями и
                                   имени файла презентации формируется путь сохранения копии файла
                                   презентации, который присваивается переменной PresentFN. */

                                PresentFN=dirPath+"presents\\"+PresentFN;

                                /* Копирование выбранного файла в директорию и с именем, указанными в переменной PresentFN.
                                   В случае, если файл с таким именем уже существует, он будет заменен. */

                                CopyFile(MainForm->OpenDialog1->FileName.c_str(),PresentFN.c_str(),false);
                        }
                        else
                        {
                                // Если файл не добавлен, формируем SQL-запрос с учетом этого...

                                s="INSERT INTO PresentsTable (Address, Area, District, MetroStation, aDate) VALUES ('"+PAddForm->Edit1->Text+"','"+AreaList+"','"+PAddForm->Edit3->Text+"','"+PAddForm->Edit4->Text+"','"+PAddForm->DateTimePicker1->Date+"');";
                        }

                        // Отправляем SQL-запрос в БД.

                        MainForm->ADOQuery2->SQL->Add(s);
                        MainForm->ADOQuery2->ExecSQL();

                        // Обновляем таблицу

                        MainForm->ADOTable2->Close();
                        MainForm->ADOTable2->Open();

                        PAddForm->Close(); //Закрываем форму
                }
        }
}
//---------------------------------------------------------------------------

// Добавление файла презентации

void __fastcall TPAddForm::SpeedButton1Click(TObject *Sender)
{
        do
        {
                if (MainForm->OpenDialog1->Execute()) // Открытие диалогового окна выбора файла и в случае нажатия кнопки "Ок"...
                {
                        bool loc; // Переменная для результата поиска.
                        TLocateOptions SearchOptions; // Опции поиска.

                        String PresentFN=ExtractFileName(MainForm->OpenDialog1->FileName); // В переменную PresentFN записывается имя выбранного файла.
                        loc=MainForm->ADOTable2->Locate("PFN", PresentFN, SearchOptions); // Идет поиск этого имени в таблице.
                        if (loc) // Если такое имя найдено, вывод сообщения о ошибке.
                        {
                               MessageDlg("Такой файл уже добавлен." ,mtError, TMsgDlgButtons()<<mbOK,0);
                        }
                        else
                        {
                                /* Если совпадений не найдено, переменной global_PFN присваивается имя файла,
                                   изображение из файла загружается в компонент Image1,
                                   изменяются свойства некоторых компонентов (надпись на кнопке, видимость компонентов) */

                                global_PFN=PresentFN;
                                SpeedButton1->Caption="Изменить файл";
                                Image1->Picture->LoadFromFile(MainForm->OpenDialog1->FileName);
                                SpeedButton5->Visible=true;
                                Label3->Visible=true;
                                DateTimePicker2->Visible=true;
                        }
                }
                else // Если в диалоговом окне нажата кнопка "Отмена", выход из цикла.
                {
                        break;
                }
        }
        while (global_PFN==""); // Цикл совершает итерации до тех пор, пока переменной global_PFN не будет присвоено значение имени файла.
}
//---------------------------------------------------------------------------

// Проверка совпадения адреса еще на стадии ввода

void __fastcall TPAddForm::Edit1Change(TObject *Sender)
{
        bool loc; // Переменная для результата поиска
        TLocateOptions SearchOptions;
        SearchOptions<<loCaseInsensitive; // Опции поиска: нечувствительность к регистру.

        loc=MainForm->ADOTable2->Locate("Address", Edit1->Text, SearchOptions); // Поиск вводимого адреса в таблице.
        if (loc) // Если адрес найден: цвет поля "Адрес" сменяется на розовый, добавляется всплывающая подсказка.
        {
                Edit1->Color=0x00C1C1FF;
                Edit1->Hint="Такой адрес уже существует.";
                Edit1->ShowHint=true;
        }
        else // Если адрес не найден: цвет поля "Адрес" сменяется на цвет окна, всплывающая подсказка скрывается.
        {
                Edit1->Color=clWindow;
                Edit1->Hint="";
                Edit1->ShowHint=false;
        }
}
//---------------------------------------------------------------------------

// Добавление нового значения площади в список по нажатию кнопки "Добавить в список"

void __fastcall TPAddForm::SpeedButton2Click(TObject *Sender)
{
        if (Edit2->Text!="") // Проверка на наличие в поле "Площадь" текста.
        {
                if (ListBox1->Items->Count>0) // Проверка на наличие в ListBoxe'e элементов
                {
                        int i; // Счетчик цикла
                        for (i=0; i<ListBox1->Items->Count; i++) // Перебираем эл-ты ListBox'a
                        {
                                /* Если есть совпадение данного эл-та списка с текстом из поля "Площадь",
                                   вывод сообщения об ошибке и выход из цикла. */

                                if (Edit2->Text==ListBox1->Items->Strings[i])
                                {
                                        MessageDlg("Такая площадь уже есть." ,mtError, TMsgDlgButtons()<<mbOK,0);
                                        break;
                                }
                        }
                        if (i==ListBox1->Items->Count) // Проверка, были ли перебраны все эл-ты списка.
                        {
                                /* Если были перебраны все эл-ты списка и не было найдено совпадений
                                   с текстом из поля "Площадь", этот текст добавляется в список,
                                   а само поле очищается. */

                                ListBox1->Items->Add(Edit2->Text);
                                Edit2->Text="";
                        }
                }
                else // Если элементов нет, текст добавляется из поля "Площадь" в ListBox, а само поле очищается.
                {
                        ListBox1->Items->Add(Edit2->Text);
                        Edit2->Text="";
                }
        }
}
//---------------------------------------------------------------------------

// Удаление выделенной строки из списка по нажатию кнопки "Удалить из списка"

void __fastcall TPAddForm::SpeedButton3Click(TObject *Sender)
{
        if (ListBox1->ItemIndex==-1) // Проверка, выделен ли какой-либо эл-т списка.
        {
                ShowMessage("Выделите удаляемое значение.");
        }
        else
        {
                ListBox1->DeleteSelected(); // Удаление выделенного элемента.
        }
}
//---------------------------------------------------------------------------

// Очистка списка по нажатию кнопки "Очистить список"

void __fastcall TPAddForm::SpeedButton4Click(TObject *Sender)
{
        ListBox1->Clear();
}
//---------------------------------------------------------------------------

/* Удаление файла презентации. (По факту файл не удаляется.
   Очищается лишь значение переменной, содержащей имя файла,
   и изменяются свойства некоторых компонентов.) */

void __fastcall TPAddForm::SpeedButton5Click(TObject *Sender)
{
        global_PFN="";
        SpeedButton1->Caption="Добавить файл";
        Image1->Picture=0;
        SpeedButton5->Visible=false;
        Label3->Visible=false;
        DateTimePicker2->Visible=false;
}
//---------------------------------------------------------------------------

