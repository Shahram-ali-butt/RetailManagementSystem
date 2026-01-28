# Retail Management System
### Advanced POS & Inventory Management System

A comprehensive retail management solution combining Point of Sale (POS) functionality with complete inventory management, built with C++ and featuring modern security implementations.

---

## 📋 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [System Architecture](#system-architecture)
- [Installation](#installation)
- [Quick Start](#quick-start)
- [File Structure](#file-structure)
- [Security Features](#security-features)
- [Technologies Used](#technologies-used)
- [System Requirements](#system-requirements)
- [Default Credentials](#default-credentials)
- [Version History](#version-history)
- [Contributors](#contributors)

---

## 🎯 Overview

The Retail Management System is a feature-rich application designed for small to medium-sized retail businesses. Originally created as a university programming project, it has evolved into a near-production-ready system with professional features including:

- Complete Point of Sale (POS) functionality
- Inventory management with real-time stock tracking
- User authentication with encrypted credentials
- PDF receipt generation
- Admin panel with full CRUD operations
- Notification system for low stock alerts
- Multi-user support with role-based access

**Created By:** Shahram Ali Butt\
**Course:** Programming Fundamentals  
**Institution:** University of Engineering and Technology, Lahore

---

## ✨ Features

### Core Functionality

#### 1. Point of Sale (POS) System
- **Multi-product Orders**: Add unlimited products to a single order
- **Real-time Stock Checking**: Automatic stock availability verification
- **Automatic Calculations**: Instant total calculation with each entry
- **Dynamic Stock Management**: Automatic stock updates after each sale
- **Input Validation**: Comprehensive validation at every step
- **Product Search**: Quick product lookup by name or ID
- **Order Editing**: Remove products from cart before finalizing
- **Purchase Confirmation**: Review and confirm before completing sale

#### 2. Receipt Generation
- **Dual Format Receipts**: 
  - Console-based receipt for immediate viewing
  - Professional PDF receipt with HTML formatting
- **Customer Information**: Name and date automatically included
- **Detailed Breakdown**: Itemized list with quantities and prices
- **Cashier Information**: Records which user processed the sale
- **Automatic Storage**: PDF receipts saved with timestamp

#### 3. Inventory Management
- **Product CRUD Operations**:
  - Add new products with ID, name, price, and quantity
  - Update existing product information
  - Remove discontinued products
  - Add stock to existing products
- **Stock Monitoring**: Visual table display with formatted columns
- **Low Stock Alerts**: Automatic notifications when stock falls below threshold
- **Data Validation**: Maximum width constraints for data integrity
- **Duplicate Prevention**: Checks for existing products before adding

#### 4. User Management

##### User Authentication
- **Secure Login System**: Username and password authentication
- **Password Encryption**: 
  - User passwords hashed for security
  - Admin password double-hashed for extra protection
  - Usernames encrypted using Affine cipher
- **Sign Up Requests**: New users request access, admin approves
- **Multiple User Support**: Up to 5 concurrent users
- **Session Tracking**: Records which user performs each transaction

##### Admin Panel
- **Full User CRUD**: Add, edit, list, and delete users
- **Product Management**: Complete control over inventory
- **Sign Up Approval**: Review and approve/reject new user requests
- **Password Management**: Change admin password securely
- **Stock Management**: Add stock quantities to products

#### 5. Notification System
- **Real-time Alerts**: Dynamic notification pane on screen
- **Low Stock Warnings**: Alerts when products reach critical levels (≤2 units)
- **Sign Up Notifications**: Shows pending user registration requests
- **Color-coded Alerts**: Different colors for different notification types
- **Non-intrusive Display**: Notifications shown without blocking workflow

#### 6. Advanced Features
- **Modular Programming**: Clean code organization with header files
- **File Persistence**: All data stored and retrieved from files
- **Color Output**: Color-coded interface for better UX
- **ASCII Art Header**: Professional branding on startup
- **Hidden Password Input**: Secure password entry with asterisks
- **Cursor Positioning**: Advanced console manipulation for UI
- **Error Handling**: Comprehensive input validation and error recovery

---

## 🏗️ System Architecture

### Modular Design

The system follows a modular architecture with clear separation of concerns:

```
Retail Management System
│
├── User Interface Layer
│   ├── Welcome Screen
│   ├── Login/Signup Interface
│   ├── POS Menu
│   └── Admin Panel
│
├── Business Logic Layer
│   ├── Sales Processing
│   ├── Inventory Management
│   ├── User Management
│   └── Authentication
│
├── Data Layer
│   ├── File Handling
│   ├── Encryption/Decryption
│   └── Data Validation
│
└── Utility Layer
    ├── Receipt Generation
    ├── PDF Conversion
    └── Console Utilities
```

### Key Components

1. **Main Controller** (`main.cpp`): Entry point and main program flow
2. **File Handling** (`fileHandling.h/cpp`): Data persistence operations
3. **Cryptography** (`crypto_functions.h/cpp`): Security and encryption
4. **HTML Generation** (`convertingToHtml.h/cpp`): Receipt HTML creation
5. **PDF Conversion** (`convertingHtmlToPDF.h/cpp`): PDF generation wrapper

---

## 🚀 Installation

### Prerequisites

Before installing, ensure you have:

1. **C++ Compiler**: GCC/MinGW with C++17 support or later
2. **Bash Shell**: 
   - Linux/Mac: Native bash
   - Windows: Git Bash or WSL (Windows Subsystem for Linux)
3. **wkhtmltopdf**: Required for PDF receipt generation
   - Download from: https://wkhtmltopdf.org/downloads.html
   - Add to system PATH

### Step-by-Step Installation

#### 1. Clone or Download the Project
```bash
git clone <repository-url>
cd RetailManagementSystem
```

Or download and extract the ZIP file.

#### 2. Install wkhtmltopdf

**Windows:**
1. Download installer from https://wkhtmltopdf.org/downloads.html
2. Run installer (choose default installation path)
3. Add to PATH:
   - Right-click "This PC" → Properties → Advanced system settings
   - Environment Variables → System Variables → Path → Edit
   - Add: `C:\Program Files\wkhtmltopdf\bin`

**Linux:**
```bash
sudo apt-get update
sudo apt-get install wkhtmltopdf
```

**Mac:**
```bash
brew install wkhtmltopdf
```

#### 3. Verify Installation

```bash
# Check GCC
g++ --version

# Check wkhtmltopdf
wkhtmltopdf --version

# Check bash (Windows users)
bash --version
```

#### 4. Verify File Structure

Ensure your directory structure looks like this:

```
RetailManagementSystem/
├── src/
│   ├── main.cpp
│   ├── fileHandling.cpp
│   ├── crypto_functions.cpp
│   ├── convertingToHtml.cpp
│   └── convertingHtmlToPDF.cpp
├── include/
│   ├── fileHandling.h
│   ├── crypto_functions.h
│   ├── convertingToHtml.h
│   └── convertingHtmlToPDF.h
├── Login_Info (Decrypted)/
│   ├── admin.txt
│   ├── users.txt
│   └── signUpData.txt
├── data/
│   ├── admin.txt
│   ├── users.txt
│   └── signUpData.txt
│   └── products.txt
├── build.sh
└── README.md
```

---

## 🎮 Quick Start

### Running the Application

#### Method 1: Using Build Script (Recommended)

**Windows (Git Bash/WSL):**
```bash
bash build.sh
```

**Linux/Mac:**
```bash
./build.sh
```

#### Method 2: Manual Compilation

```bash
# Compile
g++ -Iinclude src/*.cpp -o main.exe

# Run
./main.exe
```

### First Time Setup

1. **Launch Application**: Run using one of the methods above
2. **Welcome Screen**: You'll see the ASCII art header and main menu
3. **Choose Option**:
   - Option 1: Sign In (use default credentials below)
   - Option 2: Sign Up (request new account)
   - Option 3: Admin Panel (use admin password)
   - Option 0: Exit

### Default Credentials

**Default User:**
- Username: `Shahram`
- Password: `1234`

**Admin Access:**
- Password: `12345`
- (No username required for admin)

**Note:** The system comes pre-loaded with additional demo users and signup requests for testing purposes. All credentials are stored encrypted in `Login_Info/` folder.

---

## 📁 File Structure

```
RetailManagementSystem/
│
├── src/                          # Source files
│   ├── main.cpp                  # Main program entry point
│   ├── fileHandling.cpp          # File I/O operations
│   ├── crypto_functions.cpp      # Encryption/hashing functions
│   ├── convertingToHtml.cpp      # HTML receipt generation
│   └── convertingHtmlToPDF.cpp   # PDF conversion wrapper
│
├── include/                      # Header files
│   ├── fileHandling.h
│   ├── crypto_functions.h
│   ├── convertingToHtml.h
│   └── convertingHtmlToPDF.h
│
├── Login_Info/ (Decrypted)       # Login data (delete after reading)
│   ├── admin.txt                 # Admin password
│   ├── users.txt                 # User credentials
│   └── signUpData.txt            # Signup requests data
│
├── data/                         # In use & encripted data
|   |── admin.txt                 # Admin password (double-hashed)
│   ├── users.txt                 # User credentials (encrypted)
│   └── signUpData.txt            # Pending signup requests (encrypted)
│   └── products.txt              # Product inventory (plain text)
│
├── receipts/                     # Generated receipts (created at runtime)
│   └── receipt_YYYYMMDD_HHMMSS.pdf
│
├── build.sh                      # Build script
├── main.exe                      # Compiled executable (after build)
├── README.md                     # This file
└── UserGuide.md                  # Detailed user guide
```

### Data File Formats

#### users.txt
```
<number_of_users>
<encrypted_username>,<hashed_password>
<encrypted_username>,<hashed_password>
...
```

#### products.txt
```
<number_of_products>
<product_id>,<product_name>,<price>,<quantity_in_stock>
<product_id>,<product_name>,<price>,<quantity_in_stock>
...
```

#### signUpData.txt
```
<number_of_requests>
<encrypted_username>,<hashed_password>
<encrypted_username>,<hashed_password>
...
```

---

## 🔐 Security Features

### Password Protection
1. **User Passwords**: Hashed using custom hash function before storage
2. **Admin Password**: Double-hashed for enhanced security
3. **Hidden Input**: Passwords displayed as asterisks during entry
4. **No Plain Text**: Passwords never stored in readable format

### Username Encryption
- **Affine Cipher Encryption**: Usernames encrypted using mathematical cipher
- **Different Keys**: 
  - Regular users: Affine cipher with keys (a=5, b=8)
  - Signup requests: Affine cipher with keys (a=9, b=15)
- **Space Handling**: Spaces in usernames converted to 'X' before encryption

### Mathematical Foundation
- **Modular Arithmetic**: Base of Affine cipher
- **Hash Functions**: Custom implementation using polynomial rolling hash
- **Coprime Keys**: Ensures reversibility of Affine cipher
- **GCD Validation**: Verifies encryption key validity

---

## 💻 Technologies Used

### Programming Languages & Tools
- **C++17**: Main programming language
- **Bash**: Build script automation

### Libraries & Headers
- **iostream**: Standard input/output
- **iomanip**: Formatted output for tables
- **conio.h**: Password hiding functionality
- **windows.h**: Console colors, cursor positioning
- **limits**: Input buffer management
- **string**: String operations
- **ctime**: Date/time formatting

### External Tools
- **wkhtmltopdf**: HTML to PDF conversion
- **GCC/MinGW**: C++ compiler

### Development Practices
- **Modular Programming**: Separation of concerns
- **Header Files**: Clean code organization
- **File Persistence**: Data storage and retrieval
- **Input Validation**: Error prevention
- **Encryption**: Security implementation

---

## 🖥️ System Requirements

### Minimum Requirements
- **Operating System**: Windows 7 or later (primary), Linux, macOS (with modifications)
- **Processor**: 1 GHz or faster
- **RAM**: 512 MB minimum, 1 GB recommended
- **Storage**: 50 MB free space
- **Display**: Console/Terminal window

### Software Requirements
- **C++ Compiler**: GCC/MinGW (C++17 or later)
- **Bash Shell**: 
  - Windows: Git Bash or WSL
  - Linux/Mac: Built-in
- **wkhtmltopdf**: Latest version

### Platform-Specific Notes

**Windows:**
- Primary development platform
- Fully tested and supported
- Uses Windows.h for console features

**Linux/Mac:**
- Requires modification for platform-specific features
- Replace `windows.h` and `conio.h` dependencies
- PDF generation works natively

---

## 📊 Version History

### v8.0 (Current) - Advanced User Management
- Added complete user management functionality (CRUD)
- Separate "Product Management Panel" in admin section
- Enhanced admin interface organization

### v7.0 - Security Implementation
- Implemented username and password encryption
- Affine cipher with different keys for different data types
- Password hashing for all users
- Double-hashed admin password

### v6.0 - File Persistence
- Made all arrays and variables local
- Pass-by-reference for functions
- Complete file handling implementation
- Products, users, and signup data stored in files
- Added ASCII art header

### v5.0 - Notifications & Receipt Improvements
- Notification pane for low stock alerts
- Sign-up request notifications
- Console receipt generation
- Purchase confirmation before order completion
- Improved color output logic
- Cursor position storage utility

### v4.0 - Receipt Generation
- HTML receipt generation
- PDF conversion functionality
- Customer name storage
- CSR can remove products at sale end
- Receipt data structure implementation

### v3.0 - User System
- Sign in and sign up functionality
- Default user implementation
- Product search feature
- Color output for better UX

### v2.0 - Admin Features
- Admin panel implementation
- Password authentication with hidden input
- CRUD operations on products
- Improved stock table formatting
- Data width validation
- Input validation at all steps

### v1.0 - Core System
- Multi-product order entry
- Stock checking
- Automatic bill calculation
- Stock management
- Product availability checking
- Basic input validation

---

## 👨‍💻 Contributors

**Shahram Ali Butt**
- Session: Fall'25 Morning
- Section: A, Semester: 1st
- Email: shahramalibutt@gmail.com

**Institution:**  
University of Engineering and Technology, Lahore  
Department of Computer Science

**Course:** Programming Fundamentals  
**Instructor:** Maida Shahid & Kamran Mustafa

---

## 📝 License

This project was created as an educational assignment for the Programming Fundamentals course at UET Lahore. 

---

## 📞 Support

For issues, questions, or suggestions:
1. Check the [User Guide](UserGuide.md) for detailed instructions
2. Review the troubleshooting section in the User Guide
3. Contact: shahramalibutt@gmail.com

---

**Version:** 8.0  

---

*Built with ❤️ at UET Lahore*
