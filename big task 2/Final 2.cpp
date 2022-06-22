#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "hotel.h"
#include "room.h"
#include "booking.h"
#include "date.h"
#include "hotelManager.h"
#include "function.h"

using namespace std;


bool containsCommand(string command, string input)
{
    return input.rfind(command + " ", 0) == 0;
}

int main()
{
    HotelManager hotelManager;

    while (true)
    {
        string input;
        string command;
        getline(cin, input);

        if (input.compare("exit") == 0)
        {
            cout << "Exiting the program..." << endl;
            break;
        }
        else if (input.compare("help") == 0) hotelManager.help();
        else if (containsCommand("open", input))
        {
            if (!hotelManager.isOpened())
            {
                vector<string> words = Function().splitBySpace(input);

                string fileName = words[1];
                hotelManager.read(fileName);
            }
            else cout << "Another file is currently in use. Please close all files in order to open a new one." << endl;
        }
        else if (input.compare("save") == 0)
        {
            if (hotelManager.isOpened()) hotelManager.save();
            else cout << "No file is currently open" << endl;
        }
        else if (containsCommand("saveas", input))
        {
            if (hotelManager.isOpened()) {
                vector<string> words = Function().splitBySpace(input);
                hotelManager.saveAs(words[1]);
            }
            else cout << "No file is currently open" << endl;
        }
        else if (input.compare("close") == 0)
        {
            if (hotelManager.isOpened()) hotelManager.close();
            else cout << "No file is currently open" << endl;
        }
        else if ((containsCommand("checkin", input) || containsCommand("unavailable", input)) && hotelManager.isOpened())
        {
            Hotel* hotel = hotelManager.getHotel();
            hotel->checkIn(input);
        }
        else if (containsCommand("checkout", input) && hotelManager.isOpened())
        {
            Hotel* hotel = hotelManager.getHotel();
            hotel->checkOut(input);

        }
        else if ((input.compare("availability") == 0 || containsCommand("availability", input)) && hotelManager.isOpened()) {
            vector<string> words = Function().splitBySpace(input);

            Date date;
            if (words.size() == 2) date = Date(words[1]);

            if (date.isValid()) hotelManager.getHotel()->availability(date);
            else cout << "Invalid Date format" << endl;
        }
        else if (containsCommand("report", input) && hotelManager.isOpened()) {
            vector<string> words = Function().splitBySpace(input);

            Date from = Date(words[1]);
            Date to = Date(words[2]);
            if (from.isValid() && to.isValid())
                if (from.compareDates(to) != 1) hotelManager.getHotel()->report(from, to);
                else cout << "Please specify a valid date period." << endl;
            else cout << "Invalid Date Format" << endl;
        }
        else if (containsCommand("find", input) && hotelManager.isOpened()) {
            vector<string> words = Function().splitBySpace(input);

            if (Function().isNumber(words[1])) {
                int beds = Function().strToInt(words[1]);
                if (beds > 0) {
                    Date from = Date(words[2]);
                    Date to = Date(words[3]);
                    if (from.isValid() && to.isValid())
                        if (from.compareDates(to) != 1) hotelManager.getHotel()->find(beds, from, to);
                        else cout << "Please specify a valid date period." << endl;
                    else cout << "Invalid Date Format." << endl;
                }
                else cout << "Invalid number of beds." << endl;
            }
            else cout << "Invalid command syntax" << endl;
        }
        else if ((input.compare("info") == 0) && hotelManager.isOpened()) {
            hotelManager.getHotel()->getInfo();
        }
        else cout << "Invalid command. Type help for a list of commands." << endl;
    }
    return 0;
}


