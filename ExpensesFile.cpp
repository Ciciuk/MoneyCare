#include "ExpensesFile.h"

vector<Record> ExpensesFile::loadRecordsByUserId(int id) {
    CMarkup xml;
    vector <Record> vrecord;
    Record record;
    //string temp = "";

    bool fileExists = xml.Load("expenses.xml");

    xml.FindElem();
    xml.IntoElem();  // Expenses
    while (xml.FindElem("Expense")) {
        xml.FindChildElem("ExpenseId");
        record.setRecordId(stoi(xml.GetChildData()));
        xml.FindChildElem("UserId");
        record.setUserId(stoi(xml.GetChildData()));
        xml.FindChildElem("Date");
        tm temp = AuxilaryMethods::dateParseStringToTm(xml.GetChildData());
        record.setDate(mktime(&temp));
        xml.FindChildElem("Item");
        record.setItem(xml.GetChildData());
        xml.FindChildElem("Amount");
        record.setAmount(stod(xml.GetChildData()));
        if(record.getUserId() == id)
            vrecord.push_back(record);
    }

    return vrecord;
}

void ExpensesFile::saveNewRecord(const Record expense) {
    CMarkup xml;
    time_t time = expense.getDate();
    bool fileExists = xml.Load("expenses.xml");
    char dateString[50];

    if (!fileExists) {
        xml.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        xml.AddElem("Expenses");
    }

    xml.FindElem();
    xml.IntoElem();
    xml.AddElem("Expense");
    xml.IntoElem();
    xml.AddElem("ExpenseId", expense.getRecordId());
    xml.AddElem("UserId", expense.getUserId());
    strftime(dateString, 50, "%Y-%m-%d", gmtime(&time));
    xml.AddElem("Date", dateString);
    xml.AddElem("Item", expense.getItem());
    xml.AddElem("Amount", to_string(expense.getAmount()));
    xml.Save("expenses.xml");
}