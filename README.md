# CrimeAssist: An Anonymous Crime Evidence and Case Management System

## 📌 About the Project

**CrimeAssist** is a console-based crime evidence and case management system developed using **C++ and Object-Oriented Programming (OOP)**. The main purpose of this project is to provide a structured system for anonymously submitting crime reports, managing digital evidence, verifying cases, and monitoring case-related activities.

The system is designed to simplify the process of crime reporting and case management by providing separate modules for **Users, Officers, and Administrators**.

## 🎯 Objectives

* To provide a platform for anonymous crime reporting.
* To allow users to submit digital crime evidence.
* To provide a systematic case verification and management process.
* To enable officers to review and manage submitted cases.
* To allow administrators to monitor officers, cases, and user reviews.
* To demonstrate the practical implementation of C++ OOP concepts.

## ⚙️ Main Modules

### 👤 User Module

* Submit crime reports anonymously.
* Submit digital evidence.
* Track submitted cases.
* View case decisions.
* Review officer decisions.

### 👮 Officer Module

* View case statistics.
* Review cases waiting for verification.
* Verify submitted crime reports and evidence.
* Update case status.
* Post new cases.

### 🛡️ Admin Module

* Manage officers.
* Review officer decisions.
* Monitor user reviews.
* View case statistics.
* Manage and monitor overall case activities.

## 🔄 System Workflow

```text
User Submits Report
        ↓
Waiting for Verification
        ↓
Officer Reviews and Verifies
        ↓
    ┌───────────────┐
    │               │
    ↓               ↓
 Ongoing         Rejected
    ↓
Case Investigation
    ↓
Case Closed
    ↓
User Reviews Decision
    ↓
Admin Monitors Reviews
```

## 🛠️ Technologies Used

* **Programming Language:** C++
* **Programming Concept:** Object-Oriented Programming (OOP)
* **Application Type:** Console-Based Application
* **Development Environment:** VS Code / Any C++ IDE
* **Compiler:** GCC / MinGW

## 📂 Project Structure

```text
CrimeAssist/
│
├── Source Code/
├── Documentation/
├── Flowchart/
├── Project Report/
└── README.md
```

## 👥 Group Members

This project was developed as a *3-member group project* by:
1. *Bikita Baskota*
2. *Prince Sah*
3. *Sabak Koirala*

## 🎓 Academic Project

This project was developed as part of the *BCA 2nd Semester* academic project.

## 📜 Project Purpose

CrimeAssist is developed for educational and academic purposes to demonstrate how *Object-Oriented Programming concepts in C++* can be applied to develop a real-world-inspired crime evidence and case management system.

## 🚀 Future Enhancements

* Development of a web-based version.
* Integration with a secure database.
* Improved digital evidence storage.
* User authentication and authorization.
* Advanced case tracking and notification features.
* Enhanced security and data protection mechanisms.