// MainForm2.cpp
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include "MainForm2.h"
#include "Guest2.h"
#include "GuestManager2.h"
#include "EditGuestForm2.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Collections::Generic;
using namespace HotelManagementApp;

namespace HotelManagementApp {

    // ============================================
    // КОНСТРУКТОР И ДЕСТРУКТОР
    // ============================================

    MainForm2::MainForm2(void)
    {
        InitializeComponent();
        this->Text = "Управление гостями отеля - SQL Server LocalDB";

        manager = gcnew GuestManager2();

        UpdateGrid();
        UpdateDatabaseStatus();
    }

    MainForm2::~MainForm2()
    {
        if (components != nullptr)
        {
            delete components;
        }
    }

    // ============================================
    // ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ
    // ============================================

    void MainForm2::UpdateGrid()
    {
        UpdateGrid(manager->GuestsList);
    }

    void MainForm2::UpdateGrid(List<Guest2^>^ listToDisplay)
    {
        this->dataGridViewGuests->DataSource = nullptr;

        System::ComponentModel::BindingList<Guest2^>^ bindingList =
            gcnew System::ComponentModel::BindingList<Guest2^>(listToDisplay);

        this->dataGridViewGuests->AutoGenerateColumns = true;
        this->dataGridViewGuests->DataSource = bindingList;
        this->dataGridViewGuests->Refresh();

        // Обновляем счетчик записей
        lblRecordCount->Text = String::Format("Записей: {0}", listToDisplay->Count);
    }

    void MainForm2::UpdateDatabaseStatus()
    {
        if (manager->DatabaseConnected)
        {
            lblDatabaseStatus->Text = "? База данных: ПОДКЛЮЧЕНА";
            lblDatabaseStatus->ForeColor = Color::Green;
        }
        else
        {
            lblDatabaseStatus->Text = "? База данных: ОТКЛЮЧЕНА (локальный режим)";
            lblDatabaseStatus->ForeColor = Color::Red;
        }
    }

    // ============================================
    // ОБРАБОТЧИКИ МЕНЮ
    // ============================================

