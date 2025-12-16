// EditGuestForm2.cpp
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include "EditGuestForm2.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace HotelManagementApp {

    // --- Конструктор по умолчанию (для добавления нового гостя) ---
    EditGuestForm2::EditGuestForm2()
    {
        EditedGuest = gcnew Guest2();
        InitializeComponent();
    }

    // --- Перегруженный конструктор (для редактирования существующего гостя) ---
    EditGuestForm2::EditGuestForm2(Guest2^ guestToEdit)
    {
        EditedGuest = guestToEdit;
        InitializeComponent();

        // Заполняем поля формы текущими данными гостя
        txtFirstName->Text = EditedGuest->FirstName;
        txtLastName->Text = EditedGuest->LastName;
        txtAddress->Text = EditedGuest->Address;
        numericRoomNumber->Value = EditedGuest->RoomNumber;
        dateCheckIn->Value = EditedGuest->CheckInDate;
        numericNights->Value = EditedGuest->NightsStay;
    }

    // --- Обработчик кнопки OK ---
    System::Void EditGuestForm2::btnOK_Click(System::Object^ sender, System::EventArgs^ e)
    {
        // Сохраняем изменения в объекте EditedGuest
        EditedGuest->FirstName = txtFirstName->Text;
        EditedGuest->LastName = txtLastName->Text;
        EditedGuest->Address = txtAddress->Text;
        EditedGuest->RoomNumber = Decimal::ToInt32(numericRoomNumber->Value);
        EditedGuest->CheckInDate = dateCheckIn->Value;
        EditedGuest->NightsStay = Decimal::ToInt32(numericNights->Value);

        this->DialogResult = System::Windows::Forms::DialogResult::OK;
        this->Close();
    }

    // --- Обработчик кнопки Cancel ---
    System::Void EditGuestForm2::btnCancel_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
        this->Close();
    }

    // --- Инициализация компонентов формы ---
    void EditGuestForm2::InitializeComponent(void)
    {
        this->SuspendLayout();

        // --- Размер и заголовок формы ---
        this->Text = L"Редактирование гостя";
        this->Size = System::Drawing::Size(400, 350);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->MaximizeBox = false;
        this->MinimizeBox = false;
        this->StartPosition = FormStartPosition::CenterParent;

        // --- Поля формы ---
        txtFirstName = gcnew TextBox();
        txtFirstName->Location = Point(150, 20);
        txtFirstName->Size = Drawing::Size(200, 25);

        txtLastName = gcnew TextBox();
        txtLastName->Location = Point(150, 60);
        txtLastName->Size = Drawing::Size(200, 25);

        txtAddress = gcnew TextBox();
        txtAddress->Location = Point(150, 100);
        txtAddress->Size = Drawing::Size(200, 25);

        numericRoomNumber = gcnew NumericUpDown();
        numericRoomNumber->Location = Point(150, 140);
        numericRoomNumber->Maximum = 10000;

        dateCheckIn = gcnew DateTimePicker();
        dateCheckIn->Location = Point(150, 180);
        dateCheckIn->Format = DateTimePickerFormat::Short;

        numericNights = gcnew NumericUpDown();
        numericNights->Location = Point(150, 220);
        numericNights->Maximum = 365;

        // --- Метки ---
        Label^ lblFirstName = gcnew Label();
        lblFirstName->Text = L"Имя:";
        lblFirstName->Location = Point(20, 20);
        lblFirstName->Size = Drawing::Size(120, 25);

        Label^ lblLastName = gcnew Label();
        lblLastName->Text = L"Фамилия:";
        lblLastName->Location = Point(20, 60);
        lblLastName->Size = Drawing::Size(120, 25);

        Label^ lblAddress = gcnew Label();
        lblAddress->Text = L"Адрес:";
        lblAddress->Location = Point(20, 100);
        lblAddress->Size = Drawing::Size(120, 25);

        Label^ lblRoomNumber = gcnew Label();
        lblRoomNumber->Text = L"Номер комнаты:";
        lblRoomNumber->Location = Point(20, 140);
        lblRoomNumber->Size = Drawing::Size(120, 25);

        Label^ lblCheckIn = gcnew Label();
        lblCheckIn->Text = L"Дата заезда:";
        lblCheckIn->Location = Point(20, 180);
        lblCheckIn->Size = Drawing::Size(120, 25);

        Label^ lblNights = gcnew Label();
        lblNights->Text = L"Количество ночей:";
        lblNights->Location = Point(20, 220);
        lblNights->Size = Drawing::Size(120, 25);

        // --- Кнопки ---
        btnOK = gcnew Button();
        btnOK->Text = L"OK";
        btnOK->Location = Point(80, 270);
        btnOK->Click += gcnew EventHandler(this, &EditGuestForm2::btnOK_Click);

        btnCancel = gcnew Button();
        btnCancel->Text = L"Отмена";
        btnCancel->Location = Point(200, 270);
        btnCancel->Click += gcnew EventHandler(this, &EditGuestForm2::btnCancel_Click);

        // --- Добавляем на форму ---
        this->Controls->Add(lblFirstName);
        this->Controls->Add(txtFirstName);
        this->Controls->Add(lblLastName);
        this->Controls->Add(txtLastName);
        this->Controls->Add(lblAddress);
        this->Controls->Add(txtAddress);
        this->Controls->Add(lblRoomNumber);
        this->Controls->Add(numericRoomNumber);
        this->Controls->Add(lblCheckIn);
        this->Controls->Add(dateCheckIn);
        this->Controls->Add(lblNights);
        this->Controls->Add(numericNights);
        this->Controls->Add(btnOK);
        this->Controls->Add(btnCancel);

        this->ResumeLayout(false);
    }
}
