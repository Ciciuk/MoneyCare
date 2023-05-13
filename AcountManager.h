#ifndef ACOUNTMANAGER_H
#define ACOUNTMANAGER_H

#include "Record.h"
#include "ExpensesFile.h"
#include "IncomesFile.h"

#include <vector>

using namespace std;

class AcountManager {
   vector <Record> expenses;
   vector <Record> incomes;
   ExpensesFile expensesFile;
   IncomesFile incomesFile;
   const int CURRENT_USER_ID;

   bool checkIfEmptyIncomes();
   bool checkIfEmptyExpenses();
   
   int howManyDaysInThisMonth(int year, int month);
   bool checkIfDateIsCorrect(string date);
   time_t getDate();

  public: 
   AcountManager(string expensesFileName, string incomesFileName, int userId) : expensesFile(expensesFileName), incomesFile(incomesFileName), CURRENT_USER_ID(userId) {
      expenses = expensesFile.loadRecordsByUserId(CURRENT_USER_ID);
      incomes = incomesFile.loadRecordsByUserId(CURRENT_USER_ID);
   }
   
   Record recordDataGathering();

};

#endif