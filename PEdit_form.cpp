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

// Объявление глобальных переменных

String global_adr; // Адрес до изменений.
String global_pfn;  // Имя файла до изменений.
String global_pfp ; // Путь к добавляемому файлу (+имя файла).
int global_pid;  // Объявление глобальной переменной для корректного обновления строки таблицы.

TIniFile* iniFile;
String dirPath; // Путь к директории размещения презентаций
String iniFileName; // Имя ini-файла
String PresentFN; // Имя(+путь) файла презентации (вспомогательная переменная)

//---------------------------------------------------------------------------

// Заполнение имеющихся полей и глобальных переменных значениями из выбранной строки при создании формы.

void __fastcall TPEditForm::FormCreate(TObject *Sender)
{
        global_adr=MainForm->ADOTable2->FieldByName("Address")->AsString;
        global_pfn=MainForm->ADOTable2->FieldByName("PFN")->AsString;
        global_pid=MainForm->ADOTable2->FieldByName("pID")->AsInteger;

        PEditForm->Edit1->Text=MainForm->ADOTable2->FieldByName("Address")->AsString;
        PEditForm->Edit3->Text=MainForm->ADOTable2->FieldByName("District")->AsString;
        PEditForm->Edit4->Text=MainForm->ADOTable2->FieldByName("MetroStation")->AsString;
        PEditForm->DateTimePicker1->Date=MainForm->ADOTable2->FieldByName("aDate")->AsString;

        // Заполнение ListBox'a с площадьми

        String Areas; // Строка со значениями площадей.
        int ind=1; // Позиция вхождения в строку
        int cou; // Кол-во символов в строке

        Areas=MainForm->ADOTable2->FieldByName("Area")->AsString+";";
        do
        {
                // Переменной cou присваивается значение позиции первого вхождения символа ";" в строку Areas минус единица.

                cou=Areas.Pos(";")-1;

                /* Добавление в список нового элемента из подстроки величиной "cou" с позиции ind,
                   содержащейся в строке Areas. (Значение площади без знака ";".) */

                ListBox1->Items->Add(Areas.SubString(ind, cou));

                /* Удаление подстроки величиной "cou+1" с позиции ind, содержащейся в строке Areas.
                   (Значение площади со знаком ";".) */

                Areas.Delete(ind, cou+1);
        }
        while(!Areas.IsEmpty()); // Цикл совершает итерации, пока строка Areas не пуста.

        // Загрузка данных о презентации

        iniFileName=Application->ExeName+".ini"; // Задание имени файла - имя файла приложения + расширение ".ini".
        iniFile=new TIniFile(iniFileName);
        dirPath=iniFile->ReadString("data","dirPath",""); // Присваивание переменной dirPath значения ключа "dirPath" из секции "data".

        if (global_pfn!="") // Проверка наличия имени файла. Если имя есть...
        {
                /* Из пути до директории с приложением, имени папки с презентациями и
                   имени файла презентации формируется путь к сохраненной копии файла
                   презентации, который присваивается переменной PresentFN. */

                PresentFN=dirPath+"presents\\"+global_pfn;
                PEditForm->Image1->Picture->LoadFromFile(PresentFN); // Изображение из файла загружается в компонент Image1.

                /* Свойству Date компонента DateTimePicker2 присваивается значение поля "pDate" из выбранной строки.
                   (Дата добавления презентации.) */

                PEditForm->DateTimePicker2->Date=MainForm->ADOTable2->FieldByName("pDate")->AsString;

                // Далее изменяются свойства некоторых компонентов (надпись на кнопке, видимость компонентов).

                SpeedButton1->Caption="Изменить файл";
                SpeedButton5->Visible=true;
                Label3->Visible=true;
                DateTimePicker2->Visible=true;
        }
        else // Если имени нету...
        {
                /* Из пути до директории с приложением, имени папки с презентациями и
                   имени файла-заглушки формируется путь к файлу-заглушке,
                   который (путь) присваивается переменной PresentFN. */

                PresentFN=dirPath+"presents\\"+"not_found.jpg";
                PEditForm->Image1->Picture->LoadFromFile(PresentFN); // Изображение из файла загружается в компонент Image1.

                // Свойству Date компонента DateTimePicker2 присваивается значение текущей даты.

                PEditForm->DateTimePicker2->Date=Today();

                // Далее изменяются свойства некоторых компонентов (надпись на кнопке, видимость компонентов).

                SpeedButton1->Caption="Добавить файл";
                SpeedButton5->Visible=false;
                Label3->Visible=false;
                DateTimePicker2->Visible=false;
        }

        /* После всех операций значение переменной PresentFN содержит строку с
           абсолютной ссылкой к тому или иному файлу. Но эта переменная глобальная и
           для проверок в будущем необходимо, чтобы она содержала лишь имя файла.
           Присвоим ей значение имени файла до изменений. */

        PresentFN=global_pfn;
}
//---------------------------------------------------------------------------

