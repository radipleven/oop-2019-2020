#ifndef booking_header
#define booking_header

#include <string>
using namespace std;
#include "room.h"
#include "date.h"

class Booking {
private:
    Date from;
    Date to;
    int roomId;
    int numberOfGuests;
    string note;

public:
    Booking(Date from, Date to, int numberOfGuests, int roomId, string note);
    Booking();

    Date getFrom();
    void setFrom(Date from);

    Date getTo();
    void setTo(Date to);

    int getRoomId();
    void setRoomId(int roomId);

    int getNumberOfGuests();
    void setNumberOfGuests(int numberOfGuests);

    string getNote();
    void setNote(string note);

    void getInfo();

    bool inPeriod(Date target);

    int getActiveDaysInPeriod(Date from, Date to);

    string getConfig();
};
#endif
