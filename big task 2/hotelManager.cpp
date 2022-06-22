#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "hotel.h"
#include "hotelManager.h"
#include "room.h"
#include "booking.h"
#include "date.h"
#include "function.h"
using namespace std;

HotelManager::HotelManager()
{
}

Hotel* HotelManager::getHotel()
{
    return &hotel;
}

void HotelManager::read(string name)
{
    string line;
    ifstream myfile(name);
    fileName = name;
    while (myfile.good())
    {
        string type;
        getline(myfile, type, ',');
        if (type.compare("Room") == 0)
        {
            string roomId;
            string numberOfBeds;
            string availability;

            getline(myfile, roomId, ',');
            getline(myfile, numberOfBeds, '\n');
            Room* room = new Room(Function().strToInt(roomId), Function().strToInt(numberOfBeds));
            this->hotel.addRoom(room);

        }
        else if (type.compare("Booking") == 0)
        {
            string from;
            string to;
            string numberOfGuests;
            string roomId;
            string note;

            getline(myfile, from, ',');
            getline(myfile, to, ',');
            getline(myfile, numberOfGuests, ',');
            getline(myfile, roomId, ',');
            getline(myfile, note, '\n');
            Booking* booking = new Booking(Date(from), Date(to), Function().strToInt(numberOfGuests), Function().strToInt(roomId), note);
            hotel.addBooking(booking);

            Date currentDate;
            if (booking->inPeriod(currentDate)) hotel.getRoomById(Function().strToInt(roomId))->setAvailability(false);
        }
    }

    myfile.close();
    cout << "Successfully opened " << fileName << endl;
}

void HotelManager::save()
{
    saveAs(fileName);
}

void HotelManager::saveAs(string name)
{
    fstream fs(name, ios::out | ios::binary);

    for (int i = 0; i < hotel.getRooms().size(); i++) {
        string config = hotel.getRooms()[i]->getConfig();
        size_t size = config.size();

        char *output = new char[size + 1];
        strcpy(output, config.c_str());

        fs.write(output, size);

        delete[]output;
    }

    for (int i = 0; i < hotel.getBookings().size(); i++) {
        string config = hotel.getBookings()[i]->getConfig();
        size_t size = config.size();

        char *output = new char[size + 1];
        strcpy(output, config.c_str());

        fs.write(output, size);
        delete[] output;
    }
    fs.close();

    cout << "Succesfully saved " << name << endl;
}

string HotelManager::getFileName()
{
    return fileName;
}

void HotelManager::setFileName(string name)
{
    fileName = name;
}

void HotelManager::help()
{
    cout << "The following commands are supported:" << endl;
    cout << "open <file>        opens <file>" << endl;
    cout << "close                closes currently opened file" << endl;
    cout << "save                saves the currently open file" << endl;
    cout << "saveas <file>        saves the currently open file in <file>" << endl;
    cout << "help                prints this information" << endl;
    cout << "exit                exists the program" << endl;
}

bool HotelManager::isOpened()
{
    return fileName.compare("") != 0;

}

void HotelManager::close()
{
    setFileName("");
    hotel.emptyHotel();
    cout << "Closed." << endl;

}
