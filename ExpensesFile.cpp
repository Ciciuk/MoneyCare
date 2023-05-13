#include "ExpensesFile.h"

vector<Record> ExpensesFile::loadRecordsByUserId(int id) {
    CMarkup xml;
    vector <Record> vrecord;
    Record record;
    string fileName = "";
    int lastId;

    fileName.append(File::getName());
    fileName.append(".xml");
    xml.Load(fileName);

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
        lastId = record.getRecordId();
    }
        File::setLastId(lastId);
        return vrecord;
}

void ExpensesFile::saveNewRecord(const Record expense) {
    CMarkup xml;
    char dateString[50];
    string fileName = "";
    time_t time = expense.getDate();



    fileName.append(File::getName());
    fileName.append(".xml");
    bool fileExists = xml.Load(fileName);
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