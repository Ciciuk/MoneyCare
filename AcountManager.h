#ifndef ACOUNTMANAGER_H
#define ACOUNTMANAGER_H

#include <algorithm>
#include <vector>
#include <math.h>

#include "ExpensesFile.h"
#include "IncomesFile.h"
#include "Record.h"

using namespace std;

class AcountManager {
   vector <Record> expenses;
   vector <Record> incomes;
   ExpensesFile expensesFile;
   IncomesFile incomesFile;
   const int CURRENT_USER_ID;

   bool checkIfEmptyIncomes();
   bool checkIfEmptyExpenses();
   
   int howManyDaysInThisMonth(const int year, const int month);
   bool checkIfDateIsCorrect(const string &date);
   time_t getDate();
   double stringToDouble(const string &number);
   Record incomeDataGathering();
   Record expensesDataGathering();
   void displayExpense(const vector<Record>::iterator expense);
   void displayIncome(const vector<Record>::iterator income);
   void sortAcountInAscendingOrder();
   time_t cutOffCurrentMonthUp();
   time_t cutOffCurrentMonthDown();
   time_t cutOffPreviousMonthUp();
   time_t cutOffPreviousMonthDown();

  public:
   AcountManager(string expensesFileName, string incomesFileName, int userId) : expensesFile(expensesFileName), incomesFile(incomesFileName), CURRENT_USER_ID(userId) {
       expenses = expensesFile.loadRecordsByUserId(CURRENT_USER_ID);
       incomes = incomesFile.loadRecordsByUserId(CURRENT_USER_ID);
   }
   
   void addNewIncome();
   void addNewExpenses();
   void displayAccountinCurrentMonth();

};

#endif