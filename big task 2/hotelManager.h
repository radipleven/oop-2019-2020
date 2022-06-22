#ifndef hotelManager_header
#define hotelManager_header
#include "hotel.h"
#include <iostream>
using namespace std;

class HotelManager {
private:
    string fileName;
    Hotel hotel;


public:
    HotelManager();

    string getFileName();
    void setFileName(string name);

    Hotel* getHotel();  //problemno
    //void setHotel(Hotel hotel);

    bool isOpened();
    void read(string name);
    void save();
    void close();
    void saveAs(string name);
    void help();
};


#endif
