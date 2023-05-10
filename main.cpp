#define _XOPEN_SOURCE
#include <time.h>

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "Record.h"
#include "Markup.h"
#include "User.h"

using namespace std;

void UserToXml(const User &user){
    CMarkup xml;

    bool fileExists = xml.Load("users.xml");

    if (!fileExists) {
        xml.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        xml.AddElem("Users");
    }

    xml.FindElem();
    xml.IntoElem();
    xml.AddElem("User");
    xml.IntoElem();
    xml.AddElem("UserId", user.getId());
    xml.AddElem("Login", user.getLogin());
    xml.AddElem("Password", user.getPassword());
    xml.AddElem("Name", user.getName());
    xml.AddElem("Surname", user.getSurname());

    xml.Save("users.xml");
}

tm dateParse(string dateInString) {  // wyciaganie danych ze stringa do formatu daty (tm), strptime nie znalazłem w bibliotece ... 
    tm date = {0,0,0,0,0,0,0,0,1};
    string temp;
    stringstream ss(dateInString);

    ss >> get_time(&date,"%Y-%m-%d");

    return date;
}

void RecordToXml(const Record income) { // zapisywanie danych z vectora do XML 
    CMarkup xml;
    tm time= income.getDate();
    bool fileExists = xml.Load("incomes.xml");
    char dateString[50];

    if (!fileExists) {
        xml.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        xml.AddElem("Incomes");
    }

    xml.FindElem();
    xml.IntoElem();
    xml.AddElem("Income");
    xml.IntoElem();
    xml.AddElem("IncomeId", income.getRecordId());
    xml.AddElem("UserId", income.getUserId());
    strftime(dateString, 50, "%Y-%m-%d", &time);
    xml.AddElem("Date", dateString);
    xml.AddElem("Item", income.getItem());
    xml.AddElem("Amount", to_string(income.getAmount()));
    xml.Save("incomes.xml");
}

vector <Record> xmlToRecord() { // pobieranie danych z xml i zapisywanie do vectora 
    CMarkup xml;
    vector <Record> vrecord;
    Record record;
    string temp = "";

    bool fileExists = xml.Load("incomes.xml");

    xml.FindElem();
    xml.IntoElem(); //Incomes
    while (xml.FindElem("Income")) {
        xml.FindChildElem("IncomeId");
        record.setRecordId(stoi(xml.GetChildData()));
        xml.FindChildElem("UserId");
        record.setUserId(stoi(xml.GetChildData()));
        xml.FindChildElem("Date");
        record.setDate(dateParse( xml.GetChildData()));
        xml.FindChildElem("Item");
        record.setItem(xml.GetChildData());
        xml.FindChildElem("Amount");
        record.setAmount(stod(xml.GetChildData()));
        vrecord.push_back(record);
    }

    return vrecord;
}

tm currentTime(){ //dzisiejsza data 
    time_t t1;
    struct tm *t2;

    time(&t1);
    t2 = localtime(&t1);
    return *t2;
}

int howManyDays(int month, int year){ //ile dni w danym miesiacu i roku 
    int arr[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2 && ((year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0))))
        return arr[month - 1] + 1;

    else
        return arr[month - 1];

    return 0;
}

bool dateComparasion(tm date1, tm date2){ //porownywanie dat, jesli true to data druga jest mlodsza (blizsza aktualnej)
    time_t seconds1 = mktime(&date1);
    time_t seconds2 = mktime(&date2);

    if (seconds1 > seconds2)
        return 0;
    else 
        return 1;
}

int main()
{

    User user1(1,"Mateo","123","Ma","Miciuk");
    user1.setName("Mateusz");
    UserToXml(user1);

    time_t t1;
    struct tm *t2;

    time(&t1);
    t2 = localtime(&t1);
    //localtime(&time(NULL));
    //cout << t2->tm_hour << endl;

    Record income1(1, 1, currentTime(), "wplata", 11.5);
    // IncomeToXml(income1);

    vector <Record> income = xmlToRecord();

    bool sprawdzenie = dateComparasion(income[0].getDate(), income[2].getDate());

    system("pause");
    return 0;
}

int _main(){

    tm czas;
    czas.tm_mon = 4;


    return 0;
}