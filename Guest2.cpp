// Guest2.cpp
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include "Guest2.h"

using namespace System;

namespace HotelManagementApp {

    // --- ÊÎÍÑÒĞÓÊÒÎĞÛ ---
    Guest2::Guest2() :
        id(0),
        firstName(""),
        lastName(""),
        address(""),
        roomNumber(0),
        nightsStay(0)
    {
        checkInDate = DateTime::Now;
    }

    Guest2::Guest2(String^ fn, String^ ln, String^ addr, int rn, DateTime ci, int ns) :
        id(0),
        firstName(fn),
        lastName(ln),
        address(addr),
        roomNumber(rn),
        checkInDate(ci),
        nightsStay(ns)
    {
        // empty
    }

    Guest2::Guest2(int id, String^ fn, String^ ln, String^ addr, int rn, DateTime ci, int ns) :
        id(id),
        firstName(fn),
        lastName(ln),
        address(addr),
        roomNumber(rn),
        checkInDate(ci),
        nightsStay(ns)
    {
        // empty
    }

    // --- ÑÒÀÒÈ×ÅÑÊÈÅ ÌÅÒÎÄÛ ÊÎÌÏÀĞÀÒÎĞÎÂ ---
    int Guest2::CompareByFullName(Guest2^ g1, Guest2^ g2)
    {
        int result = g1->LastName->CompareTo(g2->LastName);
        if (result == 0)
        {
            result = g1->FirstName->CompareTo(g2->FirstName);
        }
        return result;
    }

    int Guest2::CompareByCheckInDate(Guest2^ g1, Guest2^ g2)
    {
        return g1->CheckInDate.CompareTo(g2->CheckInDate);
    }

    // --- ÌÅÒÎÄ ToString ---
    String^ Guest2::ToString()
    {
        return String::Format("[ID:{0}] {1}, Êîìíàòà:{2}, Çàåçä:{3:d}, Âûåçä:{4:d}",
            id, FullName, roomNumber, checkInDate, CheckOutDate);
    }
}