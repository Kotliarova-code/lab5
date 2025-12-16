// GuestManager2.h
#pragma once

#include "Guest2.h"
#include "DatabaseManager.h"
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::ComponentModel;

namespace HotelManagementApp {

    public ref class GuestManager2
    {
    private:
        List<Guest2^>^ guests;
        DatabaseManager^ dbManager;
        bool useDatabase;

    public:
        GuestManager2();

        property List<Guest2^>^ GuestsList
        {
            List<Guest2^>^ get() { return guests; }
        }

        property DatabaseManager^ Database
        {
            DatabaseManager^ get() { return dbManager; }
        }

        property bool UseDatabase
        {
            bool get() { return useDatabase; }
            void set(bool value)
            {
                useDatabase = value;
                if (useDatabase && dbManager->IsConnected)
                {
                    SyncToDatabase();
                }
            }
        }

        property bool DatabaseConnected
        {
            bool get() { return dbManager != nullptr && dbManager->IsConnected; }
        }

        property String^ DatabaseStatus
        {
            String^ get()
            {
                if (dbManager != nullptr)
                    return dbManager->ConnectionStatus;
                return "Менеджер БД не инициализирован";
            }
        }

        // Основные операции
        bool AddGuest(Guest2^ newGuest);
        bool RemoveGuest(Guest2^ guestToRemove);
        bool RemoveGuestById(int guestId);
        bool UpdateGuest(Guest2^ guestToUpdate);

        // Поиск
        Guest2^ FindGuestById(int id);
        List<Guest2^>^ FindGuestsByName(String^ name);

        // Работа с файлами
        bool SaveToFile(String^ filePath);
        bool LoadFromFile(String^ filePath);

        // Работа с БД
        void SyncToDatabase();
        void LoadFromDatabase();
        bool ImportFromFileToDatabase(String^ filePath);
        bool ExportFromDatabaseToFile(String^ filePath);

        // Вспомогательные методы
        void SortByName();
        void SortByCheckInDate();
        int GetCount();
        void ClearAll();

        // Тестовые методы
        void CreateTestData();
        String^ GetDatabaseInfo();
    };
}