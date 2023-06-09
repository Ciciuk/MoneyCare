#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <ctime>

using namespace std;

class Record {
    int recordId;
    int userId;
    time_t date;
    string item;
    double amount;

   public:
    Record(int recordId = 0, int userId = 0, time_t date = 0, string item = "", double amount = 0.0) {
        this->recordId = recordId;
        this->userId = userId;
        this->date = date;
        this->item = item;
        this->amount = amount;
    };

    int getRecordId() const;
    int getUserId() const;
    time_t getDate() const;
    string getItem() const;
    double getAmount() const;

    void setRecordId(int incomeId);
    void setUserId(int userId);
    void setDate(time_t date);
    void setItem(string item);
    void setAmount(double amount);
};

#endif