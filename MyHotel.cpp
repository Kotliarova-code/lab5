
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
// --------------------------------------------------

#include "MainForm2.h" // Подключение вашей главной формы

using namespace System;
using namespace System::Windows::Forms;
using namespace HotelManagementApp;

[STAThread]
void Main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Запуск Главного окна
    Application::Run(gcnew MainForm2());
}