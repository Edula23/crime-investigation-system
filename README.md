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

    **Important:** Replace `"your_root_password"` with your actual MySQL root password or the password of the user you intend to use.
