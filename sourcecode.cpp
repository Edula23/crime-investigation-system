#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include "suspect_module.h"
using namespace std;

// Structures to represent a case
struct Case {
    string case_ID;            // Case number
    string description;        // Description of the case
    string status;             // Current status of the case (e.g., open, closed)
    string date_reported;      // Date when the case was reported
    string assigned_officer;   // Officer assigned to the case
    string department;         // Department handling the case
    string progress;           // Progress of the case
};

// Function prototypes


int main() 
{
    
    //to check that the suspect module works
    suspectMenu();
   
    return 0;
}


