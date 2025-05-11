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

void initializeDatabase(sql::Connection* con) {     // Function to initialize the database
    unique_ptr<sql::Statement> stmt(con->createStatement());
// Users table for authentication: username (PK), password, role
    stmt->execute(
        "CREATE TABLE IF NOT EXISTS users ("
        " username VARCHAR(50) PRIMARY KEY,"
        " password VARCHAR(255) NOT NULL,"
        " role ENUM('Investigator','Officer') NOT NULL"
        ")"
    );

    // Insert default users if table empty
    unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT COUNT(*) as count FROM users"));
    res->next();
    if (res->getInt("count") == 0) {
        cout << "Creating default users...\n";
        // WARNING: In production, passwords must be hashed!
        stmt->execute("INSERT INTO users(username,password,role) VALUES "
            "('investigator1','password123','Investigator'),"
            "('officer1','password123','Officer')");
        cout << "Default users created: investigator1 / officer1 with password 'password123'.\n";
    }

    // Criminals table setup, drop cases table if any residual
    stmt->execute("DROP TABLE IF EXISTS cases");

    // Check if criminals table exists
    unique_ptr<sql::ResultSet> tableCheck(stmt->executeQuery("SHOW TABLES LIKE 'criminals'"));
    if (!tableCheck->next()) {
        // Table doesn't exist, create with witness_record and case_status columns, without the status column
        stmt->execute(
            "CREATE TABLE criminals ("
            " id INT AUTO_INCREMENT PRIMARY KEY,"
            " name VARCHAR(100) NOT NULL,"
            " age INT,"
            " gender ENUM('Male','Female','Other'),"
            " crime VARCHAR(255) NOT NULL,"
            " last_known_location VARCHAR(255),"
            " case_status ENUM('Open','Closed') DEFAULT 'Open',"
            " witness_record TEXT"
            ")"
        );
    }
    else {
        // Table exists, check if status column exists; if yes, drop it
        unique_ptr<sql::ResultSet> colCheckStatus(stmt->executeQuery("SHOW COLUMNS FROM criminals LIKE 'status'"));
        if (colCheckStatus->next()) {
            try {
                stmt->execute("ALTER TABLE criminals DROP COLUMN status");
                cout << "Dropped 'status' column from criminals table.\n";
            }
            catch (sql::SQLException& e) {
                cout << "Failed to drop 'status' column: " << e.what() << "\n";
            }
        }
        // Check if case_status column exists
        unique_ptr<sql::ResultSet> colCheckCaseStatus(stmt->executeQuery("SHOW COLUMNS FROM criminals LIKE 'case_status'"));
        if (!colCheckCaseStatus->next()) {
            stmt->execute(
                "ALTER TABLE criminals "
                "ADD COLUMN case_status ENUM('Open','Closed') DEFAULT 'Open'"
            );
        }
        // Check if witness_record column exists
        unique_ptr<sql::ResultSet> colCheckWitness(stmt->executeQuery("SHOW COLUMNS FROM criminals LIKE 'witness_record'"));
        if (!colCheckWitness->next()) {
            stmt->execute(
                "ALTER TABLE criminals "
                "ADD COLUMN witness_record TEXT"
            );
        }
    }
}

bool authenticateUser(sql::Connection* con, string& username, string& role) {
    // User inputs username and password, verify against users table
    cout << "(Authentication) Enter password: ";
    string password;
    getline(cin, password);

    unique_ptr<sql::PreparedStatement> pstmt(
        con->prepareStatement("SELECT role FROM users WHERE username = ? AND password = ?")
    );
    pstmt->setString(1, username);
    pstmt->setString(2, password);
    unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

    if (res->next()) {
        role = res->getString("role");
        return true;
    }
    return false;
}

