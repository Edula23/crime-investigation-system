#include <iostream>
#include <stdexcept>
#include <memory>
#include <iomanip>
#include <string>

// MySQL Connector/C++ specific headers
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

using namespace std;

// Database connection parameters 
const string DB_HOST = "tcp://127.0.0.1:3306";
const string DB_USER = "root";
const string DB_PASS = "and324292and";  //MySQL root password
const string DB_NAME = "crime_investigation";


// Function declarations
void initializeDatabase(sql::Connection* con);
bool authenticateUser(sql::Connection* con, string& username, string& role);
void addCriminalInfo(sql::Connection* con);
void showCriminals(sql::Connection* con);
void searchCases(sql::Connection* con);
void updateCaseStatus(sql::Connection* con);

int main() {
    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance(); 
        unique_ptr<sql::Connection> con(driver->connect(DB_HOST, DB_USER, DB_PASS)); // Create a unique pointer to a MySQL connection
        // Create and select database
        unique_ptr<sql::Statement> stmt(con->createStatement()); // Create a statement object for executing SQL queries
        stmt->execute("CREATE DATABASE IF NOT EXISTS " + DB_NAME); // Create the database if it does not exist
        stmt->execute("USE " + DB_NAME); 
        cout << "Crime Investigation System\n"; 
        cout << "--------------------------\n"; 
       
        initializeDatabase(con.get()); 
        string username, role; 
        bool loggedIn = false; 
        
        
        while (!loggedIn) { 
            cout << "\nPlease log in.\nUsername: "; 
            getline(cin, username); 
            cout << "Password: "; 
            string password; 
            getline(cin, password); 
           
            if (authenticateUser (con.get(), username, role)) { 
                cout << "Login successful as " << role << ": " << username << "\n"; 
                loggedIn = true; 
            } else {
                cout << "Authentication failed. Please try again.\n"; 
            }
        }


// Main menu loop
        while (true) { 
            cout << "\nMenu Options:\n"; 
            cout << "1. Add Criminal Information\n"; 
            cout << "2. Show Criminals\n";
            cout << "3. Search Cases (by status)\n";
            cout << "4. Update Case Status\n"; 
            cout << "5. Exit\n"; 
            cout << "Enter choice: "; 
            string choiceStr; 
            getline(cin, choiceStr); 
            int choice = 0; 
            try {
                choice = stoi(choiceStr); 
            } catch (...) {                     // Catch any exceptions during conversion
                cout << "Invalid input, please enter a number.\n"; 
                continue; 
            }

switch (choice) { 
            case 1: 
                addCriminalInfo(con.get()); 
                break;
            case 2: 
                showCriminals(con.get()); 
                break; 
            case 3: 
                searchCases(con.get()); 
                break; 
            case 4:
                updateCaseStatus(con.get()); 
                break; 
            case 5: 
                cout << "Exiting system. Goodbye!\n"; 
                return 0; 
            default: 
                cout << "Invalid option. Please choose again.\n"; 
            }
        }
    }

        catch (sql::SQLException& e) {            // Catch SQL exceptions
        cerr << "SQL error: " << e.what() << "\n"; // Print SQL error message
        cerr << "MySQL error code: " << e.getErrorCode() << "\n"; // Print MySQL error code
        cerr << "SQLState: " << e.getSQLState() << "\n"; 
        return EXIT_FAILURE; 
    }
    catch (exception& e) { // Catch general exceptions
        cerr << "Error: " << e.what() << "\n"; 
        return EXIT_FAILURE; 
    }
}

// Function to initialize the database




