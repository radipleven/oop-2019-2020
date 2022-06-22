#ifndef room_header
#define room_header
#include <iostream>
#include "date.h"

class Room {
private:
    int id;
    int numberOfBeds;
    bool availability;
public:

    Room(int id, int numberOfBeds);
    Room();

    int getId();
    void setId(int id);

    int getNumberOfBeds();
    void setNumberOfBeds(int numberOfBeds);

    bool isAvailable();
    void setAvailability(bool availability);

    void getInfo();

    string getConfig();
};
#endif
