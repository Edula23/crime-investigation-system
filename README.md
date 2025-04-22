# Crime Investigation and Case Management System


This is our group project for Fundamentals of Programming II. We're building a command-line based crime investigation and case management system in C++, using MySQL for the database (as proposed). Below is just a rough plan for organizing the work and making sure everything matches our original proposal.



Project Structure (basic idea, subject to change)

- main.cpp               --> menu, navigation, integration
- db_connection.cpp/.h   --> handles MySQL connection
- user_module.cpp/.h     --> login + role-based access (admin/investigator/officer)
- case_module.cpp/.h     --> creating/tracking case files
- suspect_module.cpp/.h  --> add/search suspect info
- evidence_module.cpp/.h --> upload/store reference to digital evidence
- notification_module.cpp/.h --> court dates, deadlines, etc.
- report_module.cpp/.h   --> basic reports (text or console output)



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
