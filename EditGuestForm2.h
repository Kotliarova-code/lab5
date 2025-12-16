#pragma once
#include "Guest2.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace HotelManagementApp {

    public ref class EditGuestForm2 : public Form
    {
    public:
        Guest2^ EditedGuest;

        // Конструкторы
        EditGuestForm2();                  // Для добавления нового гостя
        EditGuestForm2(Guest2^ guestToEdit); // Для редактирования существующего гостя

    private:
        // Элементы формы
        TextBox^ txtFirstName;
        TextBox^ txtLastName;
        TextBox^ txtAddress;
        NumericUpDown^ numericRoomNumber;
        DateTimePicker^ dateCheckIn;
        NumericUpDown^ numericNights;
        Button^ btnOK;
        Button^ btnCancel;

        // Методы
        void InitializeComponent(void);

        // Обработчики событий
        System::Void btnOK_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e);
    };
}
