#include <iostream>
#include "booking.h"
using namespace std;

Booking::Booking(Date from, Date to, int numberOfGuests, int roomId, string note)
{
    setFrom(from);
    setTo(to);
    setNumberOfGuests(numberOfGuests);
    setRoomId(roomId);
    setNote(note);
}

Booking::Booking() :Booking(Date(), Date(), 1, 0, "")
{
}

Date Booking::getFrom()
{
    return from;
}

void Booking::setFrom(Date from)
{
    this->from = from;
}

Date Booking::getTo()
{
    return to;
}

void Booking::setTo(Date to)
{
    this->to = to;
}

int Booking::getNumberOfGuests()
{
    return numberOfGuests;
}

void Booking::setNumberOfGuests(int numberOfGUests)
{
    this->numberOfGuests = numberOfGUests;
}

int Booking::getRoomId()
{
    return roomId;
}

void Booking::setRoomId(int roomId)
{
    this->roomId = roomId;
}

string Booking::getNote()
{
    return note;
}

void Booking::setNote(string note)
{
    this->note = note;
}

void Booking::getInfo()
{
    cout << "Date from :" << from.getInfo() << endl << "Date to info: " << to.getInfo() << endl << "Number of guests: "
        << numberOfGuests << endl << "Room id: " << roomId << endl << "Note: " << note << endl;
}

bool Booking::inPeriod(Date targetDate)
{
    return targetDate.compareDates(to) <= 0 && targetDate.compareDates(from) >= 0;
}

int Booking::getActiveDaysInPeriod(Date from, Date to) {
    int result = 0;
    if (!((from.compareDates(getFrom()) == 1 && from.compareDates(getTo()) == 1) || (to.compareDates(getFrom()) == -1 && to.compareDates(getTo()) == -1))) {

        int totalPeriod = to.getTotalDays() - from.getTotalDays(); //XY
        int a = to.getTotalDays() - getTo().getTotalDays(); //yY
        int b = getFrom().getTotalDays() - from.getTotalDays();//Xx

        if (a < 0) a = 0;
        if (b < 0) b = 0;
        result += ((totalPeriod - a) - b) + 1;
    }
    return result;
}

string Booking::getConfig() {

    return "Booking," + from.getInfo() + "," + to.getInfo() + "," + to_string(numberOfGuests) + "," + to_string(roomId) + "," + note + "\n";
}
