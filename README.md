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

