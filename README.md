# Crime Investigation and Case Management System


This is our group project for Fundamentals of Programming II. We're building a command-line based crime investigation and case management system in C++, using MySQL for the database (as proposed). 

# Overview

The Crime Investigation and Case Management System is a C++ application designed to streamline the management of crime cases within law enforcement agencies. This system provides a centralized platform for storing and managing crime-related data, facilitating task assignment, progress monitoring, and inter-departmental coordination.It enables users to report crimes, monitor their status, and facilitate investigations through a user-friendly interface backed by a MySQL database.




Project Structure (basic idea, subject to change)

- main.cpp               --> menu, navigation, integration
- db_connection.cpp/.h   --> handles MySQL connection
- user_module.cpp/.h     --> login + role-based access (admin/investigator/officer)
- case_module.cpp/.h     --> creating/tracking case files
- suspect_module.cpp/.h  --> add/search suspect info
- evidence_module.cpp/.h --> upload/store reference to digital evidence
- notification_module.cpp/.h --> court dates, deadlines, etc.
- report_module.cpp/.h   --> basic reports (text or console output)


# Features
**Add New Cases**: Users can input details about new crime cases, including case number, description, status, date reported, assigned officer, department, and progress updates.

**View Existing Cases**: Users can retrieve and display all cases stored in the database, providing a comprehensive overview of ongoing and past investigations.

**Update Case Status**: Users can change the status of a specific case (e.g., from "Open" to "Closed") based on its unique case ID, allowing for effective case management.

**Assign Tasks to Officers**: Users can assign specific officers to cases, ensuring accountability and clear task delegation within the department.

**Secure Data Storage**: Utilizes MySQL for high-performance, scalable, and secure data storage, ensuring that sensitive information is handled appropriately.

**User -Friendly Console Interface**: A simple menu-driven console interface allows users to navigate through options easily and perform operations without complex commands.

# Prerequisites

Before running the application, ensure you have the following installed:

**Development Environment:** An IDE or text editor (e.g., Visual Studio, Code::Blocks, or any text editor) for writing and compiling C++ code.

**MySQL Server:** MySQL server installed and running on your machine or accessible remotely.

**MySQL Connector/C++:** The MySQL Connector/C++ library for database connectivity.



Suggested Member Roles (nothing strict, just to get going)

- Member 1 – MySQL connection + user login
- Member 2 – Case tracking and updates
- Member 3 – Suspect data (file management + structs)
- Member 4 – Evidence file handling
- Member 5 – Notifications and alert triggers
- Member 6 – Report generation + witness/victim statement handling

If someone finishes early or needs help, feel free to swap in or pair up. We’ll keep this flexible.



Features To Implement (based 100% on the proposal)

- User login with different roles
- Create and track cases
- Add/search suspect records
- Handle evidence (images, documents – at least by name/path)
- Store witness/victim statements
- Notifications for court dates or deadlines
- Generate simple reports (case summary, open cases, etc.)



Guidelines

- Let’s stick to C++ basics: structs, classes, enums, typedefs, file I/O, functions
- MySQL is allowed, but plain file handling is fine for storing stuff too
- No advanced frameworks or GUIs—just command line
- Better to cover all features simply than add fancy stuff we haven’t learned
- We’ll test modules separately, then link everything through `main.cpp`



Let’s update this file as we go. Open to edits.
