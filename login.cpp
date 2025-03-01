
#include <iostream>
#include <fstream>
#include <json/json.h>
#include "storage.h"

using namespace std;

void login() {
    string username, password;
    cout << "Enter Your username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (authenticateUser(username, password)) {
        cout << "Login successful!" << endl;
    } else {
        cout << "Invalid credentials." << endl;
    }
}

void registerUser() {
    string username, password;
    cout << "Enter Your username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (storeUser(username, password)) {
        cout << "Registration successful!" << endl;
    } else {
        cout << "User already exists!" << endl;
    }
}

int main() {
    int choice;
    cout << "1. Login\n2. Register\nChoose: ";
    cin >> choice;

    if (choice == 1) login();
    else if (choice == 2) registerUser();
    else cout << "Invalid choice." << endl;

    return 0;
}
