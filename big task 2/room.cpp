#include <iostream>
#include "room.h"
#include <sstream>
using namespace std;

Room::Room(int id, int numberOfBeds)
{
    setId(id);
    setNumberOfBeds(numberOfBeds);
    setAvailability(true);
};

Room::Room() :Room(0, 1)
{
}

int Room::getId()
{
    return id;
}

void Room::setId(int id)
{
    this->id = id;
}

int Room::getNumberOfBeds() {
    return numberOfBeds;
}

void Room::setNumberOfBeds(int numberOfBeds)
{
    this->numberOfBeds = numberOfBeds;
}

bool Room::isAvailable()
{
    return availability;
}

void Room::setAvailability(bool availability)
{
    this->availability = availability;
}

void Room::getInfo()
{
    cout << "id:" << this->id << "    "
        << "number of beds: "
        << this->numberOfBeds << "      "
        << "availability: " << this->availability << endl;
}

string Room::getConfig() {
    return "Room," + to_string(id) + "," + to_string(numberOfBeds) + "\n";
}
