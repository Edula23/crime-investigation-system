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

// Function prototypes


int main() 
{
    
    //to check that the suspect module works
    suspectMenu();
   
    return 0;
}


