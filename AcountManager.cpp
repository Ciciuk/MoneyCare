#include "AcountManager.h"

bool AcountManager::checkIfEmptyIncomes() {
    if (incomes.empty()) {
        cout << "Brak zapisanych przychodow ";
        system("pause");
        return true;
    }

    return false;
}

bool AcountManager::checkIfEmptyExpenses() {
    if (expenses.empty()) {
        cout << "Brak zapisanych wydatków ";
        system("pause");
        return true;
    }

    return false;
}

time_t AcountManager::getDate(){
    string stringDate;
    tm tmDate;
    bool loopOn = true;

    while (loopOn) {
        cout << "Podaj date w formacie rrrr-mm-dd: " << endl;
        stringDate = AuxilaryMethods::getWholeLine();
        if (checkIfDateIsCorrect(stringDate)){
            tmDate = AuxilaryMethods::dateParseStringToTm(stringDate);
            loopOn = false;
        }
        else
            cout << "Data niepoprawna!" << endl;
    }

    return mktime(&tmDate);
}

int AcountManager::howManyDaysInThisMonth(int year, int month) {
    int arr[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2 && ((year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0))))
        return arr[month - 1] + 1;

    else
        return arr[month - 1];

    return 0;
}

bool AcountManager::checkIfDateIsCorrect(string date) { //data w tm formacie jest przechowywana rok - 1900, miesiąc - 1;
    tm tmDate = AuxilaryMethods::dateParseStringToTm(date);
    tm cutOfDate = AuxilaryMethods::dateParseStringToTm("2023-05-31");


    if (tmDate.tm_year < 100)
        return false;
    else if ((tmDate.tm_mon < 0) || (tmDate.tm_mday == 0))
        return false;
    else if ((tmDate.tm_mday <= 0) || (tmDate.tm_mday > howManyDaysInThisMonth(tmDate.tm_year + 1900, tmDate.tm_mon + 1)))
        return false;
    else if (mktime(&tmDate) > mktime(&cutOfDate))
        return false;

    return true;
}

Record AcountManager::incomeDataGathering() {
    Record income;


    cout << "-----Wprowadzanie Przychodu---------" << endl;

    cout << "Data przychodu jest dzisiejsza? Jesli tak potwierdz \" T \" " << endl;
    if(AuxilaryMethods::getOneChar() == 'T')
        income.setDate(time(0));
    else 
        income.setDate(getDate());
    cout << endl;

    cout << "Czego dotyczy przychod: " << endl;
    income.setItem(AuxilaryMethods::getWholeLine());
    cout << endl;

    cout << "Kwota przychodu: " << endl;
    income.setItem(AuxilaryMethods::getWholeLine());
    cout << endl;

    return income;
}

double AcountManager::stringToDouble(const string &number) {
    string x = number;

    size_t pos = x.find(',');
    if (pos != -1)
        x.replace(pos, 1, ".");

    return stod(x);
}