#ifndef hotel_header
#define hotel_header
#include <iostream>
#include "room.h"
#include "booking.h"
#include <vector>
using namespace std;

class Hotel {
private:
    vector<Room*>  rooms;
    vector<Booking*>  bookings;


public:

    Hotel();

    vector<Room*> getRooms();
    vector<Booking*>  getBookings();

    void addRoom(Room* room);
    void addBooking(Booking* booking);

    Room* getRoomById(int id);
    Booking* getBookingByRoomId(int roomId);
    vector<Booking*> getAllBookingsById(int roomId);

    void emptyHotel();
    bool doesRoomExist(int roomId);

    void checkIn(string input);
    void checkOut(string input);
    void getInfo();
    void availability(Date date);
    void report(Date from, Date to);

    bool isRoomAvailableInPeriod(int roomId, Date from, Date to);

    void find(int bed, Date from, Date to);
};
#endif
