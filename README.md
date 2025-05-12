Group Members
* **Eden Alemayehu - ETS0433/16**
* **Edom Getahun  - ETS0442/16**
* **Eden Mengste - ETS0436/16**
* **Ephratah Girma - ETS0480/16**
* **Enas Atham - ETS0473/16**
  
# Crime Investigation System

This is a simple command-line Crime Investigation System built using C++ and MySQL. It allows authorized users (Investigators and Officers) to manage criminal information and track case statuses.

## Features

* **User Authentication:** Secure login for Investigators and Officers. Default users are created if the `users` table is empty on the first run.
* **Add Criminal Information:** Allows authorized users to add new criminal records, including name, age, gender, crime committed, last known location, case status (Open/Closed), and witness records.
* **Show Criminals:** Displays a list of all recorded criminals with their details, including a truncated witness record for better readability.
* **Search Cases by Status:** Enables users to search for criminal cases based on their status (Open or Closed).
* **Update Case Status:** Allows users to modify the case status (Open/Closed) for a specific criminal record using their ID.
## Prerequisites

* **MySQL Server:** You need a running MySQL server instance.
* **MySQL Connector/C++:** This project relies on the MySQL Connector/C++ library to interact with the MySQL database. Make sure you have it installed and linked correctly in your C++ development environment.

## Setup and Installation

1.  **Install MySQL Connector/C++:** The installation process varies depending on your operating system and development environment. Refer to the official MySQL Connector/C++ documentation for detailed instructions.

2.  **Clone the Repository (Optional):** If you have the source code in a repository, clone it to your local machine.

3.  **Compile the Code:** Use a C++ compiler (like g++) to compile the `main.cpp` file. Make sure to link against the MySQL Connector/C++ library.

    ```bash
    g++ -o crime_system main.cpp -std=c++11 -I/path/to/mysql_connector_cpp/include -L/path/to/mysql_connector_cpp/lib -lmysqlcppconn
    ```

    **Note:** Replace `/path/to/mysql_connector_cpp/include` and `/path/to/mysql_connector_cpp/lib` with the actual paths to your MySQL Connector/C++ installation.

4.  **Configure Database Credentials:** Open the `main.cpp` file and modify the following constants at the beginning of the file to match your MySQL server settings:

    ```cpp
    const string DB_HOST = "tcp://127.0.0.1:3306"; // Your MySQL host and port
    const string DB_USER = "root";             // Your MySQL username
    const string DB_PASS = "your_root_password"; // Your MySQL password
    const string DB_NAME = "crime_investigation"; // The name of the database
    ```
## Running the Application

1.  **Start the MySQL Server:** Ensure your MySQL server is running.

2.  **Execute the Compiled Program:** Run the compiled executable from your terminal:

    ```bash
    ./crime_system
    ```

3.  **Follow the Prompts:** The application will guide you through the login process and the main menu options.

## Default Users

On the first run, if the `users` table is empty, the system will create two default users:

* **Username:** `investigator1`
    **Password:** `password123`
    **Role:** `Investigator`

* **Username:** `officer1`
    **Password:** `password123`
    **Role:** `Officer`

**Warning:** In a production environment, it is crucial to implement proper password hashing for security. The default users provided here use plain text passwords for simplicity.

## Database Structure

The system uses the following tables in the `crime_investigation` database:

* **`users`:** Stores user authentication information.
    * `username` (VARCHAR(50), PRIMARY KEY)
    * `password` (VARCHAR(255), NOT NULL)
    * `role` (ENUM('Investigator','Officer'), NOT NULL)

* **`criminals`:** Stores information about criminals and their cases.
    * `id` (INT AUTO_INCREMENT, PRIMARY KEY)
    * `name` (VARCHAR(100), NOT NULL)
    * `age` (INT)
    * `gender` (ENUM('Male','Female','Other'))
    * `crime` (VARCHAR(255), NOT NULL)
    * `last_known_location` (VARCHAR(255))
    * `case_status` (ENUM('Open','Closed'), DEFAULT 'Open')
    * `witness_record` (TEXT)

## Security Considerations

* **Password Hashing:** The current implementation stores passwords in plain text for the default users. In a real-world application, always use strong password hashing algorithms (e.g., bcrypt, Argon2) to protect user credentials.
* **SQL Injection:** The code uses prepared statements, which helps prevent SQL injection vulnerabilities. However, always be mindful of user input and sanitize it appropriately if dynamic SQL queries are constructed.
* **Access Control:** The basic role-based access control (Investigator/Officer) is implemented. You might need more granular permissions based on the application's requirements.

## Future Enhancements

* **More Sophisticated Search Options:** Implement searching for criminals by name, crime, location, or a combination of criteria.
* **Detailed Case Information:** Create a separate `cases` table to store more detailed information about each crime, linking it to the `criminals` table.
* **User Management:** Add functionality to create, modify, and delete user accounts.
* **Reporting Features:** Implement the ability to generate reports on open/closed cases, types of crimes, etc.
* **GUI Interface:** Develop a graphical user interface for easier interaction.    




