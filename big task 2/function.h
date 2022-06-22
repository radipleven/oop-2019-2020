#ifndef function_header
#define function_header

#include <iostream>
#include "room.h"
#include "booking.h"
#include <vector>
using namespace std;

class Function {
public:

    Function();

    int strToInt(string input);
    bool isNumber(const string& s);
    vector<string> splitBySpace(string input);
};
#endif
