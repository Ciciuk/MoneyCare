#include "MoneyCare.h"

using namespace std;

int main() {
    char menuChoice;

    MoneyCare moneyCare("users","expenses","incomes");

    while (1) {
        system("cls");
        moneyCare.displayMainMenu();
        menuChoice = AuxilaryMethods::getOneChar();
        switch (menuChoice) {
            case '1':
                moneyCare.logging();
                break;
            case '2':
                moneyCare.registration();
                break;
            case '9':
                return 0;
            default:
                break;
        }
        while (moneyCare.isSomeUserLogged()) {
            system("cls");
            moneyCare.displayInternalMenu();
            menuChoice = AuxilaryMethods::getOneChar();
            switch (menuChoice) {
                case '1':
                    moneyCare.insertNewIncome();
                    break;
                case '2':
                    moneyCare.insertNewExpense();
                    break;
                case '3':
                    moneyCare.displayAccountInCurrentMonth();
                    break;
                case '4':
                    moneyCare.displayAccountInPreviousMonth();
                    break;
                case '5':
                    moneyCare.displayAccountInChosenPeriod();
                    break;
                case '6':
                    moneyCare.changePassword();
                    break;
                case '9':
                    moneyCare.logout();
                    break;
                default:
                    break;
            }
        }
    }

    return 0;
}