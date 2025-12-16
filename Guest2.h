// Guest2.h
#pragma once

using namespace System;
using namespace System::Collections::Generic;

namespace HotelManagementApp {

    [Serializable]
        public ref class Guest2
    {
    private:
        int id; // ÄÎÁÀÂËÅÍÎ: ID äëÿ áàçû äàííûõ
        String^ firstName;
        String^ lastName;
        String^ address;
        int roomNumber;
        DateTime checkInDate;
        int nightsStay;

    public:
        // --- ÊÎÍÑÒĞÓÊÒÎĞÛ ---
        Guest2();
        Guest2(int id, String^ firstName, String^ lastName, String^ address,
            int roomNumber, DateTime checkInDate, int nightsStay);
        Guest2(String^ firstName, String^ lastName, String^ address,
            int roomNumber, DateTime checkInDate, int nightsStay);

        // --- ÑÂÎÉÑÒÂÀ ---
        property int Id {
            int get() { return id; }
            void set(int value) { id = value; }
        }
        property String^ FirstName {
            String^ get() { return firstName; }
            void set(String^ value) { firstName = value; }
        }
        property String^ LastName {
            String^ get() { return lastName; }
            void set(String^ value) { lastName = value; }
        }
        property String^ FullName {
            String^ get() { return String::Format("{0} {1}", lastName, firstName); }
        }
        property String^ Address {
            String^ get() { return address; }
            void set(String^ value) { address = value; }
        }
        property int RoomNumber {
            int get() { return roomNumber; }
            void set(int value) { roomNumber = value; }
        }
        property DateTime CheckInDate {
            DateTime get() { return checkInDate; }
            void set(DateTime value) { checkInDate = value; }
        }
        property int NightsStay {
            int get() { return nightsStay; }
            void set(int value) { nightsStay = value; }
        }
        property DateTime CheckOutDate {
            DateTime get() { return checkInDate.AddDays(nightsStay); }
        }

        // --- ÑÒÀÒÈ×ÅÑÊÈÅ ÌÅÒÎÄÛ ÊÎÌÏÀĞÀÒÎĞÎÂ ---
        static int CompareByFullName(Guest2^ g1, Guest2^ g2);
        static int CompareByCheckInDate(Guest2^ g1, Guest2^ g2);

        // --- ÌÅÒÎÄ ToString ---
        virtual String^ ToString() override;
    };
}