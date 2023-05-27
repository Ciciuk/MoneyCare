#ifndef MONEYCARE_H
#define MONEYCARE_H

#include "AuxilaryMethods.h"
#include "AcountManager.h"
#include "UserManager.h"

using namespace std;

class MoneyCare {
    UserManager userManager;
    AcountManager *acountManager;
    const string INCOMES_FILE_NAME;
    const string EXPENSES_FILE_NAME;

   public:
    MoneyCare(string userFileName, string expenseFileName, string incomesFileName) : userManager(userFileName), EXPENSES_FILE_NAME(expenseFileName), INCOMES_FILE_NAME(incomesFileName) {
        acountManager = NULL;
    };

    ~MoneyCare(){
        delete acountManager;
        acountManager = NULL;
    };

    void displayMainMenu();
    void displayInternalMenu();
    void registration();
    void logging();
    void loginMenu();
    void changePassword();
    void logout();
    bool isSomeUserLogged();
    void insertNewIncome();
    void insertNewExpense();
    void displayAccountInCurrentMonth();
    void displayAccountInPreviousMonth();
    void displayAccountInChosenPeriod();
};
#endif