// Закрытие формы

void __fastcall TPEditForm::Button2Click(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

// Добавление файла презентации

void __fastcall TPEditForm::SpeedButton1Click(TObject *Sender)
{
        do
        {
                if (MainForm->OpenDialog1->Execute()) // Открытие диалогового окна выбора файла и в случае нажатия кнопки "Ок"...
                {
                        bool loc; // Переменная для результата поиска.
                        TLocateOptions SearchOptions; // Опции поиска.
                        
                        PresentFN=ExtractFileName(MainForm->OpenDialog1->FileName); // В переменную PresentFN записывается имя выбранного файла.
                        loc=MainForm->ADOTable2->Locate("PFN", PresentFN, SearchOptions); // Идет поиск этого имени в таблице.

                        /* Если такое имя найдено и оно совпадает с именем файла до изменений,
                           осуществляется подмена значения результата поиска на противоположное. */

                        if (loc==true && global_pfn==MainForm->ADOTable2->FieldByName("PFN")->AsString)
                        {
                                loc=false;
                        }

                        /* Если такое имя найдено и оно не совпадает с именем файла до изменений,
                           выводится сообщение об ошибке. */

                        if (loc)
                        {
                               MessageDlg("Такой файл уже добавлен." ,mtError, TMsgDlgButtons()<<mbOK,0);
                        }
                        else // В противном случае...
                        {
                                /* Переменной global_pfp присваивается полный путь до
                                   выбранного файла вместе с именем файла. */

                                global_pfp=MainForm->OpenDialog1->FileName;

                                /* Если изначально презентации не было, переменной global_pfn
                                   присваивается имя выбранного файла. */

                                if (global_pfn=="")
                                {
                                        global_pfn=PresentFN;
                                }

                                // Изображение из выбранного файла загружается в компонент Image1.

                                Image1->Picture->LoadFromFile(global_pfp);

                                // Свойству Date компонента DateTimePicker2 присваивается значение текущей даты.

                                DateTimePicker2->Date=Today();

                                // Далее изменяются свойства некоторых компонентов (надпись на кнопке, видимость компонентов).

                                SpeedButton1->Caption="Изменить файл";
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
        while (global_pfp==""); // Цикл совершает итерации до тех пор, пока переменной global_pfp не будет присвоено значение пути до файла.
}
//---------------------------------------------------------------------------

// Сохранение отредактированных данных в БД.

void __fastcall TPEditForm::Button1Click(TObject *Sender)
{
        bool loc; // Переменная для значения результата поиска.
        TLocateOptions SearchOptions;
        SearchOptions<<loCaseInsensitive; // Опции поиска: нечувствительность к регистру.
        String Areas; // Строка со значениями площадей из ListBox.

        if (ListBox1->Items->Count>0) // Проверка на наличие в ListBox'e элементов и если они есть...
        {
                for (int i=0; i<ListBox1->Items->Count; i++) // Перебор элементов списка.
                {
                        Areas+=ListBox1->Items->Strings[i]+";"; // Запись элементов списка в строку Areas через знак ";".
                }
                Areas.Delete(Areas.Length(),1); // Удаляем из конца строки знак ";".
        }

        loc=MainForm->ADOTable2->Locate("Address", Edit1->Text, SearchOptions); // Поиск введенного адреса в таблице.

        /* Если такой адрес найден и он совпадает с адресом до изменений,
           осуществляется подмена значения результата поиска на противоположное. */

        if (loc==true && global_adr==MainForm->ADOTable2->FieldByName("Address")->AsString)
        {
                loc=false;
        }

        /* Если такой адрес найден и он не совпадает с адресом до изменений,
           выводится сообщение с ошибкой. */

        if (loc)
        {
                MessageDlg("Такой адрес уже существует." ,mtError, TMsgDlgButtons()<<mbOK,0);
        }
        else
        {
                // Проверяем, заполнены ли все необходимые поля. Если нет - вывод сообщения об ошибке.

                if (Edit1->Text=="" || ListBox1->Items->Text=="" || Edit3->Text=="" || Edit4->Text=="")
                {
                        MessageDlg("Одно из полей 'Адрес', 'Список площадей', 'Район', 'Станция метро' не заполнено !" ,mtError, TMsgDlgButtons()<<mbOK,0);
                }
                else
                {
                        MainForm->ADOQuery2->Close();
                        MainForm->ADOQuery2->SQL->Clear();
                        String s;// Переменная для строки SQL-запроса.

                        // Проверяем, добавлен ли файл презентации.

                        if (global_pfn!="")
                        {
                                // Если файл добавлен, формируем SQL-запрос с учетом этого...

                                s="UPDATE PresentsTable SET Address='"+PEditForm->Edit1->Text+"', Area='"+Areas+"', District='"+PEditForm->Edit3->Text+"', MetroStation='"+PEditForm->Edit4->Text+"', aDate='"+PEditForm->DateTimePicker1->Date+"', PFN='"+PresentFN+"', pDate='"+PEditForm->DateTimePicker2->Date+"' WHERE pID="+global_pid+";";

                                // И заменяем старую копию файла презентации новой.

                                iniFileName=Application->ExeName+".ini"; // Задание имени файла - имя файла приложения + расширение ".ini".
                                iniFile=new TIniFile(iniFileName);
                                dirPath=iniFile->ReadString("data","dirPath",""); // Присваивание переменной dirPath значения ключа "dirPath" из секции "data".

                                /* Из пути до директории с приложением, имени папки с презентациями и
                                   имени файла презентации формируется путь к старой копии файла
                                   презентации, который присваивается переменной global_pfn. */

                                global_pfn=dirPath+"presents\\"+global_pfn;
                                DeleteFile(global_pfn); // Удаление старой копии файла.

                                /* Из пути до директории с приложением, имени папки с презентациями и
                                   имени файла презентации формируется путь сохранения копии файла
                                   презентации, который присваивается переменной PresentFN. */

                                PresentFN=dirPath+"presents\\"+PresentFN;

                                /* Копирование выбранного файла в директорию и с именем, указанными в переменной PresentFN.
                                   В случае, если файл с таким именем уже существует, он будет заменен. */

                                CopyFile(global_pfp.c_str(),PresentFN.c_str(),false);
                        }
                        else
                        {
                                // Если файл не добавлен, формируем SQL-запрос с учетом этого...

                                s="UPDATE PresentsTable SET Address='"+PEditForm->Edit1->Text+"', Area='"+Areas+"', District='"+PEditForm->Edit3->Text+"', MetroStation='"+PEditForm->Edit4->Text+"', aDate='"+PEditForm->DateTimePicker1->Date+"', PFN=NULL, pDate=NULL WHERE pID="+global_pid+";";
                        }

                        // Отправляем SQL-запрос в БД.

                        MainForm->ADOQuery2->SQL->Add(s);
                        MainForm->ADOQuery2->ExecSQL();

                        // Обновляем таблицу

                        MainForm->ADOTable2->Close();
                        MainForm->ADOTable2->Open();

                        PEditForm->Close(); // Закрываем форму.
                }
        }
}
//---------------------------------------------------------------------------

// Проверка совпадения адреса еще на стадии ввода

void __fastcall TPEditForm::Edit1Change(TObject *Sender)
{
        bool loc; // Переменная для результата поиска.
        TLocateOptions SearchOptions;
        SearchOptions<<loCaseInsensitive; // Опции поиска: нечувствительность к регистру.
        
        loc=MainForm->ADOTable2->Locate("Address", Edit1->Text, SearchOptions); // Поиск вводимого адреса в таблице.

        /* Если адрес найден и он совпадает с адресом до изменений,
           осуществляется подмена значения результата поиска на противоположное. */

        if (loc==true && global_adr==MainForm->ADOTable2->FieldByName("Address")->AsString)
        {
                loc=false;
        }

        /* Если адрес найден и он не совпадает с адресом до изменений,
           цвет поля "Адрес" сменяется на розовый, добавляется всплывающая подсказка. */

        if (loc)
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

void __fastcall TPEditForm::SpeedButton2Click(TObject *Sender)
{
        if (Edit2->Text!="") // Проверка на наличие в поле "Площадь" текста.
        {
                if (ListBox1->Items->Count>0) // Проверка на наличие в ListBoxe'e элементов
                {
                        int i; // Счетчик цикла
                        for (i=0; i<ListBox1->Items->Count; i++) // Перебираем эл-ты списка
                        {
                                /* Если есть совпадение данного эл-та списка с текстом из поля "Площадь",
                                   вывод сообщения об ошибке и выход из цикла. */

                                if (Edit2->Text==ListBox1->Items->Strings[i])
                                {
                                        MessageDlg("Такая площадь уже есть." ,mtError, TMsgDlgButtons()<<mbOK,0);
                                        break;
                                }
                        }
                        if (i==ListBox1->Items->Count) // Проверка, были ли перебраны все элементы списка.
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

void __fastcall TPEditForm::SpeedButton3Click(TObject *Sender)
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

void __fastcall TPEditForm::SpeedButton4Click(TObject *Sender)
{
        ListBox1->Clear();
}
//---------------------------------------------------------------------------

// Удаление файла презентации

void __fastcall TPEditForm::SpeedButton5Click(TObject *Sender)
{
        if (MessageBox(0,"Вы действительно хотите удалить копию файла презентации?","Подтвердите удаление",MB_YESNO)==IDYES);
        {
                iniFileName=Application->ExeName+".ini"; // Задание имени файла - имя файла приложения + расширение ".ini".
                iniFile=new TIniFile(iniFileName);
                dirPath=iniFile->ReadString("data","dirPath",""); // Присваивание переменной dirPath значения ключа "dirPath" из секции "data".

                /* Из пути до директории с приложением, имени папки с презентациями и
                   имени файла презентации формируется путь к сохраненной копии файла
                   презентации, который присваивается переменной global_pfn. */

                global_pfn=dirPath+"presents\\"+global_pfn;
                DeleteFile(global_pfn); // Удаление копии файла презентации

                /* Из пути до директории с приложением, имени папки с презентациями и
                   имени файла-заглушки формируется путь к файлу-заглушке,
                   который (путь) присваивается переменной PresentFN. */

                PresentFN=dirPath+"presents\\"+"not_found.jpg";
                PEditForm->Image1->Picture->LoadFromFile(PresentFN); // Изображение из файла-заглушки загружается в компонент Image1.

                /* После всех операций значения переменных global_pfn и PresentFN содержат строки с
                   абсолютными ссылками к тем или иным файлам. Однако, прикрепленного файла
                   презентации теперь нет, следовательно этим переменным надо присвоить значение пустой строки. */

                global_pfn="";
                PresentFN="";

                // Формируем и отправлем SQL-запрос в БД, обновляем таблицу.

                MainForm->ADOQuery2->Close();
                MainForm->ADOQuery2->SQL->Clear();
                String s="UPDATE PresentsTable SET PFN='"+PresentFN+"', pDate=NULL WHERE pID="+global_pid+";";
                MainForm->ADOQuery2->SQL->Add(s);
                MainForm->ADOQuery2->ExecSQL();
                MainForm->ADOTable2->Close();
                MainForm->ADOTable2->Open();

                // Далее изменяются свойства некоторых компонентов (надпись на кнопке, видимость компонентов).

                SpeedButton1->Caption="Добавить файл";
                SpeedButton5->Visible=false;
                Label3->Visible=false;
                DateTimePicker2->Visible=false;
        }
}
//---------------------------------------------------------------------------

