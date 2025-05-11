# Crime Investigation System

This is a simple command-line Crime Investigation System built using C++ and MySQL. It allows authorized users (Investigators and Officers) to manage criminal information and track case statuses.

## Features

* **User Authentication:** Secure login for Investigators and Officers. Default users are created if the `users` table is empty on the first run.
* **Add Criminal Information:** Allows authorized users to add new criminal records, including name, age, gender, crime committed, last known location, case status (Open/Closed), and witness records.
* **Show Criminals:** Displays a list of all recorded criminals with their details, including a truncated witness record for better readability.
* **Search Cases by Status:** Enables users to search for criminal cases based on their status (Open or Closed).
* **Update Case Status:** Allows users to modify the case status (Open/Closed) for a specific criminal record using their ID.
