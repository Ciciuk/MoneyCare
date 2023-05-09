#include "Income.h"

int Record::getRecordId() const{
    return recordId;
};

int Record::getUserId() const {
    return userId;
};

tm Record::getDate() const {
    return date;
};

string Record::getItem() const {
    return item;
};

double Record::getAmount() const {
    return amount;
};

void Record::setRecordId(int incomeId){
    this->recordId = incomeId;
};

void Record::setUserId(int userId){
    this->userId = userId;
};

void Record::setDate(struct tm date){
    this->date = date;
};

void Record::setItem(string item){
    this->item = item;
};

void Record::setAmount(double amount){
    this->amount = amount;
};