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

// Действия при создании формы приложения

void __fastcall TMainForm::FormCreate(TObject *Sender)
{

// Настройка почтовика

        TIniFile* iniFile;
        String iniFileName; // Имя ini-файла
        String dirPath; // Путь до файла приложения
        String host,port,username,password; // Имя хоста, номер порта, логин, пароль

        iniFileName=Application->ExeName+".ini"; // Задание имени файла - имя файла приложения + расширение ".ini".
        iniFile=new TIniFile(iniFileName);

        /* Считывание из ini-файла имени хоста, номера порта, логина, пароля и
           занесение этих значений в соответствующие переменные. */

        host=iniFile->ReadString("post","host","");
        port=iniFile->ReadString("post","port","");
        username=iniFile->ReadString("post","username","");
        password=iniFile->ReadString("post","password","");

        // Если какого-то из этих значений нету, выводится сообщение с ошибкой.

        if (host=="" || port=="" || username=="" || password=="")
        {
                MessageDlg("Ошибка чтения из файла " + iniFile->FileName + ". Один из параметров не имеет значения." ,mtError, TMsgDlgButtons()<<mbOK,0);
        }
        else
        {
                /* Запись имени хоста, номера порта, логина, пароля в
                   соответствующие свойства компонента IdSMTP1. */

                IdSMTP1->Host=host;
                IdSMTP1->Port=StrToInt(port);
                IdSMTP1->UserId=username;
                IdSMTP1->Password=password;
        }

        Edit1->Text=username; // Запись логина в поле "От кого".

// Заполнение комбобокса2(страница "Письмо" поле "Кому") итемами [E-mail адрес]

        // Формируем и отправляем в БД SQL-запрос, возвращающий столбец Email.

        ADOQuery1->Close();
        ADOQuery1->SQL->Clear();
        String s="SELECT Email FROM EmailTable";
        ADOQuery1->SQL->Add(s);
        ADOQuery1->Open();

        // Перевод указателя на первый элемент, возвращенный в результате запроса.

        ADOQuery1->First();

        // Перебор всех элементов и их добавление в ComboBox.

        while (!ADOQuery1->Eof)
        {
                ComboBox2->Items->Add(ADOQuery1->FieldByName("Email")->AsString);
                ADOQuery1->Next();
        }
        ADOQuery1->Close();

// Установка у DateTimePicker'а текущей даты.

        DateTimePicker1->Date=Today();
}
//---------------------------------------------------------------------------

/* Настройка соединения с БД так, чтобы приложение запускалось из
любой директории при условии, что БД и папка с презентациями находятся в
одной директории с приложением.*/

void __fastcall TMainForm::ADOConnection1BeforeConnect(TObject *Sender)
{
        TIniFile* iniFile;
        String dirPath; // Путь к директории размещения БД
        String conString1,conString2,cs; // Строки соединения
        String DBFileName; // Имя файла базы данных
        String iniFileName; // Имя ini-файла

        String AppName; // Имя файла приложения
        int ind, cou; // Позиция вхождения в строку, кол-во символов в строке.

        // Запись в ini-файл пути до текущей директории приложения

        iniFileName=Application->ExeName+".ini"; // Задание имени файла - имя файла приложения + расширение ".ini".
        iniFile=new TIniFile(iniFileName);
        AppName=ExtractFileName(Application->ExeName); // Запись имени файла приложения в переменную AppName.
        cou=AppName.Length(); // Запись кол-ва символов в имени файла приложения в переменную cou.

        // Запись в переменную ind позиции вхождения имени файла приложения в строку, содержащую путь к файлу приложения.

        ind=Application->ExeName.Pos(AppName);

        // Из строки, содержащей путь к файлу приложения, удаляется имя файла и полученный путь пишется в переменную dirPath.

        dirPath=Application->ExeName.Delete(ind, cou);

        // Путь к директории, содерждащей приложение, записывается в ini-файл в секцию "data", как значение ключа "dirPath".

        iniFile->WriteString("data","dirPath",dirPath);

        /* Считывание из ini-файла пути до директории с приложением,
           2-х частей строки соединения и имени БД и
           занесение этих значений в соответсвующие переменные. */

        dirPath=iniFile->ReadString("data","dirPath","");
        conString1=iniFile->ReadString("data","conString1","");
        DBFileName=iniFile->ReadString("data","DBFileName","");
        conString2=iniFile->ReadString("data","conString2","");

        // Если какого-то из этих значений нету, выводится сообщение с ошибкой.

        if (dirPath=="" || conString1=="" || DBFileName=="" || conString2=="")
        {
                MessageDlg("Ошибка чтения из файла " + iniFile->FileName + ". Один из параметров не имеет значения." ,mtError, TMsgDlgButtons()<<mbOK,0);
        }
        else
        {
                // Формирование строки соединения с БД из имеющихся частей.

                cs=conString1+dirPath+DBFileName+conString2;

                // Помещение получившейся строки в св-во ConnectionString компонента ADOConnection1.

                ADOConnection1->ConnectionString = cs;
        }
}
//---------------------------------------------------------------------------

