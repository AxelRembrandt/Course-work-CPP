//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Main_form.cpp", MainForm);
USEFORM("EAdd_form.cpp", EAddForm);
USEFORM("EEdit_form.cpp", EEditForm);
USEFORM("PAdd_form.cpp", PAddForm);
USEFORM("PEdit_form.cpp", PEditForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TPAddForm), &PAddForm);
                 Application->CreateForm(__classid(TPEditForm), &PEditForm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
