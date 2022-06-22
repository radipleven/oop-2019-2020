#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "room.h"
#include "booking.h"
#include "hotel.h"
#include "function.h"
using namespace std;

Hotel::Hotel()
{
}

vector<Room*> Hotel::getRooms()
{
    return rooms;
}

vector<Booking*> Hotel::getBookings()
{
    return bookings;
}

void Hotel::addRoom(Room* room)
{
    rooms.push_back(room);
}

void Hotel::addBooking(Booking* booking)
{
    bookings.push_back(booking);
}

void Hotel::emptyHotel()
{
    rooms.clear();
    bookings.clear();
}

Room* Hotel::getRoomById(int id)
{
    for (int i = 0; i < rooms.size(); i++)
        if ((rooms[i])->getId() == id) return rooms[i];

    Room* temp = new Room();
    return temp;
}

bool Hotel::doesRoomExist(int id)
{
    for (int i = 0; i < rooms.size(); i++) if (rooms[i]->getId() == id) return true;
    return false;
}

void Hotel::checkIn(string input)
{
    vector<string> words = Function().splitBySpace(input);

    bool isUnavailable = words[0] == "unavailable";

    int roomId = Function().strToInt(words[1]);
    if (doesRoomExist(roomId))
    {
        Room* room = getRoomById(roomId);

        Date from = Date(words[2]);
        Date to = Date(words[3]);
        if (from.isValid() && to.isValid())
        {
            if (isRoomAvailableInPeriod(roomId, from, to)) {
                if (from.compareDates(to) != 1)
                {
                    string note;
                    int numberOfGuests = room->getNumberOfBeds();
                    for (size_t i = 4; i < words.size() - 1; i++) note += words[i] + " ";

                    if (Function().isNumber(words[words.size() - 1])) numberOfGuests = Function().strToInt(words[words.size() - 1]);
                    else note += words[words.size() - 1] + " ";

                    if (isUnavailable) numberOfGuests = 0;

                    if (numberOfGuests <= room->getNumberOfBeds())
                    {
                        Booking* booking = new Booking(from, to, numberOfGuests, roomId, note);
                        addBooking(booking);
                        if (booking->inPeriod(Date())) room->setAvailability(false);
                        cout << "Room " << roomId << " is booked in the period between " << from.getInfo() << " and " << to.getInfo() << "." << endl;

                    }
                    else cout << "You can't fit so many people in this room" << endl;
                }
                else cout << "You can't book a room in the future and use it in the past." << endl;
            }
            else cout << "Room is unavailable" << endl;
        }
        else cout << "Invalid Date format." << endl;
    }
    else cout << "Invalid room number" << endl;
}

void Hotel::checkOut(string input)
{
    vector<string> words = Function().splitBySpace(input);

    int roomId = Function().strToInt(words[1]);
    if (doesRoomExist(roomId))
    {
        Room* room = getRoomById(roomId);
        if (!(room->isAvailable()))
        {
            room->setAvailability(true);
            getBookingByRoomId(roomId)->setTo(Date());
            cout << "Checked out room " << roomId << endl;

        }
        else cout << "Room is already checked out" << endl;
    }
    else cout << "Invalid room number" << endl;
}

Booking* Hotel::getBookingByRoomId(int roomId)
{
    for (int i = 0; i < bookings.size(); i++)
        if (bookings[i]->getRoomId() == roomId)
            if (bookings[i]->inPeriod(Date())) return bookings[i];

    Booking* temp = new Booking();
    return temp;
}

void Hotel::getInfo()
{
    for (size_t i = 0; i < rooms.size(); i++) rooms[i]->getInfo();

    for (size_t j = 0; j < bookings.size(); j++) bookings[j]->getInfo();
}

void Hotel::availability(Date date) {
    vector<int> availableRoomIds;

    for (int i = 0; i < bookings.size(); i++) {
        Booking* booking = bookings[i];
        int id = booking->getRoomId();

        if (!booking->inPeriod(date)) availableRoomIds.push_back(id);
    }

    for (int i = 0; i < rooms.size(); i++) {
        int roomId = rooms[i]->getId();
        bool bookingExists = false;
        for (int j = 0; j < bookings.size(); j++) {
            int id = bookings[j]->getRoomId();

            if (id == roomId) bookingExists = true;
        }
        if (!bookingExists) availableRoomIds.push_back(roomId);
    }
    string output = "Here is a list of all the available rooms on " + date.getInfo() + ": ";
    cout << output;

    for (int i = 0; i < availableRoomIds.size(); i++) cout << availableRoomIds[i] << ", ";
    cout << endl;
}

void Hotel::report(Date from, Date to) {
    cout << "Here  is a report of all the unavailable rooms from " << from.getInfo() << " to " << to.getInfo() << " :" << endl;

    for (int j = 0; j < rooms.size(); j++) {
        int result = 0;
        int id = rooms[j]->getId();
        vector<Booking*> bookingsOfThisRoom = getAllBookingsById(id);

        for (int i = 0; i < bookingsOfThisRoom.size(); i++) {
            Booking* booking = bookingsOfThisRoom[i];

            result += booking->getActiveDaysInPeriod(from, to);
        }
        if (result != 0) cout << "Room " << id << " was unavailable for " << result << " days." << endl;
    }
}

vector<Booking*> Hotel::getAllBookingsById(int roomId) {
    vector<Booking*> vector;

    for (int j = 0; j < bookings.size(); j++)
        if (bookings[j]->getRoomId() == roomId)
            vector.push_back(bookings[j]);
    return vector;
}

bool Hotel::isRoomAvailableInPeriod(int roomId, Date from, Date to) {
    bool isAvaialble = true;

    vector<Booking*> bookingsOfThisRoom = getAllBookingsById(roomId);
    for (int i = 0; i < bookingsOfThisRoom.size(); i++)
        if (bookingsOfThisRoom[i]->getActiveDaysInPeriod(from, to) != 0) isAvaialble = false;

    return isAvaialble;
}

void Hotel::find(int beds, Date from, Date to) {
    int prefferableRoom = 0;
    int minBeds = -1;

    for (int i = 0; i < rooms.size(); i++) {
        int roomId = rooms[i]->getId();
        int numberOfBeds = rooms[i]->getNumberOfBeds();

        if (isRoomAvailableInPeriod(roomId, from, to) && beds <= numberOfBeds) {
            if (minBeds > numberOfBeds || minBeds == -1) {
                minBeds = numberOfBeds;
                prefferableRoom = roomId;
            }
        }
    }
    if (prefferableRoom == 0) cout << "No rooms with at least " << beds << " beds are currently available. Try again later :)" << endl;
    else cout << "Found! Room " << prefferableRoom << " has " << minBeds << " beds and is available in the specified period" << endl;
}
