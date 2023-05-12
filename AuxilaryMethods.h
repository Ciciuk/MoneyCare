#ifndef AUXILARYMETHODS_H
#define AUXILARYMETHODS_H

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class AuxilaryMethods {
   public:
    static string getWholeLine();
    static char getOneChar();
    static int getId();
    static tm dateParseStringToTm(string dateInString);
};

#endif