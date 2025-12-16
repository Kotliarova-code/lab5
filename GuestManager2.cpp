// GuestManager2.cpp
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include "GuestManager2.h"
#include <msclr/marshal_cppstd.h>

using namespace System::Runtime::Serialization::Formatters;
using namespace System::Runtime::Serialization::Formatters::Binary;
using namespace System::IO;

namespace HotelManagementApp {

    // ============================================
    // КОНСТРУКТОР
    // ============================================

    GuestManager2::GuestManager2()
    {
        guests = gcnew List<Guest2^>();
        dbManager = gcnew DatabaseManager();

        useDatabase = dbManager->IsConnected;

        if (useDatabase)
        {
            // Загружаем данные из БД
            LoadFromDatabase();
            Console::WriteLine("GuestManager2: Работа с базой данных.");
        }
        else
        {
            // Работаем в локальном режиме
            Console::WriteLine("GuestManager2: Работа в локальном режиме.");

            // Если локальный список пуст, создаем тестовые данные
            if (guests->Count == 0)
            {
                CreateTestData();
            }
        }
    }

    // ============================================
    // ОСНОВНЫЕ ОПЕРАЦИИ
    // ============================================

    bool GuestManager2::AddGuest(Guest2^ newGuest)
    {
        if (newGuest == nullptr)
            return false;

        if (useDatabase && DatabaseConnected)
        {
            // Добавляем в БД
            if (dbManager->InsertGuest(newGuest))
            {
                guests->Add(newGuest);
                return true;
            }
            return false;
        }
        else
        {
            // Локальный режим
            guests->Add(newGuest);
            return true;
        }
    }

    bool GuestManager2::RemoveGuest(Guest2^ guestToRemove)
    {
        if (guestToRemove == nullptr)
            return false;

        return RemoveGuestById(guestToRemove->Id);
    }

    bool GuestManager2::RemoveGuestById(int guestId)
    {
        if (guestId <= 0)
            return false;

        if (useDatabase && DatabaseConnected)
        {
            // Удаляем из БД
            if (dbManager->DeleteGuest(guestId))
            {
                // Удаляем из локального списка
                for (int i = 0; i < guests->Count; i++)
                {
                    if (guests[i]->Id == guestId)
                    {
                        guests->RemoveAt(i);
                        return true;
                    }
                }
            }
            return false;
        }
        else
        {
            // Локальный режим
            for (int i = 0; i < guests->Count; i++)
            {
                if (guests[i]->Id == guestId)
                {
                    guests->RemoveAt(i);
                    return true;
                }
            }
            return false;
        }
    }

    bool GuestManager2::UpdateGuest(Guest2^ guestToUpdate)
    {
        if (guestToUpdate == nullptr || guestToUpdate->Id <= 0)
            return false;

        if (useDatabase && DatabaseConnected)
        {
            return dbManager->UpdateGuest(guestToUpdate);
        }

        // В локальном режиме объект уже обновлен в памяти
        return true;
    }

    // ============================================
    // ПОИСК
    // ============================================

    Guest2^ GuestManager2::FindGuestById(int id)
    {
        if (useDatabase && DatabaseConnected)
        {
            return dbManager->GetGuestById(id);
        }
        else
        {
            // Поиск в локальном списке
            for each (Guest2 ^ guest in guests)
            {
                if (guest->Id == id)
                    return guest;
            }
            return nullptr;
        }
    }

    List<Guest2^>^ GuestManager2::FindGuestsByName(String^ name)
    {
        List<Guest2^>^ result = gcnew List<Guest2^>();

        if (String::IsNullOrEmpty(name))
            return result;

        String^ searchName = name->ToLower();

        for each (Guest2 ^ guest in guests)
        {
            if (guest->LastName->ToLower()->Contains(searchName) ||
                guest->FirstName->ToLower()->Contains(searchName) ||
                guest->FullName->ToLower()->Contains(searchName))
            {
                result->Add(guest);
            }
        }

        return result;
    }

    // ============================================
    // РАБОТА С ФАЙЛАМИ
    // ============================================

