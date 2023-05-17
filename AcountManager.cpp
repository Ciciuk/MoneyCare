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

bool AcountManager::checkIfDateIsCorrect(const string &date) { //data w tm formacie jest przechowywana rok - 1900, miesiąc - 1;
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
    income.setAmount(stringToDouble(AuxilaryMethods::getWholeLine()));
    cout << endl;

    return income;
}

Record AcountManager::expensesDataGathering() {
    Record expenses;

    cout << "-----Wprowadzanie Wydatku---------" << endl;

    cout << "Data przychodu jest dzisiejsza? Jesli tak potwierdz \" T \" " << endl;
    if (AuxilaryMethods::getOneChar() == 'T')
        expenses.setDate(time(0));
    else
        expenses.setDate(getDate());
    cout << endl;

    cout << "Czego dotyczy przychod: " << endl;
    expenses.setItem(AuxilaryMethods::getWholeLine());
    cout << endl;

    cout << "Kwota przychodu: " << endl;
    expenses.setAmount(stringToDouble(AuxilaryMethods::getWholeLine()));
    cout << endl;

    return expenses;
}

double AcountManager::stringToDouble(const string &number) {
    string x = number;

    size_t pos = x.find(',');
    if (pos != -1)
        x.replace(pos, 1, ".");

    return stod(x);
}

void AcountManager::addNewIncome() {
    Record newRecord = incomeDataGathering();
    newRecord.setRecordId(incomesFile.getLastId() + 1);
    newRecord.setUserId(CURRENT_USER_ID);

    incomes.push_back(newRecord);
    incomesFile.saveNewRecord(newRecord);
}

void AcountManager::addNewExpenses() {
    Record newRecord = incomeDataGathering();
    newRecord.setRecordId(expensesFile.getLastId() + 1);
    newRecord.setUserId(CURRENT_USER_ID);

    expenses.push_back(newRecord);
    expensesFile.saveNewRecord(newRecord);
}

void AcountManager::displayExpense(const vector<Record>::iterator expense) {
    time_t date = expense->getDate();
    char dateString[50];

        cout << left << setw(20) << "ID:" << expense->getRecordId() << endl;
    cout << left << setw(20) << "Nazwa wydatku:" << expense->getItem() << endl;
    strftime(dateString, 50, "%Y-%m-%d", gmtime(&date));
    cout << left << setw(20) << "Data:" << dateString << endl;
    cout << left << setw(20) << "Wartosc przychodu:" << fixed << setprecision(2) << round(expense->getAmount()) << endl;
}

void AcountManager::displayIncome(const vector<Record>::iterator income) {
    time_t date = income->getDate();
    char dateString[50];

    cout << left << setw(20) << "ID:" << income->getRecordId() << endl;
    cout << left << setw(20) << "Nazwa przychodu:" << income->getItem() << endl;
    strftime(dateString, 50, "%Y-%m-%d", gmtime(&date));
    cout << left << setw(20) << "Data:" << dateString << endl;
    cout << left << setw(20) << "Wartosc przychodu:" << fixed << setprecision(2) << income->getAmount() << endl;
}

void AcountManager::sortAcountInAscendingOrder() {
    sort(expenses.begin(), expenses.end(), [](const Record& l, const Record& r) {
        return (l.getDate() < r.getDate());
    });

    sort(incomes.begin(), incomes.end(), [](const Record& l, const Record& r) {
        return (l.getDate() < r.getDate());
    });
}

time_t AcountManager::cutOffCurrentMonthUp() {
    time_t currentTime = time(0);
    tm currentDate = *gmtime(&currentTime);

    if (currentDate.tm_mon == 11) {
        currentDate.tm_mday = 0;
        currentDate.tm_year += 1;
    } else
        currentDate.tm_mon += 1;

    currentDate.tm_mday = 1;
    currentDate.tm_sec = 0;
    currentDate.tm_min = 0 ;
    currentDate.tm_hour = 1;

        return mktime(&currentDate);
}

time_t AcountManager::cutOffCurrentMonthDown() {
    time_t currentTime = time(0);
    tm currentDate = *gmtime(&currentTime);

    currentDate.tm_mday = 1;
    currentDate.tm_sec = 0;
    currentDate.tm_min = 0;
    currentDate.tm_hour = 1;

    return mktime(&currentDate);
}

time_t AcountManager::cutOffPreviousMonthUp() {
    time_t currentTime = time(0);
    tm currentDate = *gmtime(&currentTime);

    currentDate.tm_mday = 1;
    currentDate.tm_sec = 0;
    currentDate.tm_min = 0;
    currentDate.tm_hour = 1;

    return mktime(&currentDate);
}

time_t AcountManager::cutOffPreviousMonthDown() {
    time_t currentTime = time(0);
    tm currentDate = *gmtime(&currentTime);

    if (currentDate.tm_mon == 0) {
        currentDate.tm_mon = 12;
        currentDate.tm_year -= 1;
    } else
        currentDate.tm_mon -= 1;

    currentDate.tm_mday = 1;
    currentDate.tm_sec = 0;
    currentDate.tm_min = 0;
    currentDate.tm_hour = 1;

    return mktime(&currentDate);
}

void AcountManager::displayAccountinCurrentMonth() {
    double sumIncomes = 0, sumExpenses = 0;
    time_t cutOfDateUp = cutOffCurrentMonthUp();
    time_t cutOfDateLow = cutOffCurrentMonthDown();

    sortAcountInAscendingOrder();

    cout << left << setw(20) << "-------Przychody w obecnym miesiacu:-------" << endl;
    for ( vector<Record>::iterator i = incomes.begin(); i < incomes.end(); i++ ){
        if (i->getDate() < cutOfDateUp && i->getDate() >= cutOfDateLow){
             displayIncome(i);
             sumIncomes += i->getAmount();
        }
    }

    cout << left << setw(20) << "-------Wydatki w obecnym miesiacu:-------" << endl;
    for (vector<Record>::iterator i = expenses.begin(); i < expenses.end(); i++) {
        if (i->getDate() < cutOfDateUp && i->getDate() >= cutOfDateLow) {
             displayIncome(i);
             sumExpenses += i->getAmount();
        }
    }

    cout << left << setw(20) << "Laczne przychody w obecnym miesiacu wyniosly: " << sumIncomes << endl;
    cout << left << setw(20) << "Laczne wydatki w obecnym miesiacu wyniosly: " << sumExpenses << endl;
    cout << left << setw(20) << "Bilans w obecnym miesiacu wynosi: " << sumIncomes - sumExpenses << endl;
}