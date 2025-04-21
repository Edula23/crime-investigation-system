#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct Suspect {
    int id;
    string name;
    string alias;
    string crime;
    string description;
};

void addSuspect() {
    ofstream file("suspects.txt", ios::app);
    if (!file) {
        cout << "Error opening suspects.txt for writing.\n";
        return;
    }

    Suspect s;

    cout << "\n--- Add New Suspect ---\n";
    cout << "ID: ";
    cin >> s.id;
    cin.ignore();

    cout << "Name: ";
    getline(cin, s.name);

    cout << "Alias: ";
    getline(cin, s.alias);

    cout << "Crime Committed: ";
    getline(cin, s.crime);

    cout << "Description: ";
    getline(cin, s.description);

    file << s.id << "," << s.name << "," << s.alias << "," << s.crime << "," << s.description << endl;
    file.close();

    cout << "Suspect saved.\n";
}

void viewAllSuspects() {
    ifstream file("suspects.txt");
    if (!file) {
        cout << "No suspect records found.\n";
        return;
    }

    string line;
    cout << "\n--- All Suspects ---\n";
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        int fieldCount = 0;

        while (getline(ss, token, ',')) {
            switch (fieldCount) {
                case 0: cout << "ID: " << token << endl; break;
                case 1: cout << "Name: " << token << endl; break;
                case 2: cout << "Alias: " << token << endl; break;
                case 3: cout << "Crime: " << token << endl; break;
                case 4: cout << "Description: " << token << endl; break;
            }
            fieldCount++;
        }
        cout << "---------------------\n";
    }

    file.close();
}

void suspectMenu() {
    int choice;
    do {
        cout << "\n--- Suspect Management ---\n";
        cout << "1. Add Suspect\n";
        cout << "2. View All Suspects\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addSuspect(); break;
            case 2: viewAllSuspects(); break;
            case 0: break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}