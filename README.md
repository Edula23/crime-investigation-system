# Crime Investigation and Case Management System


This is our group project for Fundamentals of Programming II. We're building a command-line based crime investigation and case management system in C++, using MySQL for the database (as proposed). 

# Overview

The Crime Investigation and Case Management System is a C++ application designed to streamline the management of crime cases within law enforcement agencies. This system provides a centralized platform for storing and managing crime-related data, facilitating task assignment, progress monitoring, and inter-departmental coordination.It enables users to report crimes, monitor their status, and facilitate investigations through a user-friendly interface backed by a MySQL database.By digitizing case records, this system addresses the challenges of traditional paper-based methods, ensuring secure and organized access to critical crime data.




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

**User Authentication:** Provides a secure login mechanism for authorized personnel, ensuring that sensitive information is protected.

**Comprehensive Case Management:** Users can create, update, and monitor cases with extensive details, facilitating thorough investigations.

**Witness and Victim Statements:** Efficiently manage and store statements from witnesses and victims, which are crucial for case development.

**Evidence Management:** Record, track, and manage evidence linked to each case, ensuring that all pertinent information is organized and accessible.

**Dynamic Case Status Updates:** Users can easily update the status of cases (e.g., open, closed, under investigation), allowing for better tracking of case progress.

**Centralized Database:** Utilizes MySQL for secure, scalable, and high-performance data storage, ensuring that all case-related information is stored in one location.

**Reporting Capabilities:** Generate detailed reports for case summaries and statistical analysis, aiding in decision-making and resource allocation.

**User -Friendly Interface:** Designed with an intuitive interface that simplifies navigation and enhances user experience, making it easy for personnel to access the information they need quickly.



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
