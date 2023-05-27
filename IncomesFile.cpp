#include "IncomesFile.h"

vector<Record> IncomesFile::loadRecordsByUserId(int id) {
    CMarkup xml;
    vector <Record> vrecord;
    Record record;
    string fileName = "";
    int lastId;

    fileName.append(File::getName());
    fileName.append(".xml");
    xml.Load(fileName);

    xml.FindElem();
    xml.IntoElem();  // Incomes
    while (xml.FindElem("Income")) {
        xml.FindChildElem("IncomeId");
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

void IncomesFile::saveNewRecord(const Record income) {
    CMarkup xml;
    time_t time = income.getDate();
    char dateString[50];
    string fileName = "";

    fileName.append(File::getName());
    fileName.append(".xml");
    bool fileExists = xml.Load(fileName);
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
    strftime(dateString, 50, "%Y-%m-%d", gmtime(&time));
    xml.AddElem("Date", dateString);
    xml.AddElem("Item", income.getItem());
    xml.AddElem("Amount", to_string(income.getAmount()));
    xml.Save(fileName);

    File::setLastId(income.getRecordId());
}