#include <iostream>
#include <string>
using namespace std;

bool login() {
    const string username = "user";
    const string password = "pass";
    string inputUser, inputPass;
    int attempts = 3;

    while (attempts > 0) { 
    cout << "Enter username: ";
    getline (cin,inputUser);
    cout << "Enter password: ";
    getline (cin,inputPass);
    }

    if (inputUser == username && inputPass == password) {
        cout << "Login successful!\n";
        return true;
    }

    else {
        attempts--;
        cout << "Invalid username or password.\n"
             << ">> Attempts Left: " << attempts << "\n";
    }

    if (attempts == 0) {
        cout << "Too many failed attempts. Exiting program.\n";
        return false;
    }    
    
    }
int main() {
    cout << "\n\n----- To Do List Application -----\n\n ";
    cout << "1. Create new list\n";
    cout << "2. View existing list\n";
    cout << "3. Edit list\n";
    cout << "4. Exit\n\n";
    cout << "Menu: "
         << ">> ";
         
    int option;
    cin >> option;
    cin.ignore();
}