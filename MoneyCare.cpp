#include "MoneyCare.h"

void MoneyCare::registration() {
    userManager.newUserRegistration();
}
void MoneyCare::logging() {
    if (userManager.logginng())
        acountManager = new AcountManager(EXPENSES_FILE_NAME, INCOMES_FILE_NAME, userManager.getLoggedUserId());
}

void MoneyCare::insertNewIncome(){
    acountManager->addNewIncome();
}

void MoneyCare::insertNewExpense() {
    acountManager->addNewExpenses();
}

void MoneyCare::displayAccountInCurrentMonth() {
    acountManager->displayAccountinCurrentMonth();
}

void MoneyCare::displayAccountInPreviousMonth() {
    acountManager->displayAccountinLasttMonth();
}

void MoneyCare::displayAccountInChosenPeriod() {
    acountManager->displayAccountinChosenPeriod();
}

void MoneyCare::changePassword(){
    userManager.changePassword();
}

void MoneyCare::logout() {
    userManager.setLoggedUserId(0);
    delete acountManager;
    acountManager = NULL;
}

bool MoneyCare::isSomeUserLogged(){
    return (userManager.getLoggedUserId() != 0);
}

void MoneyCare::displayMainMenu() {
    cout << "1. Logowanie" << endl;
    cout << "2. Rejestracja" << endl;
    cout << "9. Wyjdz" << endl;
}

void MoneyCare::displayInternalMenu() {
    cout << "1. Dodaj przychod" << endl;
    cout << "2. Dodaj wydatek" << endl;
    cout << "3. Bilans z bierzacego miesiaca" << endl;
    cout << "4. Bilans z poprzedniego miesiaca" << endl;
    cout << "5. Bilans z wybranego okresu" << endl;
    cout << "6. Zmien haslo" << endl;
    cout << "9. Wyloguj sie" << endl;
}