#include "AuxilaryMethods.h"

using namespace std;

string AuxilaryMethods::getWholeLine() {
    string line;

    cin.sync();
    getline(cin, line);

    return line;
}

char AuxilaryMethods::getOneChar() {
    string input = "";
    char sign = {0};

    while (true) {
        cin.sync();
        getline(cin, input);
        if (input.length() == 1) {
            sign = input[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }

    return sign;
}

int AuxilaryMethods::getId() {
    string line;
    int number = 0;

    while (true) {
        cin.sync();
        getline(cin, line);
        stringstream input(line);
        if (input >> number)
            break;
        cout << "Niepoprawne ID wpisz ponownie" << endl;
    }

    return number;
}

tm AuxilaryMethods::dateParseStringToTm(string dateInString) {  // wyciaganie danych ze stringa do formatu daty (tm), strptime nie znalazłem w bibliotece ...
    tm date = {0, 0, 2, 0, 0, 0, 0, 0, 1};
    string temp;
    stringstream ss(dateInString);

    ss >> get_time(&date, "%Y-%m-%d");

    return date;
}