void addCriminalInfo(sql::Connection* con) {
    cout << "\n--- Add Criminal Information ---\n";
    string name, gender, crime, location, witnessRecord;
    int age;
    string caseStatus;

    cout << "Enter full name: ";
    getline(cin, name);
    cout << "Enter age: ";
    string ageStr; getline(cin, ageStr);
    try {
        age = stoi(ageStr);
    }
    catch (...) {
        cout << "Invalid input for age. Setting age to 0.\n";
        age = 0;
    }
    cout << "Enter gender (Male/Female/Other): ";
    getline(cin, gender);
    cout << "Enter crime committed: ";
    getline(cin, crime);
    cout << "Enter last known location: ";
    getline(cin, location);
    cout << "Enter case status (Open/Closed) [default: Open]: ";
    getline(cin, caseStatus);
    if (caseStatus != "Open" && caseStatus != "Closed") {
        caseStatus = "Open";
    }
    cout << "Enter witness record (if any, else leave blank): ";
    getline(cin, witnessRecord);

    unique_ptr<sql::PreparedStatement> pstmt(
        con->prepareStatement("INSERT INTO criminals(name, age, gender, crime, last_known_location, case_status, witness_record) VALUES (?, ?, ?, ?, ?, ?, ?)")
    );
    pstmt->setString(1, name);
    pstmt->setInt(2, age);
    pstmt->setString(3, gender);
    pstmt->setString(4, crime);
    pstmt->setString(5, location);
    pstmt->setString(6, caseStatus);
    pstmt->setString(7, witnessRecord);

    int updateCount = pstmt->executeUpdate();
    if (updateCount > 0) {
        cout << "Criminal information added successfully.\n";
    }
    else {
        cout << "Failed to add criminal information.\n";
    }
}

void showCriminals(sql::Connection* con) {
    cout << "\n--- Recorded Criminals ---\n";
    unique_ptr<sql::Statement> stmt(con->createStatement());
    unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT id, name, age, gender, crime, last_known_location, case_status, witness_record FROM criminals"));

    cout << left << setw(5) << "ID"
        << setw(25) << "Name"
        << setw(5) << "Age"
        << setw(8) << "Gender"
        << setw(30) << "Crime"
        << setw(25) << "Last Known Location"
        << setw(12) << "Case Status"
        << setw(40) << "Witness Record" << "\n";

    cout << string(140, '-') << "\n";

    while (res->next()) {
        string witnessRec = res->getString("witness_record");
        // Truncate witness record for display if too long
        if (witnessRec.length() > 37) {
            witnessRec = witnessRec.substr(0, 34) + "...";
        }

        cout << setw(5) << res->getInt("id")
            << setw(25) << res->getString("name")
            << setw(5) << res->getInt("age")
            << setw(8) << res->getString("gender")
            << setw(30) << res->getString("crime")
            << setw(25) << res->getString("last_known_location")
            << setw(12) << res->getString("case_status")
            << setw(40) << witnessRec << "\n";
    }
}

void searchCases(sql::Connection* con) {
    cout << "\n--- Search Cases by Status ---\n";
    cout << "Enter case status to search (Open/Closed): ";
    string status;
    getline(cin, status);
    if (status != "Open" && status != "Closed") {
        cout << "Invalid case status. Use 'Open' or 'Closed'.\n";
        return;
    }

    unique_ptr<sql::PreparedStatement> pstmt(
        con->prepareStatement("SELECT id, name, age, gender, crime, last_known_location, case_status, witness_record FROM criminals WHERE case_status = ?")
    );
    pstmt->setString(1, status);

    unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

    cout << left << setw(5) << "ID"
        << setw(25) << "Name"
        << setw(5) << "Age"
        << setw(8) << "Gender"
        << setw(30) << "Crime"
        << setw(25) << "Last Known Location"
        << setw(12) << "Case Status"
        << setw(40) << "Witness Record" << "\n";

    cout << string(140, '-') << "\n";
bool found = false;
    while (res->next()) {
        found = true;
        string witnessRec = res->getString("witness_record");
        if (witnessRec.length() > 37) {
            witnessRec = witnessRec.substr(0, 34) + "...";
        }
        cout << setw(5) << res->getInt("id")
            << setw(25) << res->getString("name")
            << setw(5) << res->getInt("age")
            << setw(8) << res->getString("gender")
            << setw(30) << res->getString("crime")
            << setw(25) << res->getString("last_known_location")
            << setw(12) << res->getString("case_status")
            << setw(40) << witnessRec << "\n";
    }
    if (!found) {
        cout << "No cases found with status '" << status << "'.\n";
    }
}
void updateCaseStatus(sql::Connection* con) {
    cout << "\n--- Update Case Status ---\n";
    cout << "Enter Criminal ID to update case status: ";
    string criminalIdStr;
    getline(cin, criminalIdStr);
    int criminalId;
    try {
        criminalId = stoi(criminalIdStr);
    }
    catch (...) {
        cout << "Invalid Criminal ID.\n";
        return;
    }
// Check if criminal exists
    unique_ptr<sql::PreparedStatement> checkStmt(
        con->prepareStatement("SELECT id, case_status FROM criminals WHERE id = ?")
    );
    checkStmt->setInt(1, criminalId);
    unique_ptr<sql::ResultSet> res(checkStmt->executeQuery());
    if (!res->next()) {
        cout << "Criminal ID " << criminalId << " not found.\n";
        return;
    }