    bool GuestManager2::SaveToFile(String^ filePath)
    {
        try
        {
            BinaryFormatter^ formatter = gcnew BinaryFormatter();
            FileStream^ stream = gcnew FileStream(filePath, FileMode::Create, FileAccess::Write);
            formatter->Serialize(stream, guests);
            stream->Close();

            Console::WriteLine("Данные сохранены в файл: " + filePath);
            return true;
        }
        catch (Exception^ ex)
        {
            Console::WriteLine("Ошибка сохранения в файл: " + ex->Message);
            return false;
        }
    }

    bool GuestManager2::LoadFromFile(String^ filePath)
    {
        if (!File::Exists(filePath))
            return false;

        try
        {
            BinaryFormatter^ formatter = gcnew BinaryFormatter();
            FileStream^ stream = gcnew FileStream(filePath, FileMode::Open, FileAccess::Read);
            guests = (List<Guest2^>^)formatter->Deserialize(stream);
            stream->Close();

            Console::WriteLine("Данные загружены из файла: " + filePath);

            // Если используется БД, синхронизируем
            if (useDatabase && DatabaseConnected)
            {
                SyncToDatabase();
            }

            return true;
        }
        catch (Exception^ ex)
        {
            Console::WriteLine("Ошибка загрузки из файла: " + ex->Message);
            return false;
        }
    }

    // ============================================
    // РАБОТА С БАЗОЙ ДАННЫХ
    // ============================================

    void GuestManager2::SyncToDatabase()
    {
        if (useDatabase && DatabaseConnected)
        {
            dbManager->SyncToDatabase(guests);
        }
    }

    void GuestManager2::LoadFromDatabase()
    {
        if (useDatabase && DatabaseConnected)
        {
            guests = dbManager->SyncFromDatabase();
            Console::WriteLine(String::Format("Загружено {0} записей из БД", guests->Count));
        }
    }

    bool GuestManager2::ImportFromFileToDatabase(String^ filePath)
    {
        if (!useDatabase || !DatabaseConnected)
            return false;

        return dbManager->ImportFromFile(filePath);
    }

    bool GuestManager2::ExportFromDatabaseToFile(String^ filePath)
    {
        if (!useDatabase || !DatabaseConnected)
            return false;

        return dbManager->ExportToFile(filePath);
    }

    // ============================================
    // ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ
    // ============================================

    void GuestManager2::SortByName()
    {
        guests->Sort(gcnew Comparison<Guest2^>(Guest2::CompareByFullName));
    }

    void GuestManager2::SortByCheckInDate()
    {
        guests->Sort(gcnew Comparison<Guest2^>(Guest2::CompareByCheckInDate));
    }

    int GuestManager2::GetCount()
    {
        return guests->Count;
    }

    void GuestManager2::ClearAll()
    {
        guests->Clear();

        if (useDatabase && DatabaseConnected)
        {
            dbManager->ClearDatabase();
        }
    }

    // ============================================
    // ТЕСТОВЫЕ МЕТОДЫ
    // ============================================

    void GuestManager2::CreateTestData()
    {
        if (useDatabase && DatabaseConnected)
        {
            dbManager->CreateTestData();
            LoadFromDatabase();
        }
        else
        {
            // Локальные тестовые данные
            guests->Add(gcnew Guest2("Елена", "Котова", "г. Санкт-Петербург, ул. Мира, 1", 505, DateTime(2025, 12, 19), 3));
            guests->Add(gcnew Guest2("Иван", "Петров", "г. Москва, пр. Ленина, 12", 205, DateTime(2025, 12, 22), 5));
            guests->Add(gcnew Guest2("Анна", "Смирнова", "г. Тверь, ул. Тверская, 7", 101, DateTime(2025, 12, 15), 10));

            // Назначаем ID для локального режима
            for (int i = 0; i < guests->Count; i++)
            {
                guests[i]->Id = i + 1;
            }

            Console::WriteLine("Создано тестовых данных: " + guests->Count + " записей");
        }
    }

    String^ GuestManager2::GetDatabaseInfo()
    {
        if (useDatabase && DatabaseConnected)
        {
            return dbManager->TestConnectionDetailed();
        }
        else
        {
            return "Режим работы: ЛОКАЛЬНЫЙ\n" +
                String::Format("Записей в памяти: {0}", guests->Count);
        }
    }

} // namespace HotelManagementApp