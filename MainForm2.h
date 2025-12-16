// MainForm2.h
#pragma once

#include "GuestManager2.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace HotelManagementApp;

namespace HotelManagementApp {

    public ref class MainForm2 : public System::Windows::Forms::Form
    {
    public:
        MainForm2(void);

    protected:
        ~MainForm2();

    private:
        // UI элементы
        DataGridView^ dataGridViewGuests;
        Label^ lblDatabaseStatus;
        Label^ lblRecordCount;

        Button^ btnAdd;
        Button^ btnEdit;
        Button^ btnDelete;
        Button^ btnSortFIO;
        Button^ btnSortCheckInDate;
        Button^ btnSaveLoad;
        Button^ btnDatabase;
        Button^ btnTestDB;

        System::ComponentModel::Container^ components;

    private:
        // Данные
        GuestManager2^ manager;

        // Методы
        void InitializeComponent(void);
        void UpdateGrid();
        void UpdateGrid(List<Guest2^>^ listToDisplay);
        void UpdateDatabaseStatus();

        // Обработчики событий
        System::Void btnAdd_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnEdit_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnDelete_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnSortFIO_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnSortCheckInDate_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnSaveLoad_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnDatabase_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnTestDB_Click(System::Object^ sender, System::EventArgs^ e);

        // Обработчики меню
        System::Void SaveToFile_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void LoadFromFile_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void SyncToDB_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void ReloadFromDB_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void ClearDB_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void CreateTestData_Click(System::Object^ sender, System::EventArgs^ e);
    };
}