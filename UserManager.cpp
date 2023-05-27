#include "UserManager.h"

int UserManager::getLoggedUserId() {
    return loggedUser.getId();
}

void UserManager::setLoggedUserId(int id) {
    loggedUser.setId(id);
}

void UserManager::loadUsersFromFile() {
    users = userFile.loadUsersFromFile();
}

void UserManager::newUserRegistration() {
    system("cls");
    User newUser;
    newUser = userDataGathering();

    if (users.empty())
        newUser.setId(1);
    else
        newUser.setId(users.back().getId() + 1);

    users.push_back(newUser);
    userFile.saveNewUserInFile(newUser);

    cout << "Rejestracja zakonczona" << endl;
    system("pause");
}

User UserManager::userDataGathering() {
    string login;
    User newUser;

    cout << setw(20) << "----------Rejestracja----------- " << endl;

    do {
        cout << "Podaj login: " << endl;
        login = AuxilaryMethods::getWholeLine();
    } while (checkIfLoginIsNotUnique(login));
    newUser.setLogin(login);

    cout << "Podaj haslo: " << endl;
    newUser.setPassword(AuxilaryMethods::getWholeLine());

    cout << "Podaj imie: " << endl;
    newUser.setName(AuxilaryMethods::getWholeLine());

    cout << "Podaj nazwisko: " << endl;
    newUser.setSurname(AuxilaryMethods::getWholeLine());

    return newUser;
}

bool UserManager::checkIfLoginIsNotUnique( const string login) {
    for (size_t i = 0; i < users.size(); i++) {
        if (users[i].getLogin() == login) {
            cout << "Login juz istnieje, podaj inny login" << endl;
            system("pause");
            return true;
        }
    }

    return false;
}

bool UserManager::checkLoginAndPassword() {
    system("cls");
    string login;

    if (checkIfEmptyUsers())
        return false;

    cout << setw(20) << "----------Logowanie----------- " << endl;
    cout << "Podaj login:  " << endl;
    login = AuxilaryMethods::getWholeLine();

    for (vector<User>::iterator i = users.begin(); i < users.end(); i++) {
        if (login == i->getLogin()) {
            if (checkPassword(i)) {
                loggedUser = *i;
                return true;
            } else{
                loggedUser.setId(0);
                return false;
            } 
        }
    }

    cout << "Brak loginu w bazie danych:  ";
    system("pause");

    loggedUser.setId(0);
    return false;
}

bool UserManager::checkIfEmptyUsers() {
    if (users.empty()) {
        cout << "Brak zarejestrowanych uzytkownikow ";
        system("pause");
        return true;
    }

    return false;
}

bool UserManager::checkPassword(vector<User>::iterator i) {
    string password;

    for (int j = 3; j > 0; j--) {
        cout << "Pozostalo Ci: " << j << " prob" << endl;
        cout << "Podaj haslo: " << endl;
        password = AuxilaryMethods::getWholeLine();
        if (password == i->getPassword()) {
            cout << "Gratuluje, poprawne haslo" << endl;
            system("pause");
            return true;
        } else {
            cout << "Nieprawidlowe haslo" << endl;
            cout << endl;
            system("pause");
        }
    }

    cout << "Wykorzystano wszystkie proby, nastapi przekierowanie na ekran glowny" << endl;
    system("pause");

    return false;
}

bool UserManager::logginng() {
    if (checkLoginAndPassword()) {
        cout << "Uzytkownik zalogowany ";
        system("pause");
        return true;
    } else {
        cout << "Nie udalo sie zalogowac! ";
        system("pause");
        return false;
    }
}

void UserManager::changePassword() {
    vector<User>::iterator i;
    for (i = users.begin(); i < users.end(); i++) {
        if (i->getId() == loggedUser.getId())
            break;
    }
    
    system("cls");
    cout << setw(20) << "----------Zmiana hasla----------- " << endl;
    cout << "Podaj nowe haslo: ";

    i->setPassword(AuxilaryMethods::getWholeLine());

    userFile.saveUserAfterPaswordChange(*i);

    cout << "Haslo zostalo zmienione: ";
    system("pause");
}