    System::Void MainForm2::SaveToFile_Click(System::Object^ sender, System::EventArgs^ e)
    {
        SaveFileDialog^ saveDialog = gcnew SaveFileDialog();
        saveDialog->Filter = "Файлы данных (*.dat)|*.dat|Все файлы (*.*)|*.*";
        saveDialog->Title = "Сохранить список гостей";
        saveDialog->FileName = "guests.dat";

        if (saveDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
        {
            if (manager->SaveToFile(saveDialog->FileName))
            {
                MessageBox::Show("Данные успешно сохранены.", "Успех",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            else
            {
                MessageBox::Show("Ошибка при сохранении.", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
    }

    System::Void MainForm2::LoadFromFile_Click(System::Object^ sender, System::EventArgs^ e)
    {
        OpenFileDialog^ openDialog = gcnew OpenFileDialog();
        openDialog->Filter = "Файлы данных (*.dat)|*.dat|Все файлы (*.*)|*.*";
        openDialog->Title = "Загрузить список гостей";

        if (openDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
        {
            if (manager->LoadFromFile(openDialog->FileName))
            {
                UpdateGrid();
                UpdateDatabaseStatus();
                MessageBox::Show("Данные успешно загружены.", "Успех",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            else
            {
                MessageBox::Show("Ошибка при загрузке.", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
    }

    System::Void MainForm2::SyncToDB_Click(System::Object^ sender, System::EventArgs^ e)
    {
        manager->SyncToDatabase();
        MessageBox::Show("Данные синхронизированы с базой данных.", "Синхронизация",
            MessageBoxButtons::OK, MessageBoxIcon::Information);
    }

    System::Void MainForm2::ReloadFromDB_Click(System::Object^ sender, System::EventArgs^ e)
    {
        manager->LoadFromDatabase();
        UpdateGrid();
        UpdateDatabaseStatus();
        MessageBox::Show("Данные загружены из базы данных.", "Загрузка",
            MessageBoxButtons::OK, MessageBoxIcon::Information);
    }

    System::Void MainForm2::ClearDB_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (MessageBox::Show("Очистить всю базу данных? Это действие нельзя отменить.",
            "Подтверждение", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) == System::Windows::Forms::DialogResult::Yes)
        {
            manager->ClearAll();
            UpdateGrid();
            UpdateDatabaseStatus();
            MessageBox::Show("База данных очищена.", "Очистка",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
    }

    System::Void MainForm2::CreateTestData_Click(System::Object^ sender, System::EventArgs^ e)
    {
        manager->CreateTestData();
        UpdateGrid();
        UpdateDatabaseStatus();
        MessageBox::Show("Тестовые данные созданы.", "Тест",
            MessageBoxButtons::OK, MessageBoxIcon::Information);
    }

    // ============================================
    // ИНИЦИАЛИЗАЦИЯ КОМПОНЕНТОВ
    // ============================================

    void MainForm2::InitializeComponent(void)
    {
        this->dataGridViewGuests = gcnew DataGridView();
        this->lblDatabaseStatus = gcnew Label();
        this->lblRecordCount = gcnew Label();

        this->btnAdd = gcnew Button();
        this->btnEdit = gcnew Button();
        this->btnDelete = gcnew Button();
        this->btnSortFIO = gcnew Button();
        this->btnSortCheckInDate = gcnew Button();
        this->btnSaveLoad = gcnew Button();
        this->btnDatabase = gcnew Button();
        this->btnTestDB = gcnew Button();

        this->components = gcnew System::ComponentModel::Container();

        // --- Настройка формы ---
        this->Text = L"Управление гостями отеля";
        this->Size = Drawing::Size(900, 600);
        this->StartPosition = FormStartPosition::CenterScreen;
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->MaximizeBox = false;

        // --- Статус базы данных ---
        this->lblDatabaseStatus->Location = Point(10, 10);
        this->lblDatabaseStatus->Size = Drawing::Size(400, 25);
        this->lblDatabaseStatus->Font = gcnew Drawing::Font("Arial", 10, FontStyle::Bold);

        // --- Счетчик записей ---
        this->lblRecordCount->Location = Point(420, 10);
        this->lblRecordCount->Size = Drawing::Size(200, 25);
        this->lblRecordCount->Font = gcnew Drawing::Font("Arial", 10, FontStyle::Regular);
        this->lblRecordCount->Text = "Записей: 0";

        // --- DataGridView ---
        this->dataGridViewGuests->Location = Point(10, 40);
        this->dataGridViewGuests->Size = Drawing::Size(650, 500);
        this->dataGridViewGuests->Anchor = AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Bottom;
        this->dataGridViewGuests->ReadOnly = true;
        this->dataGridViewGuests->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
        this->dataGridViewGuests->DoubleClick += gcnew EventHandler(this, &MainForm2::btnEdit_Click);

        // --- Настройка кнопок ---
        int buttonWidth = 200;
        int buttonHeight = 35;
        int startX = 670;
        int spacing = 10;
        int currentY = 40;

        // Кнопка "Добавить"
        this->btnAdd->Text = "1. Добавить гостя";
        this->btnAdd->Location = Point(startX, currentY);
        this->btnAdd->Size = Drawing::Size(buttonWidth, buttonHeight);
        this->btnAdd->Click += gcnew EventHandler(this, &MainForm2::btnAdd_Click);
        currentY += buttonHeight + spacing;

        // Кнопка "Редактировать"
        this->btnEdit->Text = "2. Редактировать";
        this->btnEdit->Location = Point(startX, currentY);
        this->btnEdit->Size = Drawing::Size(buttonWidth, buttonHeight);
        this->btnEdit->Click += gcnew EventHandler(this, &MainForm2::btnEdit_Click);
        currentY += buttonHeight + spacing;

        // Кнопка "Удалить"
        this->btnDelete->Text = "3. Удалить";
        this->btnDelete->Location = Point(startX, currentY);
        this->btnDelete->Size = Drawing::Size(buttonWidth, buttonHeight);
        this->btnDelete->Click += gcnew EventHandler(this, &MainForm2::btnDelete_Click);
        currentY += buttonHeight + spacing * 2;

        // Кнопка "Сортировать по ФИО"
        this->btnSortFIO->Text = "4. Сортировать по ФИО";
        this->btnSortFIO->Location = Point(startX, currentY);
        this->btnSortFIO->Size = Drawing::Size(buttonWidth, buttonHeight);
        this->btnSortFIO->Click += gcnew EventHandler(this, &MainForm2::btnSortFIO_Click);
        currentY += buttonHeight + spacing;

        // Кнопка "Сортировать по дате"
        this->btnSortCheckInDate->Text = "5. Сортировать по дате заезда";
        this->btnSortCheckInDate->Location = Point(startX, currentY);
        this->btnSortCheckInDate->Size = Drawing::Size(buttonWidth, buttonHeight);
        this->btnSortCheckInDate->Click += gcnew EventHandler(this, &MainForm2::btnSortCheckInDate_Click);
        currentY += buttonHeight + spacing * 2;

        // Кнопка "Сохранить/Загрузить"
        this->btnSaveLoad->Text = "6. Сохранить/Загрузить файл";
        this->btnSaveLoad->Location = Point(startX, currentY);
        this->btnSaveLoad->Size = Drawing::Size(buttonWidth, buttonHeight);
        this->btnSaveLoad->Click += gcnew EventHandler(this, &MainForm2::btnSaveLoad_Click);
        currentY += buttonHeight + spacing;

        // Кнопка "Управление БД"
        this->btnDatabase->Text = "7. Управление базой данных";
        this->btnDatabase->Location = Point(startX, currentY);
        this->btnDatabase->Size = Drawing::Size(buttonWidth, buttonHeight);
        this->btnDatabase->Click += gcnew EventHandler(this, &MainForm2::btnDatabase_Click);
        currentY += buttonHeight + spacing;

        // Кнопка "Тест БД"
        this->btnTestDB->Text = "8. Тестирование БД";
        this->btnTestDB->Location = Point(startX, currentY);
        this->btnTestDB->Size = Drawing::Size(buttonWidth, buttonHeight);
        this->btnTestDB->Click += gcnew EventHandler(this, &MainForm2::btnTestDB_Click);

        // --- Добавление элементов на форму ---
        this->Controls->Add(this->lblDatabaseStatus);
        this->Controls->Add(this->lblRecordCount);
        this->Controls->Add(this->dataGridViewGuests);
        this->Controls->Add(this->btnAdd);
        this->Controls->Add(this->btnEdit);
        this->Controls->Add(this->btnDelete);
        this->Controls->Add(this->btnSortFIO);
        this->Controls->Add(this->btnSortCheckInDate);
        this->Controls->Add(this->btnSaveLoad);
        this->Controls->Add(this->btnDatabase);
        this->Controls->Add(this->btnTestDB);

        this->ResumeLayout(false);
    }

    // ============================================
    // ОБРАБОТЧИКИ СОБЫТИЙ - ОПЕРАЦИИ
    // ============================================

    System::Void MainForm2::btnAdd_Click(System::Object^ sender, System::EventArgs^ e)
    {
        EditGuestForm2^ addForm = gcnew EditGuestForm2();
        if (addForm->ShowDialog() == System::Windows::Forms::DialogResult::OK)
        {
            Guest2^ newGuest = addForm->EditedGuest;
            if (newGuest != nullptr)
            {
                if (manager->AddGuest(newGuest))
                {
                    UpdateGrid();
                    UpdateDatabaseStatus();
                    MessageBox::Show("Гость успешно добавлен.", "Успех",
                        MessageBoxButtons::OK, MessageBoxIcon::Information);
                }
                else
                {
                    MessageBox::Show("Ошибка при добавлении гостя.", "Ошибка",
                        MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
        }
    }

    System::Void MainForm2::btnEdit_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (this->dataGridViewGuests->SelectedRows->Count == 0)
        {
            MessageBox::Show("Выберите гостя для редактирования.", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        Guest2^ selectedGuest = (Guest2^)this->dataGridViewGuests->SelectedRows[0]->DataBoundItem;
        EditGuestForm2^ editForm = gcnew EditGuestForm2(selectedGuest);

        if (editForm->ShowDialog() == System::Windows::Forms::DialogResult::OK)
        {
            if (manager->UpdateGuest(selectedGuest))
            {
                UpdateGrid();
                MessageBox::Show("Данные гостя успешно обновлены.", "Успех",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            else
            {
                MessageBox::Show("Ошибка при обновлении данных.", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
    }

    System::Void MainForm2::btnDelete_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (this->dataGridViewGuests->SelectedRows->Count == 0)
        {
            MessageBox::Show("Выберите гостя для удаления.", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        if (MessageBox::Show(
            "Вы уверены, что хотите удалить выбранного гостя?",
            "Подтверждение",
            MessageBoxButtons::YesNo,
            MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
        {
            Guest2^ selectedGuest = (Guest2^)this->dataGridViewGuests->SelectedRows[0]->DataBoundItem;

            if (manager->RemoveGuest(selectedGuest))
            {
                UpdateGrid();
                UpdateDatabaseStatus();
                MessageBox::Show("Гость успешно удален.", "Успех",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            else
            {
                MessageBox::Show("Ошибка при удалении гостя.", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
    }

    // ============================================
    // ОБРАБОТЧИКИ СОБЫТИЙ - СОРТИРОВКА
    // ============================================

    System::Void MainForm2::btnSortFIO_Click(System::Object^ sender, System::EventArgs^ e)
    {
        manager->SortByName();
        UpdateGrid();
        MessageBox::Show("Список отсортирован по ФИО.", "Сортировка",
            MessageBoxButtons::OK, MessageBoxIcon::Information);
    }

    System::Void MainForm2::btnSortCheckInDate_Click(System::Object^ sender, System::EventArgs^ e)
    {
        manager->SortByCheckInDate();
        UpdateGrid();
        MessageBox::Show("Список отсортирован по дате заезда.", "Сортировка",
            MessageBoxButtons::OK, MessageBoxIcon::Information);
    }

    // ============================================
    // ОБРАБОТЧИКИ СОБЫТИЙ - ФАЙЛЫ И БД
    // ============================================

    System::Void MainForm2::btnSaveLoad_Click(System::Object^ sender, System::EventArgs^ e)
    {
        // Меню выбора действия
        System::Windows::Forms::ContextMenuStrip^ menu = gcnew System::Windows::Forms::ContextMenuStrip();

        ToolStripMenuItem^ saveItem = gcnew ToolStripMenuItem("Сохранить в файл");
        saveItem->Click += gcnew EventHandler(this, &MainForm2::SaveToFile_Click);

        ToolStripMenuItem^ loadItem = gcnew ToolStripMenuItem("Загрузить из файла");
        loadItem->Click += gcnew EventHandler(this, &MainForm2::LoadFromFile_Click);

        menu->Items->Add(saveItem);
        menu->Items->Add(loadItem);

        // Показываем меню рядом с кнопкой
        menu->Show(btnSaveLoad, Point(0, btnSaveLoad->Height));
    }

    System::Void MainForm2::btnDatabase_Click(System::Object^ sender, System::EventArgs^ e)
    {
        // Меню управления БД
        System::Windows::Forms::ContextMenuStrip^ dbMenu = gcnew System::Windows::Forms::ContextMenuStrip();

        ToolStripMenuItem^ syncItem = gcnew ToolStripMenuItem("Синхронизировать с БД");
        syncItem->Click += gcnew EventHandler(this, &MainForm2::SyncToDB_Click);

        ToolStripMenuItem^ reloadItem = gcnew ToolStripMenuItem("Перезагрузить из БД");
        reloadItem->Click += gcnew EventHandler(this, &MainForm2::ReloadFromDB_Click);

        ToolStripMenuItem^ clearItem = gcnew ToolStripMenuItem("Очистить базу данных");
        clearItem->Click += gcnew EventHandler(this, &MainForm2::ClearDB_Click);

        ToolStripMenuItem^ testDataItem = gcnew ToolStripMenuItem("Создать тестовые данные");
        testDataItem->Click += gcnew EventHandler(this, &MainForm2::CreateTestData_Click);

        dbMenu->Items->Add(syncItem);
        dbMenu->Items->Add(reloadItem);
        dbMenu->Items->Add(gcnew ToolStripSeparator());
        dbMenu->Items->Add(clearItem);
        dbMenu->Items->Add(testDataItem);

        // Показываем меню рядом с кнопкой
        dbMenu->Show(btnDatabase, Point(0, btnDatabase->Height));
    }

    System::Void MainForm2::btnTestDB_Click(System::Object^ sender, System::EventArgs^ e)
    {
        String^ info = manager->GetDatabaseInfo();
        MessageBox::Show(info, "Информация о базе данных",
            MessageBoxButtons::OK, MessageBoxIcon::Information);
    }

} // namespace HotelManagementApp