// Закрытие приложения

void __fastcall TMainForm::N2Click(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

// Открытие формы добавления нового контакта

void __fastcall TMainForm::SpeedButton1Click(TObject *Sender)
{
        Application->CreateForm(__classid(TEAddForm), &EAddForm);
        EAddForm->ShowModal();
        EAddForm->Free();
}
//---------------------------------------------------------------------------

// Открытие формы редактирования выделенной записи (Контакты)

void __fastcall TMainForm::SpeedButton2Click(TObject *Sender)
{
        Application->CreateForm(__classid(TEEditForm), &EEditForm);
        EEditForm->ShowModal();
        EEditForm->Free();
}
//---------------------------------------------------------------------------

// Удаление выделенной записи (Контакты)

void __fastcall TMainForm::SpeedButton3Click(TObject *Sender)
{
        if (MessageBox(0,"Вы действительно хотите удалить выделенную запись?","Подтвердите удаление",MB_YESNO)==IDYES);
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

// Отображение коментария к записи (Контакты) по клику по ячейке

void __fastcall TMainForm::DBGrid1CellClick(TColumn *Column)
{
        Memo1->Lines->Clear(); // Очистка имеющегося текста из компонента Memo1.

        // Проверка поля "eComment" на наличие в нем текста.

        if (ADOTable1->FieldByName("eComment")->AsString!="")
        {
                // Если поле "eComment" не пустое, его содержимое помещается в Memo1.

                Memo1->Text=ADOTable1->FieldByName("eComment")->AsString;
        }
        else
        {
                // Если поле "eComment" пустое, в Memo1 прописывается сообщение об этом.

                Memo1->Text="К этой записи нет коментария.";
        }
}

//---------------------------------------------------------------------------

// Отображение презентации (вкладка Презентации) по клику по ячейке

void __fastcall TMainForm::DBGrid2CellClick(TColumn *Column)
{
        TIniFile* iniFile;
        String dirPath; // Путь к директории размещения презентаций
        String iniFileName; // Имя ini-файла
        String PresentFN; // Имя(+путь) файла презентации

        iniFileName=Application->ExeName+".ini"; // Задание имени файла - имя файла приложения + расширение ".ini".
        iniFile=new TIniFile(iniFileName);
        dirPath=iniFile->ReadString("data","dirPath",""); // Считывание из ini-файла пути к директории с приложением.

        // Проверяется, есть ли имя презентации в поле "PFN".

        if (ADOTable2->FieldByName("PFN")->AsString!="")
        {
                /* Из пути до директории с приложением, имени папки с презентациями и
                   имени файла презентации формируется путь к сохраненной копии файла
                   презентации, который присваивается переменной PresentFN. */

                PresentFN=ADOTable2->FieldByName("PFN")->AsString;
                PresentFN=dirPath + "presents\\" + PresentFN;
        }
        else // Если имени нету..
        {
                /* Из пути до директории с приложением, имени папки с презентациями и
                   имени файла-заглушки формируется путь к файлу-заглушке,
                   который (путь) присваивается переменной PresentFN. */

                PresentFN=dirPath+"presents\\"+"not_found.jpg";
        }
        Image1->Picture->LoadFromFile(PresentFN); // Изображение из файла загружается в компонент Image1.
}
//---------------------------------------------------------------------------

// Открытие формы добавления презентации

void __fastcall TMainForm::SpeedButton9Click(TObject *Sender)
{
        Application->CreateForm(__classid(TPAddForm), &PAddForm);
        PAddForm->ShowModal();
        PAddForm->Free();
}
//---------------------------------------------------------------------------

// Открытие формы изменения презентации

void __fastcall TMainForm::SpeedButton10Click(TObject *Sender)
{
        Application->CreateForm(__classid(TPEditForm), &PEditForm);
        PEditForm->ShowModal();
        PEditForm->Free();
}
//---------------------------------------------------------------------------

// Удаление выделенной записи адреса и презентации из БД и копии файла из директории с презентациями

void __fastcall TMainForm::SpeedButton11Click(TObject *Sender)
{
        if (MessageBox(0,"Вы действительно хотите удалить выделенную запись и копию файла презентации?","Подтвердите удаление",MB_YESNO)==IDYES);
        {
                // Проверяется, есть ли имя презентации в поле "PFN".

                if (ADOTable2->FieldByName("PFN")->AsString!="")
                {
                        TIniFile* iniFile;
                        String dirPath; // Путь к директории размещения презентаций
                        String iniFileName; // Имя ini-файла
                        String PresentFN=ADOTable2->FieldByName("PFN")->AsString; // Имя(+путь) файла презентации

                        iniFileName=Application->ExeName+".ini"; // Задание имени файла - имя файла приложения + расширение ".ini".
                        iniFile=new TIniFile(iniFileName);
                        dirPath=iniFile->ReadString("data","dirPath",""); // Считывание из ini-файла пути к директории с приложением.

                        /* Из пути до директории с приложением, имени папки с презентациями и
                           имени файла презентации формируется путь к сохраненной копии файла
                           презентации, который присваивается переменной PresentFN. */

                        PresentFN=dirPath+"presents\\"+PresentFN;
                        DeleteFile(PresentFN); // Удаление указанной копии файла из папки с презентациями.
                }

                // Формирование SQL-запроса, отправление его в БД и обновление таблицы.

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

// Отправление письма

void __fastcall TMainForm::SpeedButton6Click(TObject *Sender)
{
        // Проверка заполненности полей "Кому" и "Текст письма".

        if (ComboBox2->Text=="" || Memo2->Text=="")
        {
                // Если одно из этих полей не заполнено, вывод сообщения с ошибкой.

                MessageDlg("Одно из полей не заполнено!" ,mtError, TMsgDlgButtons()<<mbOK,0);
        }
        else
        {
                if (MessageBox(0,"Вы уверены, что хотите отправить письмо?","Подтвердите отправку письма",MB_YESNO)==IDYES);
                {
                        // Заполнение свойств компонента IdMessage1.

                        IdMessage1->From->Text = Edit1->Text;
                        IdMessage1->Recipients->EMailAddresses = ComboBox2->Text;
                        IdMessage1->Subject = Edit2->Text;
                        IdMessage1->Body->Text = Memo2->Text;

                        IdSMTP1->Connect(); // Открытие соединения с почтовым сервером.
                        if (IdSMTP1->Connected()) // Если соединение прошло успешно...
                        {
                                bool SendInd=0; // "Переменная-индикатор" отправленного письма.
                                try
                                {
                                        IdSMTP1->Send(IdMessage1); // Отправка письма.
                                        SendInd=1;
                                }
                                catch(...)
                                {
                                        // Если по какой-либо причине письмо не было отправлено, вывод сообщения с ошибкой.

                                        MessageDlg("Произошла ошибка! Письмо не отправлено." ,mtError, TMsgDlgButtons()<<mbOK,0);
                                        SendInd=0;
                                }
                                if (SendInd) // Если письмо было отправлено...
                                {
                                        // Проверка, была ли прикреплена презентация. (Для подсчета статистики.)

                                        if(CheckBox1->Checked==true && ComboBox1->Text!="")
                                        {
                                                // Берем имя файла презентации из ComboBox1->Text, ищем его в таблице.

                                                TLocateOptions SearchOptions;
                                                bool loc=MainForm->ADOTable2->Locate("PFN", ComboBox1->Text, SearchOptions);
                                                if (loc) // Если имя было найдено...
                                                {
                                                        /* Выбираем найденную строку, считываем
                                                           значение, содержащееся в поле "pStat". */

                                                        int pst=ADOTable2->FieldByName("pStat")->AsInteger;
                                                        pst++; // Увеличиваем это значение на единицу.

                                                        /* Формируем и отправляем в БД SQL-запрос, обновляющий поле "pStat".
                                                           Обновляем таблицу. */

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
                                        MessageDlg("Письмо успешно отправлено." ,mtInformation, TMsgDlgButtons()<<mbOK,0);
                                }
                        }
                        IdSMTP1->Disconnect(); // Закрытие соединения с почтовым сервером.
                }
        }
}
//---------------------------------------------------------------------------

/* Выбор пользователем прикрепления презентации или отказ от этого выбора
        и следующие за этим отображение или скрытие элементов интерфейса */

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

// Переход на вкладку "Презентации" по нажатию на псевдоссылку.

void __fastcall TMainForm::Label10Click(TObject *Sender)
{
        PageControl1->ActivePage=TabSheet3;
}
//---------------------------------------------------------------------------

/* Заполнение компонентов данными, необходимыми для прикрепления презентации,
        по нажатию кнопки "Прикрепить к письму" на странице презентаций */

void __fastcall TMainForm::SpeedButton8Click(TObject *Sender)
{
        /* Перевод CheckBox'a в положение "Выбрано",
           из выбранной строки занесение в поля значений:
           "Презентация" - имени файла презентации;
           "Дата добавления презентации" - даты добавления презентации. */

        CheckBox1->Checked=true;
        ComboBox1->Text=ADOTable2->FieldByName("PFN")->AsString;
        DateTimePicker1->Date=ADOTable2->FieldByName("pDate")->AsString;

        TIniFile* iniFile;
        String dirPath; // Путь к директории размещения презентаций
        String iniFileName; // Имя ini-файла
        String PresentFN; // Имя(+путь) файла презентации

        iniFileName=Application->ExeName+".ini"; // Задание имени файла - имя файла приложения + расширение ".ini".
        iniFile=new TIniFile(iniFileName);
        dirPath=iniFile->ReadString("data","dirPath",""); // Считывание из ini-файла пути к директории с приложением.

        PresentFN=ComboBox1->Text; // Присваивание переменной PresentFN имени файла.

        /* Из пути до директории с приложением, имени папки с презентациями и
           имени файла презентации формируется путь к сохраненной копии файла
           презентации, который присваивается переменной PresentFN. */

        PresentFN=dirPath + "presents\\" + PresentFN;

        // Изображение из файла загружается в компонент Image1.

        Image2->Picture->LoadFromFile(PresentFN);

        /* Далее происходит переключение с текущей вкладки на вкладку "Письмо" и
           передача фокуса полю "Презентация". */

        PageControl1->ActivePage=TabSheet1;
        ComboBox1->SetFocus();
}
//---------------------------------------------------------------------------

// Отображение презентации при ее выборе из ComboBox'a.

void __fastcall TMainForm::ComboBox1Select(TObject *Sender)
{
        TIniFile* iniFile;
        String dirPath; // Путь к директории размещения презентаций
        String iniFileName; // Имя ini-файла
        String PresentFN; // Имя(+путь) файла презентации

        iniFileName=Application->ExeName+".ini"; // Задание имени файла - имя файла приложения + расширение ".ini".
        iniFile=new TIniFile(iniFileName);
        dirPath=iniFile->ReadString("data","dirPath",""); // Считывание из ini-файла пути к директории с приложением.

        PresentFN=ComboBox1->Text; // Присваивание переменной PresentFN имени файла.

        /* Из пути до директории с приложением, имени папки с презентациями и
           имени файла презентации формируется путь к сохраненной копии файла
           презентации, который присваивается переменной PresentFN. */

        PresentFN=dirPath + "presents\\" + PresentFN;

        // Изображение из файла загружается в компонент Image1.

        Image2->Picture->LoadFromFile(PresentFN);
}
//---------------------------------------------------------------------------

// Очищение все полей, кроме "От кого", на странице "Письмо"

void __fastcall TMainForm::SpeedButton7Click(TObject *Sender)
{
        if (MessageBox(0,"Вы уверены, что хотите очистить поля?","Подтвердите очистку",MB_YESNO)==IDYES);
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

/* Заполнение комбобокса1(страница "Письмо" поле "Прикрепить презентацию")
итемами [Имя файла презентации] в зависимости от выбора пользователем даты.*/

void __fastcall TMainForm::ComboBox1DropDown(TObject *Sender)
{
        ComboBox1->Items->Clear(); // Очистка выпадающего списка ComboBox'a

        /* Формирование и отправка в БД SQL-запроса, возвращающего значения
           полей "PFN", если значение поля "pDate" совпадает с выбранной
           пользователем датой. */

        ADOQuery2->Close();
        ADOQuery2->SQL->Clear();
        String s="SELECT PFN FROM PresentsTable WHERE pDate LIKE '"+DateTimePicker1->Date+"';";
        ADOQuery2->SQL->Add(s);
        ADOQuery2->Open();

        // Перевод указателя на первый элемент, возвращенный в результате запроса.

        ADOQuery2->First();

        // Перебор всех элементов и их добавление в ComboBox.

        while (!ADOQuery2->Eof)
        {
                ComboBox1->Items->Add(ADOQuery2->FieldByName("PFN")->AsString);
                ADOQuery2->Next();
        }
        ADOQuery2->Close();
}
//---------------------------------------------------------------------------

// Активация "Добавления презентации" через Меню.

void __fastcall TMainForm::N14Click(TObject *Sender)
{
        CheckBox1->Checked=!CheckBox1->Checked;
}
//---------------------------------------------------------------------------

/* Скрытие/отображение надписей на кнопках. (По факту происходит изменение размеров
   самих кнопок и их смещение.) */

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

// Нажатие кнопки меню "Письмо->Редактировать->Вырезать"

void __fastcall TMainForm::N11Click(TObject *Sender)
{
        Memo2->CutToClipboard();
}
//---------------------------------------------------------------------------

// Нажатие кнопки меню "Письмо->Редактировать->Копировать"

void __fastcall TMainForm::N12Click(TObject *Sender)
{
        Memo2->CopyToClipboard();
}
//---------------------------------------------------------------------------

// Нажатие кнопки меню "Письмо->Редактировать->Вставить"

void __fastcall TMainForm::N13Click(TObject *Sender)
{
        Memo2->PasteFromClipboard();
}
//---------------------------------------------------------------------------

