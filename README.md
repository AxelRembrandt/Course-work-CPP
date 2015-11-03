# Курсовая работа на C++

Это программа для условного риэлтерского агентства с базой данных контактов, адресов помещений и презентаций в виде фотографий. Реализованы возможности добавления, редактирования, удаления контактов и адресов, отправки почты контактам с прикреплением к письму фотографий-презентаций и прочие мелочи.

Для работы приложения необходимо, чтобы в одной папке с ним находилась БД и файл с настройками. 
При переносе этих трех файлов в какую-либо папку, настройки обновлять вручную не требуется: 
приложение автоматически обновляет их при запуске. Если есть желание использовать другой email, 
тогда изменения надо вносить вручную.

Для удобства проект целиком лежит в папке Project files, а в папку exe скопированы приложение, файл настроек и БД.

Файлы проекта можно открыть в C++ Builder 6.
Сам проект - это  файл KR_2123.bpr

Файлы с исходным кодом - *.cpp. Main_form.cpp - главная форма, остальные - дополнительные. EAdd_form.cpp - добавление нового контакта, EEdit_form.cpp - редактирование информации о контакте. PAdd_form.cpp - добавление нового помещения(адреса, презентации, проч.), PEdit_form.cpp - редактирование информации о помещении. Кодировка в файлах - Windows-1251.

База данных - KR_2123_DB.accdb

Скомпилированное приложение - KR_2123.exe

В файле KR_2123.exe.ini настройки соединения с БД и с почтой.

В папке presents находятся изображения-"презентации".


