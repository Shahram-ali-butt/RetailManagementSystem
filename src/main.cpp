// Features: 

// --v1 
// Entering multiple products in one order without restrain
// Checking Stock
// Automatically calculates total bill with each entry and price of current product
// Automatically handles Stock of products
// Checks for availability of products
// Validates input and fixes input stream issues

// --v2
// Added an Admin panel
// Password authentication for admin and hidding the input of password
// CRUD funtionality on products (adding, removing, updating products and adding stock)
// Imporoved stock table using std::left and setw() stream manipulators
// Checks for the maximum width of product data allowed to be stored
// Created an utility function for stoping execution of program
// Input Validation at all steps

// --v3
// Sign In and Sign Up functionality
// Default user
// Search function for products
// Color Output

// --v4
// Storing Data for Receipt
// Generating a receipt in HTML
// Converting the HTML receipt to PDF
// Storing Customer's name
// Making CSR able to remove products at the end of sale

// --v5
// Notification pane for low stock and sign up request notifications
// Created a console recipt
// Confirming purchase before closing order 
// Improved Color output logic
// Created a utility function to store current position of cursor

// --v6
// Made all arrays and variables local
// Passed variables to functions by reference
// Added file handling
// Products data, user information, sign up requests are stored and retrieved from filesi
// Added an ASCII art header 

// --v7
// Implemented encription of usernames and passwords
// Used Affine ciphher with different keys to encript usernames and names in new signup data
// Hashed passwords of users and signup data
// Double hashed admin password for enhanced security.

// --v8
// Added User Management functioinality (Full CRUD)
// Created a separate "Product Management Panel"

// ====================================================================================

#include <iostream>
#include <iomanip> // Products table formatting
#include <conio.h> // Hidden password input
#include <windows.h> // Color Output, gotoxy, cursor position
#include <limits> // I used it to clear the input buffer 
#include <string> // Added for string usage
#include <ctime> // Passing formatted date for receipt
#include "convertingHtmlToPDF.h"
#include "convertingToHtml.h"
#include "fileHandling.h"
#include "crypto_functions.h"

using namespace std;

const int maxUsers = 5;

// ======== Logging
void printHeader();
int welcomeScreen();
void checkStock(int inventorySize, int productId[], string productNames[], float prices[], int quantityInStock[], int idWidth, int nameWidth, int priceWidth, int qtyWidth);
void printProductData(int productId, string productName, float productPrice, int quantityInStock, int idWidth, int nameWidth, int priceWidth, int qtyWidth);
void printOrderData(string productName, float productPrice, int quantityInStock, int nameWidth, int priceWidth, int qtyWidth); //--v5

// ======== Signing in and up --v3
bool signInMenu(int currentUsers, string userNames[], string userPasswords[], string &currentUser);
bool signUpMenu(int currentUsers, string signUpRequestData[][2], int &signUpRequests, string userNames[]);

// ======== Backbone
void printPOSMenu(string productNames[], int quantityInStock[], float prices[], float &total, int &orderProductsCount, 
                int inventorySize, int inventoryLimit, string orderProductNames[], int orderProductsQuantity[], float orderPrices[], int orderProductId[], 
                string &customerName, int productId[], int idWidth, int nameWidth, int priceWidth, int qtyWidth, string currentUser, string &formattedDate);
float salesMenu(int productId[], string productNames[], int quantityInStock[], float prices[], float &total, int &orderProductsCount, 
                int inventorySize, int inventoryLimit, string orderProductNames[], int orderProductsQuantity[], float orderPrices[], int orderProductId[], 
                string &customerName, int idWidth, int nameWidth, int qtyWidth, int priceWidth, string currentUser, string &formattedDate);
void chooseProduct(string productNames[], int quantityInStock[], float prices[], float &total, int &orderProductsCount, 
                int inventorySize, int inventoryLimit, string orderProductNames[], int orderProductsQuantity[], float orderPrices[], int orderProductId[]);
void searchProduct(string productNames[], int quantityInStock[], float prices[], int productId[], int inventorySize, int idWidth, int nameWidth, int priceWidth, int qtyWidth); // --v3
void orderRemoveProduct(int &orderProductsCount, string orderProductNames[], int orderProductsQuantity[], float orderPrices[], int orderProductId[],  int idWidth, int nameWidth); // removing product from current order --v4

// ======== Admin panel and related functionality --v2
bool passwordAuth();
void adminPanel(int &inventorySize, int inventoryLimit, int productId[], string productNames[], float prices[], int quantityInStock[], int idWidth, int nameWidth, int priceWidth, int qtyWidth,
                int signUpRequests, string signUpRequestData[][2], int &currentUsers, string userNames[], string userPasswords[], int maxUsers);

void addStock(int inventorySize, int productId[], string productNames[], float prices[], int quantityInStock[], int qtyWidth, int idWidth, int nameWidth, int priceWidth);
void signUpRequest(int &signUpRequests, string signUpRequestData[][2], int &currentUsers, string userNames[], string userPasswords[]); // --v5
void changeAdminPassword();

// Product Management (admin panel)
void manageProducts(int &inventorySize, int inventoryLimit, int productId[], string productNames[], float prices[], int quantityInStock[], int nameWidth, int priceWidth, int qtyWidth);
void addProduct(int &inventorySize, int inventoryLimit, int productId[], string productNames[], float prices[], int quantityInStock[], int nameWidth, int priceWidth, int qtyWidth);
void removeProduct(int &inventorySize, int productId[], string productNames[], float prices[], int quantityInStock[]);
void updateProduct(int inventorySize, int productId[], string productNames[], float prices[], int quantityInStock[], int nameWidth, int priceWidth);

// User Management (admin panel)
void manageUsers(string userNames[], string userPasswords[], int &currentUsers, int maxUsers, int idWidth, int nameWidth);
void listUsers(string userNames[], int currentUsers, int idWidth, int nameWidth);
void addUser(string userNames[], string userPasswords[], int maxUsers, int &currentUsers, int nameWidth);
void editUserInfo(string userNames[], string userPasswords[], int &currentUsers);
void deleteUser(string userNames[], string userPasswords[], int &currentUsers);

// Notification Pane // --v5
void notificationPane(int inventorySize, int quantityInStock[], int productId[], string productNames[], int &signUpRequests, string signUpRequestData[][2]); 
void stockNotification(int &coordX , int &coordY, int inventorySize, int quantityInStock[], int productId[], string productNames[]);
void signUpNotification(int &coordX, int &coordY, int signUpRequests, string signUpRequestData[][2]);

// ======== receipt printing -v4
void updateBill(int productId, string productName, int quantity, float price, int &orderProductsCount, int inventoryLimit, string orderProductNames[], int orderProductsQuantity[], float orderPrices[], int orderProductId[]);
void printBillPDF(float totalAmount, int inventoryLimit, string orderProductNames[], int orderProductsQuantity[], float orderPrices[],
                    int orderProductsCount, string customerName, string userName, string &formattedDate);
void printBillConsole(string customerName, int nameWidth, int qtyWidth, int priceWidth, int orderProductsCount, int total, string orderProductNames[], float orderPrices[], int orderProductsQuantity[]);
bool confirmPurchase(int orderProductsCount, int orderProductId[], int quantityInStock[], int orderProductsQuantity[]);
bool editOrder(int &orderProductsCount, string orderProductNames[], int orderProductsQuantity[], float orderPrices[], int orderProductId[],  int idWidth, int nameWidth);

// ======== Utility Functions
string encriptPassword();
void ValidateInputStream(); // Handling failbit error
void stopExecution();
void stopExecutionWithIgnore();
void gotoxy(int x, int y); // --v5
COORD getCursorPosition(); //--v5
void generateColors(int color); // --v5 
bool checkDataWidth(int dataWidth, string data);
bool productExists(string productName, string productNames[], int inventorySize);


int main(){
    // Date Formatting Logic
    time_t timestamp = time(NULL);
    struct tm datetime = *localtime(&timestamp);
    char output[50];
    strftime(output, 50, "%B %e, %Y", &datetime); 
    string formattedDate; // Formated date for receipt
    string formattedDateStr(output);
    formattedDate = formattedDateStr;
 
// --------------- Variables, arrays and constants -----------------------------------------    

    // Users -v3
    int currentUsers = 1;
    string userNames[maxUsers] = {};
    string userPasswords[maxUsers] = {};

    string currentUser; //Current urser operating app
    string customerName = " "; //Current customer

    // SignUp Requests Data
    string signUpRequestData[maxUsers][2] = {};
    int signUpRequests = 0;

    // Products Sold by the shop (now as arrays) --v2
    int inventorySize = 4;
    const int inventoryLimit = 20;

    int idWidth = 15; //Maximum sizes of product data allowed (important for logging)
    int nameWidth = 30;
    int priceWidth = 15;
    int qtyWidth = 10;

    string productNames[inventoryLimit] = {};
    int productId[inventoryLimit] = {};
    float prices[inventoryLimit] = {};
    int quantityInStock[inventoryLimit] = {};

    // Data for receipt --v4
    string orderProductNames[inventoryLimit] = {};
    int orderProductId[inventoryLimit] = {};
    float orderPrices[inventoryLimit] = {};
    int orderProductsQuantity[inventoryLimit] = {};
    int orderProductsCount = 0;

    float total = 0; // Total price of one order

// --------------------------------------------------------

    // Begining of program
    generateColors(6);

    // Load Data from files
    loadProductRecords(inventorySize, productNames, productId, prices, quantityInStock);
    loadUserDataDec(currentUsers, userNames, userPasswords);
    loadSignUpDataDec(signUpRequests, signUpRequestData);

    while(true){

        printHeader();

        int signInOption = welcomeScreen();
        ValidateInputStream();

        if(signInOption == 1){
            if(signInMenu(currentUsers, userNames, userPasswords, currentUser)){
                cout << "Sign In Successful! You will be directed to POS Menu" << endl;
                stopExecution();
                printPOSMenu(productNames, quantityInStock, prices, total, 
                 orderProductsCount, inventorySize, inventoryLimit, orderProductNames, orderProductsQuantity, orderPrices, 
                 orderProductId, customerName, productId, idWidth, nameWidth, priceWidth, qtyWidth, currentUser, formattedDate);
            }else{
                cout << "Sign In Unsuccessful!" << endl;
                stopExecution();
                continue;
            }
        }
        else if(signInOption == 2){
            if(signUpMenu(currentUsers, signUpRequestData, signUpRequests, userNames)){
                cout << "Sign Up Request sent!" << endl;
                cout << "If the admin allows you would be able to sign in" << endl;
                storeSignUpDataEnc(signUpRequests, signUpRequestData);
            }
            stopExecution();
            continue;
        }
        else if(signInOption == 3){
            system("cls");
            if(!passwordAuth()){
                cout << "Access denied!" << endl;
                stopExecution();
                continue;
            }
            adminPanel(inventorySize, inventoryLimit, productId, productNames, prices, quantityInStock, 
                idWidth, nameWidth, priceWidth, qtyWidth, signUpRequests, signUpRequestData, currentUsers, userNames, userPasswords, maxUsers);
        }
        else if(signInOption == 4){ // Exit option 4
            break;
        }
        else{
            cout << "Invalid Option" << endl;
            stopExecution();
        }
    }

    return 0;
}


// ======== Billing

void updateBill(int productId, string productName, int quantity, float price, int &orderProductsCount, 
                int inventoryLimit, string orderProductNames[], int orderProductsQuantity[], float orderPrices[], int orderProductId[]){
    int existingProductIdx = -1;

    if(orderProductsCount >= inventoryLimit){
        cout << "Maximum limit for order reached!";
        return;
    }

    for (int i = 0; i < orderProductsCount; i++){
        if (productName == orderProductNames[i]){
            existingProductIdx = i;
            break;
        }
    }

    if (existingProductIdx != -1){
        orderProductsQuantity[existingProductIdx] += quantity;
         orderPrices[existingProductIdx] += price;
    }else{
        orderProductNames[orderProductsCount] = productName;
        orderProductId[orderProductsCount] = productId;
        orderProductsQuantity[orderProductsCount] = quantity;
        orderPrices[orderProductsCount] = price;
        orderProductsCount++;
    }
}

void printBillPDF(float totalAmount, int inventoryLimit, string orderProductNames[], int orderProductsQuantity[], float orderPrices[],
    int orderProductsCount, string customerName, string userName, string &formattedDate){
    char choice;
    cout << "Do you want to print recipt (y/n): ";
    cin >> choice;

    if(choice == 'y' || choice == 'Y'){
        const string HTML_FILE = "receipt_temp.html";
        const string PDF_FILE = "receipt_" + to_string((int)time(0)) + ".pdf"; // Unique filename
    
        // 1. Generate the HTML content string
        string receiptHtml = generateHtmlReceipt(totalAmount, inventoryLimit, orderProductNames, orderProductsQuantity, 
            orderPrices, orderProductsCount, customerName, userName, formattedDate);
    
        // 2. Write the string to a temporary HTML file
        writeHtmlFile(HTML_FILE, receiptHtml);
    
        // 3. Convert the HTML file to PDF
        printBillToPdf(HTML_FILE, PDF_FILE);
    
        // Optional: Clean up the temporary HTML file
        // remove(HTML_FILE.c_str()); 
    }
}

void printBillConsole(string customerName, int nameWidth, int qtyWidth, int priceWidth, int orderProductsCount, int total, string orderProductNames[], float orderPrices[], int orderProductsQuantity[]){
    cout << endl << "**** Receipt" << endl;
    cout << endl << "Customer name: " << customerName << endl;
    cout << "***********************************************************" << endl;
    cout  << std::left << setw(nameWidth) << "Product name"
    << std::left << setw(qtyWidth) << "Quantity "
    << std::left << setw(priceWidth) << "Price" << endl;
    cout << "***********************************************************" << endl;
    for(int i = 0; i < orderProductsCount; i++){
        printOrderData(orderProductNames[i], orderPrices[i], orderProductsQuantity[i], nameWidth, priceWidth, qtyWidth);
    }
    cout << "***********************************************************" << endl;
    cout << "Total: $" << total << endl;
    cout << "***********************************************************" << endl << endl;
}

bool confirmPurchase(int orderProductsCount, int orderProductId[], int quantityInStock[], int orderProductsQuantity[]){
    char choice;
    int productId;

    while(true){
        cout << "Confirm Purchase (y/n): ";
        cin >> choice;
    
        if(choice == 'y' || choice == 'Y'){
            for(int i = 0; i < orderProductsCount; i++){
                productId = orderProductId[i];
                quantityInStock[productId] -= orderProductsQuantity[i];
            }
            return true;
        }else if(choice == 'n' || choice == 'N'){
            return false;
        }else{
            cout << "Invalid Input!" << endl;
        }
    }
}

bool editOrder(int &orderProductsCount, string orderProductNames[], int orderProductsQuantity[], float orderPrices[], int orderProductId[],  int idWidth, int nameWidth){
    char choice;
    while(true){
        cout << "Do you want to edit order (y/n): ";
        cin >> choice;

        if(choice == 'y' || choice == 'Y'){
            orderRemoveProduct(orderProductsCount, orderProductNames, orderProductsQuantity, orderPrices, orderProductId, idWidth, nameWidth);
            return true;
        }else if(choice == 'n' || choice == 'N'){
            cout << "Order Canceled!" << endl;
            return false;
        }else{
            cout << "Invalid Input!" << endl;
        }
    }
}

// ======== Logging of data 

void printHeader(){
    system("cls");
    generateColors(11);
    SetConsoleOutputCP(CP_UTF8);
    cout << "══════════════════════════════════════════" << endl;
    cout << " ███████████   ██████   ██████  █████████ " << endl;
    cout << "░░███░░░░░███ ░░██████ ██████  ███░░░░░███" << endl;
    cout << " ░███    ░███  ░███░█████░███ ░███    ░░░ " << endl;
    cout << " ░██████████   ░███░░███ ░███ ░░█████████ " << endl;
    cout << " ░███░░░░░███  ░███ ░░░  ░███  ░░░░░░░░███" << endl;
    cout << " ░███    ░███  ░███      ░███  ███    ░███" << endl;
    cout << " █████   █████ █████     █████░░█████████ " << endl;
    cout << "░░░░░   ░░░░░ ░░░░░     ░░░░░  ░░░░░░░░░  " << endl;
    cout << endl << "          Retail Management System        " << endl;
    cout << "══════════════════════════════════════════" << endl;                                    
    generateColors(6);
}

int welcomeScreen(){
    int choice = 0;
    cout << endl << "_____________" << endl;
    cout << "   Welcome   " << endl;
    cout <<"_____________" << endl;
    cout << "1. Sign In" << endl;
    cout << "2. Sign Up" << endl;
    cout << "3. Login as admin" << endl;
    cout << "4. Exit" << endl;
    cout << endl << "Option (1-4): ";
    cin >> choice; 
    return choice; 
}

void checkStock(int inventorySize, int productId[], string productNames[], float prices[], int quantityInStock[], int idWidth, int nameWidth, int priceWidth, int qtyWidth){
    cout << "********************************************************************************" << endl;
    cout << std::left << setw(idWidth) << "Product ID" 
          << std::left << setw(nameWidth) << "Product name"
          << std::left << setw(priceWidth) << "Price"
          << std::left << setw(qtyWidth) << "Quantity in Stock" << endl;
    cout << "********************************************************************************" << endl;
    for(int i = 0; i < inventorySize; i++){
        printProductData(productId[i], productNames[i], prices[i], quantityInStock[i], idWidth, nameWidth, priceWidth, qtyWidth);
    }
    cout << "********************************************************************************" << endl;
}

void printProductData(int productId, string productName, float productPrice, int quantityInStock, int idWidth, int nameWidth, int priceWidth, int qtyWidth){
    cout << std::left << setw(idWidth) << productId 
          << std::left << setw(nameWidth) << productName 
          << std::left << setw(priceWidth) << productPrice 
          << std::left << setw(qtyWidth) << quantityInStock << endl; 
}

void printOrderData(string productName, float productPrice, int quantityInStock, int nameWidth, int priceWidth, int qtyWidth){
    cout  << std::left << setw(nameWidth) << productName 
          << std::left << setw(qtyWidth) << quantityInStock 
          << std::left << "$" << setw(priceWidth) << productPrice << endl;
} 	

// ======== Backbone

void printPOSMenu(string productNames[], int quantityInStock[], float prices[], float &total, int &orderProductsCount, 
                int inventorySize, int inventoryLimit, string orderProductNames[], int orderProductsQuantity[], float orderPrices[], int orderProductId[], 
                string &customerName, int productId[], int idWidth, int nameWidth, int priceWidth, int qtyWidth, string currentUser, string &formattedDate){
    system("cls");
    printHeader();
    int option = 0;
    while(option != 4){
    cout << endl << "______________" << endl;
    cout << "   POS MENU   " << endl;
    cout <<"______________" << endl;
        cout << "1. Record Sale" << endl;
        cout << "2. Check Stock" << endl;
        cout << "3. Search Product" << endl;
        cout << "4. Exit POS Menu" << endl;
        cout << endl << "Enter option (1-4): ";
        cin >> option;
        ValidateInputStream();

        if(option == 1){
            system("cls");
            float currentTotal = salesMenu(productId, productNames, quantityInStock, prices, total, orderProductsCount, 
             inventorySize, inventoryLimit, orderProductNames, orderProductsQuantity, orderPrices, orderProductId, customerName, idWidth, nameWidth, qtyWidth, priceWidth, currentUser, formattedDate);
            if(currentTotal == 0){
                cout << "################################################" << endl;
                stopExecutionWithIgnore();
                system("cls");
                return;
            }else{
                cout << "The total is: $" << currentTotal << endl;
                cout << "################### Order Closed ###################" << endl;
                stopExecutionWithIgnore();
                system("cls");
            }
        } else if(option == 2){
            system("cls");
            checkStock(inventorySize, productId, productNames, prices, quantityInStock, idWidth, nameWidth, priceWidth, qtyWidth);
            stopExecution();
        } else if(option == 3){
            system("cls");
            searchProduct(productNames, quantityInStock, prices, productId, inventorySize, idWidth, nameWidth, priceWidth, qtyWidth);
        } else if(option != 4){
            cout << "Invalid Input" << endl;
            stopExecution();
        }
    }
}

float salesMenu(int productId[], string productNames[], int quantityInStock[], float prices[], float &total, int &orderProductsCount, 
                int inventorySize, int inventoryLimit, string orderProductNames[], int orderProductsQuantity[], float orderPrices[], int orderProductId[], string &customerName, 
                int idWidth, int nameWidth, int qtyWidth, int priceWidth, string currentUser, string &formattedDate){
    total = 0; 
    bool purchaseConfirmed = false;
    int option;
    
    while(true){
        cout << endl << "________________" << endl;
        cout << "   Sales MENU   " << endl;
        cout <<"________________" << endl;
        if(customerName == " "){
            cout << "Enter Customer Name: ";
            getline(cin, customerName); 
            cout << '\n';
        }
        cout << "1. Enter details of a product" << endl;
        cout << "2. Remove a product from order" << endl;
        cout << "3. Close Order: " << endl;
        cout << "4. Exit/Cancel Order: " << endl;
        cout << endl << "Enter option (1-4): ";
        cin >> option;
        ValidateInputStream();

        if(option == 1){
            chooseProduct(productNames, quantityInStock, prices, total, orderProductsCount, 
                inventorySize, inventoryLimit, orderProductNames, orderProductsQuantity, orderPrices, orderProductId);
        }else if(option == 2){
            orderRemoveProduct(orderProductsCount, orderProductNames, orderProductsQuantity, orderPrices, orderProductId, idWidth, nameWidth);
        }else if(option == 3){
            printBillConsole(customerName, nameWidth, qtyWidth, priceWidth, orderProductsCount, total, orderProductNames, orderPrices, orderProductsQuantity);
            purchaseConfirmed = confirmPurchase(orderProductsCount, orderProductId, quantityInStock, orderProductsQuantity);
            if(purchaseConfirmed){
                printBillPDF(total, inventoryLimit, orderProductNames, orderProductsQuantity, orderPrices, orderProductsCount, customerName, currentUser, formattedDate);
                orderProductsCount = 0;
                saveProductData(inventorySize, productNames, productId, prices, quantityInStock);
                return total;      
            }else{
                if(!editOrder(orderProductsCount, orderProductNames, orderProductsQuantity, orderPrices, orderProductId, idWidth, nameWidth)){
                    return 0;
                }else{
                    printBillPDF(total, inventoryLimit, orderProductNames, orderProductsQuantity, orderPrices, orderProductsCount, customerName, currentUser, formattedDate);
                    orderProductsCount = 0;
                    saveProductData(inventorySize, productNames, productId, prices, quantityInStock);
                    return total;      
                }      
            }
        } else if(option == 4){
            total  = 0;
            cout << "!! You exited the sales Menu !!" << endl;
            orderProductsCount = 0;
            return 0;
        } else{
            cout << "Invalid Input" << endl;
        } 
    }
}


void chooseProduct(string productNames[], int quantityInStock[], float prices[], float &total, int &orderProductsCount, 
                int inventorySize, int inventoryLimit, string orderProductNames[], int orderProductsQuantity[], float orderPrices[], int orderProductId[]){
    string productName;
    int choice;
    int quantity;
    float price = 0;

    cout << endl << "Choose Product from the catalog:" << endl;
    for(int i = 0; i < inventorySize; i++){
        cout << i + 1 << ". " << productNames[i] << endl;
    }
    cout << "Choice (1-" << inventorySize << "): ";
    cin >> choice;
    ValidateInputStream();
    choice--;

    if(choice < inventorySize && choice >= 0){ 
        cout << "Current stock of "<< productNames[choice] << ": " << quantityInStock[choice] << ". Enter quantity: ";
        cin >> quantity;
        ValidateInputStream();
    
        if(quantity <= 0){
            cout << "Invalid Quantity!" << endl;
            stopExecution();
            return;
        }

        if(quantityInStock[choice] == 0){
            cout << "Stock of " << productNames[choice] << " has finished!" << endl;
        } else if(quantityInStock[choice] < quantity){
            cout << "Not enough stock of " << productNames[choice] << "! Quantity in Stock: " << quantityInStock[choice] << endl;
        }else{
            productName = productNames[choice];
            price = (prices[choice] * quantity);
            cout << "Price: $" << price << endl;
            total += price;
            updateBill(choice, productName, quantity, price, orderProductsCount, inventoryLimit, orderProductNames, orderProductsQuantity, orderPrices, orderProductId);
        }
        
    }else{
        cout << "Invalid Input!" << endl;
    }
}

void searchProduct(string productNames[], int quantityInStock[], float prices[], int productId[], int inventorySize, int idWidth, int nameWidth, int priceWidth, int qtyWidth){
    int id;
    string name;
    float price;
    int quantity;
    int choice = 0;

    cout << "1. Search by id" << endl;
    cout << "2. Serach by name" << endl;
    cout << "Choice: ";
    cin >> choice;
    ValidateInputStream();

    if(choice == 1){
        cout << "Enter Product ID: ";
        cin >> id;

        for(int i = 0; i < inventorySize; i++){
            if(productId[i] == id){
                name = productNames[i];
                price = prices[i];
                quantity = quantityInStock[i];
            }
        }
    }else if(choice == 2){
        cout << "Enter Product Name: ";
        cin >> name;

        for(int i = 0; i < inventorySize; i++){
            if(productNames[i] == name){
                id = productId[i];
                price = prices[i];
                quantity = quantityInStock[i];
            }
        }
    }else{
        cout << "Invalid Input!" << endl;
        return;
    }

    cout << "********************************************************************************" << endl;
    cout << std::left << setw(idWidth) << "Product ID" 
        << std::left << setw(nameWidth) << "Product name"
        << std::left << setw(priceWidth) << "Price"
        << std::left << setw(qtyWidth) << "Quantity in Stock" << endl;
    cout << "********************************************************************************" << endl;
    printProductData(id, name, price, quantity, idWidth, nameWidth, priceWidth, qtyWidth);
    cout << "********************************************************************************" << endl;
    stopExecutionWithIgnore();
    system("cls");
}

void orderRemoveProduct(int &orderProductsCount, string orderProductNames[], int orderProductsQuantity[], float orderPrices[], int orderProductId[],  int idWidth, int nameWidth){
    int productNo;

    if(orderProductsCount == 0){
        cout << "There are no products to be removed." << endl;
    }else{
        cout << endl;
        cout << "************************************************" << endl;
        cout << std::left << setw(idWidth) << "NO." << std::left << setw(nameWidth) << "Names" << endl;
        cout << "************************************************" << endl;
        for(int i = 0; i < orderProductsCount; i++){
            cout << std::left << setw(idWidth) << i + 1 << std::left << setw(nameWidth) << orderProductNames[i] << endl;
        }

        while(true){
            cout << endl << "Enter the product number to remove: ";
            cin >> productNo;
            ValidateInputStream();
    
            productNo--;
    
            if(productNo < orderProductsCount){
                orderProductNames[productNo] = orderProductNames[orderProductsCount - 1];
                orderPrices[productNo] = orderPrices[orderProductsCount - 1];
                orderProductsQuantity[productNo] = orderProductsQuantity[orderProductsCount - 1];
                cout << "Product removed!" << endl;
                orderProductsCount--;
                break;
            }else{
                cout << "Invalid product number!" << endl;
            }
        }

    }
}

// ======== Signing in and up

bool signInMenu(int currentUsers, string userNames[], string userPasswords[], string &currentUser){
    string name;
    string password;

    cout << "Enter user name: ";
    getline(cin, name);
    cout << "Enter User password: ";
    password = encriptPassword();
    
    if(verifyUser(currentUser, name, password)){
        return true;
    }
    return false;
}

bool signUpMenu(int currentUsers, string signUpRequestData[][2], int &signUpRequests, string userNames[]){
    string name;
    string password;

    if(currentUsers < maxUsers){
        cout << "Enter User name: ";
        getline(cin, name);

        for(int i = 0; i < currentUsers; i++){
            if(checkUserExists(name)){
                cout << "User already exists!" << endl;
                return false;
            }
        }

        cout << "Enter User password: ";
        password = encriptPassword();
        password = hashPassword(password);
        
        signUpRequestData[signUpRequests][0] = name;
        signUpRequestData[signUpRequests][1] = password;
        signUpRequests++;
        storeSignUpDataEnc(signUpRequests, signUpRequestData);
        return true;
    }
    cout << "Maximum Users reached!" << endl;
    return false;
}

// ======== Admin panel and related functionality

bool passwordAuth(){
    string pass;
    cout << "Enter administrator password: ";
    pass = encriptPassword();

    return verifyAdmin(pass);
}

void adminPanel(int &inventorySize, int inventoryLimit, int productId[], string productNames[], float prices[], int quantityInStock[], int idWidth, int nameWidth, int priceWidth, int qtyWidth,
                int signUpRequests, string signUpRequestData[][2], int &currentUsers, string userNames[], string userPasswords[], int maxUsers){
    int option = 0, loginOnce = 0;
    cout << "Welcome! Select action to perform: " << endl;
    while(option != 7){
        loginOnce++;
        system("cls");

        AdminPanelStart:

        if(loginOnce > 1){
            notificationPane(inventorySize, quantityInStock, productId, productNames, signUpRequests, signUpRequestData);
        }


        cout << endl << "________________" << endl;
        cout << "   Admin MENU   " << endl;
        cout <<"________________" << endl;
        cout << "1. Check Inventory" << endl; 
        cout << "2. Add Stock" << endl; 
        cout << "3. Product Management Panel" << endl; 
        cout << "4. User Management panel" << endl;
        cout << "5. View Sign Up requests" << endl;
        cout << "6. Change Admin Password" << endl;
        cout << "7. Exit admin panel" << endl;
        cout << endl << "Option (1-7): ";

        if(loginOnce == 1){
            notificationPane(inventorySize, quantityInStock, productId, productNames, signUpRequests, signUpRequestData);
        }

        cin >> option;
        ValidateInputStream();

        if(option == 1){
            checkStock(inventorySize, productId, productNames, prices, quantityInStock, idWidth, nameWidth, priceWidth, qtyWidth);
            stopExecution();
        }else if(option == 2){
            addStock(inventorySize, productId, productNames, prices, quantityInStock, qtyWidth, idWidth, nameWidth, priceWidth);
        }else if(option == 3){
            manageProducts(inventorySize, inventoryLimit, productId, productNames, prices, quantityInStock, nameWidth, priceWidth, qtyWidth);
            stopExecution();
            system("cls");
            goto AdminPanelStart;
        }else if(option == 4){ 	
            manageUsers(userNames, userPasswords, currentUsers, maxUsers, idWidth, nameWidth);
            stopExecution();
            system("cls");
            goto AdminPanelStart;
        }else if(option == 5){ 	
            signUpRequest(signUpRequests, signUpRequestData, currentUsers, userNames, userPasswords);
            stopExecution();
        }else if(option == 6){ 	
            changeAdminPassword();
            stopExecution();
        }else if(option == 7){
            cout << "You exited the admin panel!" << endl;
            stopExecution();
        }else{ 
            cout << "Invalid Input" << endl;
            stopExecution();
        }
    }
}

void addStock(int inventorySize, int productId[], string productNames[], float prices[], int quantityInStock[], int qtyWidth, int idWidth, int nameWidth, int priceWidth){
    int id = 0; 
    int quantityToAdd = 0;
    cout << endl << "Current stock and products: " << endl;
    checkStock(inventorySize, productId, productNames, prices, quantityInStock, idWidth, nameWidth, priceWidth, qtyWidth);
    cout << endl << "Enter Product ID to add stock: ";
    cin >> id;
    ValidateInputStream();

    if(id > 0 && id <= inventorySize){
        cout << "Enter quantity to add ("<< qtyWidth <<" characters max): ";
        cin >> quantityToAdd;
        ValidateInputStream();

        if(quantityToAdd > 0){
            int totalQuantity = quantityInStock[id - 1] + quantityToAdd;

            if(!checkDataWidth(qtyWidth, to_string(totalQuantity))) return;
            else{
                quantityInStock[id - 1] = totalQuantity;
                cout << "Updated Stock of " << productNames[id - 1] << ": " << quantityInStock[id - 1] << endl;
                
                saveProductData(inventorySize, productNames, productId, prices, quantityInStock);
                stopExecution();
            }
        } 
        else{
            cout << "Invalid quantity enetered!" << endl;
            stopExecution();
        }
    }else{
        cout << "Invalid ID Entered!" << endl;
        stopExecution();
    }
}

void signUpRequest(int &signUpRequests, string signUpRequestData[][2], int &currentUsers, string userNames[], string userPasswords[]){
    char allow;

    if(signUpRequests > 0){
        cout << "Request for new sign up (" << signUpRequests << "): " << endl;
    
        for(int i = 0; i < signUpRequests; i++){
            cout << "Name: " << signUpRequestData[i][0] << endl;
            while(true){
                cout << "Allow (y/n): ";
                cin >> allow;

                if(allow == 'Y' || allow == 'y'){
                    userNames[currentUsers] = signUpRequestData[i][0];
                    userPasswords[currentUsers] = signUpRequestData[i][1]; 
                    currentUsers++;
                    break;
                }else if(allow == 'N' || allow == 'n'){
                    cout << "Denied!" << endl;
                    break;
                }else{
                    cout << "Invalid Input!" << endl;
                }
                stopExecution();
            }

            if(signUpRequests > 1){
                for(int j = i; j < signUpRequests - 1; j++){
                    signUpRequestData[j][0] = signUpRequestData[j + 1][0];
                    signUpRequestData[j][1] = signUpRequestData[j + 1][1];
                }
            }else{
                signUpRequestData[0][0] = "";
                signUpRequestData[0][1] = "";
            }

            signUpRequests--;    
        }
        
        storeUserDataEnc(currentUsers, userNames, userPasswords);
        storeSignUpDataEnc(signUpRequests, signUpRequestData);
    }else{
        cout << "There are no new sign up requests." << endl;
    }
}

void changeAdminPassword(){
    string password, confirmPass;
    bool verified = passwordAuth();

    if(!verified){
        cout << "Incorrect Password!" << endl;
        return;
    }

    cout << "Enter new password: ";
    password = encriptPassword();

    cout << "Confirm password: ";
    confirmPass = encriptPassword();

    if(password != confirmPass){
        cout << "Password didn't match! Try again." << endl;
        return;
    }

    changeAdminEnc(password);
    cout << "Password has been changed successfully!" << endl;
}

// Product Management

void manageProducts(int &inventorySize, int inventoryLimit, int productId[], string productNames[], float prices[], int quantityInStock[], int nameWidth, int priceWidth, int qtyWidth){
    char option;
    system("cls");
    while(true){
        cout << endl << "_________________________" << endl;
        cout << "Product Managemment Panel" << endl;
        cout << "_________________________" << endl << endl;
        cout << "1. Add Product" << endl; 
        cout << "2. Update product details" << endl; 
        cout << "3. Remove product" << endl;
        cout << "4. Exit" << endl;
    
        cout << endl << "Option (1-4): ";
        cin >> option;

        if(option == '1'){
            addProduct(inventorySize, inventoryLimit, productId, productNames, prices, quantityInStock, nameWidth, priceWidth, qtyWidth);
            stopExecution();
        } else if (option == '2'){
            updateProduct(inventorySize, productId, productNames, prices, quantityInStock, nameWidth, priceWidth);
            stopExecution();
        } else if (option == '3'){
            removeProduct(inventorySize, productId, productNames, prices, quantityInStock);
            stopExecution();
        } else if (option == '4'){
            break;
        } else{
            cout << "Invalid Input!" << endl;
        }
        system("cls");
    }
}

void addProduct(int &inventorySize, int inventoryLimit, int productId[], string productNames[], float prices[], int quantityInStock[], int nameWidth, int priceWidth, int qtyWidth){
    string productName;
    float productPrice;
    int productQuantity, count = 0;
    
    do{
        cout << "Enter number of products you want to add: ";
        cin >> count;
        ValidateInputStream();
        if(count + inventorySize > inventoryLimit){
            cout << "The value exceeded the inventory limit of " << inventoryLimit << endl;
            cout << "Current inventory size: " << inventorySize << endl;
        }
    }while(count + inventorySize > inventoryLimit);

    // ValidateInputStream(); 

    for(int i = 0; i < count; i++){
        
        cout << "Enter name of product (" << nameWidth << " characters max): ";
        getline(cin, productName);
        if(!checkDataWidth(nameWidth, productName)) continue;
        else if(productExists(productName, productNames, inventorySize)){
            cout << "Product already exists! You can update it or add stock to it." << endl;
            continue;
        }

        cout << "Enter price of product (" << priceWidth << " characters max): ";
        cin >> productPrice;
        ValidateInputStream();

        if(!checkDataWidth(priceWidth, to_string(productPrice))) continue;

        cout << "Enter quantity of product (" << qtyWidth << " characters max): ";
        cin >> productQuantity;
        ValidateInputStream();

        if(!checkDataWidth(qtyWidth, to_string(productQuantity))) continue;

        
        productNames[inventorySize] = productName;
        prices[inventorySize] = productPrice;
        quantityInStock[inventorySize] = productQuantity;
        productId[inventorySize] = inventorySize + 1;
        inventorySize++; 
        
        saveProductData(inventorySize, productNames, productId, prices, quantityInStock);
        cout << "Product added successfully!" << '\n';
        cout << endl;
    }
}

void removeProduct(int &inventorySize, int productId[], string productNames[], float prices[], int quantityInStock[]){
    string productName;
    
    cout << "Enter name of the product you want to remove: ";
    cin.ignore();
    getline(cin, productName);

    for(int i = 0; i < inventorySize; i++){
        if(productNames[i] == productName){
            for(int j = i + 1; j < inventorySize; j++){
                productNames[j - 1] = productNames[j];
                prices[j - 1] = prices[j];
                quantityInStock[j - 1] = quantityInStock[j]; 
            }
            cout << "Product was found and successfully removed!" << endl;
            inventorySize--;
            saveProductData(inventorySize, productNames, productId, prices, quantityInStock);
            return;
        }
    }
    cout << "Product was not found!" << endl;
}

void updateProduct(int inventorySize, int productId[], string productNames[], float prices[], int quantityInStock[], int nameWidth, int priceWidth){
    string productName;
    float productPrice;
    bool isPresent = false;

    // ValidateInputStream(); 
    cout << "Enter name of the product you want to update: ";
    cin.ignore();
    getline(cin, productName);

    for(int i = 0; i < inventorySize; i++){
        if(productNames[i] == productName){
            isPresent = true; 
            
            cout << "Enter new name of the product or enter 'same' to keep it unchanged (" << nameWidth << " characters max): ";
            cin >> productName;
            ValidateInputStream();

            if(!checkDataWidth(nameWidth, productName)) return;

            cout << "Enter new price or enter '-1' to keep it unchanged (" << priceWidth << " characters max): ";
            cin >> productPrice;
            ValidateInputStream();
            if(!checkDataWidth(priceWidth, to_string(productPrice))) return;
            
            
            if(productPrice != -1 && productPrice <= 0){
                cout << "Invalid price entered! Product remains unchanged." << endl;
            }
            else if(productPrice != -1 && productPrice > 0){
                if(productName != "same") productNames[i] = productName;
                prices[i] = productPrice;
                
                saveProductData(inventorySize, productNames, productId, prices, quantityInStock);
                cout << "Product was found and successfully updated!" << endl;
            }else if(productPrice == -1 && productName != "same"){
                productNames[i] = productName;
                cout << "Product was found and successfully updated!" << endl;
                saveProductData(inventorySize, productNames, productId, prices, quantityInStock);
            }else if(productPrice == -1 && productName == "same"){
                cout << "Product details unchanged!" << endl;
            }
            return; 
        }
    }

    if(!isPresent){
        cout << "Product was not found!" << endl;
    }
}

// User Management

void manageUsers(string userNames[], string userPasswords[], int &currentUsers, int maxUsers, int idWidth, int nameWidth){
    char option;
    system("cls");
    while(true){
        cout << endl << "______________________" << endl;
        cout << "User Managemment Panel" << endl;
        cout << "______________________" << endl << endl;
        cout << "1. List All Users" << endl;
        cout << "2. Add a User" << endl;
        cout << "3. Edit User Info" << endl;
        cout << "4. Remove a User" << endl;
        cout << "5. Exit" << endl;
    
        cout << endl << "Option (1-5): ";
        cin >> option;

        if(option == '1'){
            listUsers(userNames, currentUsers, idWidth, nameWidth);
            stopExecutionWithIgnore();
        } else if (option == '2'){
            addUser(userNames, userPasswords, maxUsers, currentUsers, nameWidth);
            stopExecution();
        } else if (option == '3'){
            editUserInfo(userNames, userPasswords, currentUsers);
            stopExecution();
        } else if (option == '4'){
            deleteUser(userNames, userPasswords, currentUsers);
            stopExecution();
        } else if (option == '5'){
            break;
        } else{
            cout << "Invalid Input!" << endl;
        }
        system("cls");
    }
}

void listUsers(string userNames[], int currentUsers, int idWidth, int nameWidth){
    cout << endl;
    cout << setw(idWidth) << std::left << "Sr. no" << setw(nameWidth) << std::left << "Username" << endl;
    cout << "=======================================" << endl;
    for(int i = 0; i < currentUsers; i++){
        cout << setw(idWidth) << std::left << i + 1 << setw(nameWidth) << std::left << userNames[i] << endl;
    }
    cout << endl;
}

void addUser(string userNames[], string userPasswords[], int maxUsers, int &currentUsers, int nameWidth){
    string name, password;
    bool exists = false;

    cout << endl;

    if(currentUsers >= maxUsers){
        cout << "Max users have been reached!" << endl;
        return;
    }
    
    while(true){
        cout << "Enter Username to add or enter -1 to exit: ";
        cin.ignore();
        getline(cin, name);

        if(name == "-1") break;

        if(name.length() > nameWidth){
            cout << "Name should be atmost " << nameWidth << " characters long.";
            continue;
        }
        
        for(int i = 0; i < currentUsers; i++){
            if(name == userNames[i]){
                cout << "User already exists!" << endl;
                exists = true;
            }
        }

        if(exists) continue;
        else{
            cout << "Set password for user: ";
            cin >> password;
            password = hashPassword(password);
    
            userNames[currentUsers] = name;
            userPasswords[currentUsers] = password;
            currentUsers++;
            
            storeUserDataEnc(currentUsers, userNames, userPasswords);
            break;
        }
    }
}

void editUserInfo(string userNames[], string userPasswords[], int &currentUsers){
    string name, password, confirmPass;
    bool found = false, verified = false;
    int userIdx;

    cout << endl;
    cout << "Enter name of the user you want to edit: ";
    cin.ignore();
    getline(cin, name);

    for(int i = 0; i < currentUsers; i++){
        if(userNames[i] == name){
            userIdx = i;
            found = true;
            break;
        }
    }

    if(!found){
        cout << "User was not found!" << endl;
        return;
    }

    cout << "Enter name to change or enter 'same' to keep it unchanged: ";
    getline(cin, name);

    if(name != "same") userNames[userIdx] = name;

    cout << "Enter password to change or enter '-1' to keep it unchanged: ";
    password = encriptPassword();
    
    if(password != "-1"){
        cout << "Confirm password: ";
        confirmPass = encriptPassword();

        if(confirmPass != password){
            cout << "Password didn't match!" << endl;
            return;
        }

        userPasswords[userIdx] = hashPassword(password);
    } 

    storeUserDataEnc(currentUsers, userNames, userPasswords);
    cout << "User Info Updated!" << endl;
}

void deleteUser(string userNames[], string userPasswords[], int &currentUsers){
    string name;

    cout << endl;
    cout << "Enter name of the user you want to remove: ";
    cin.ignore();
    getline(cin, name);

    for(int i = 0; i < currentUsers; i++){
        if(userNames[i] == name){
            for(int j = i + 1; j < currentUsers; j++){
                userNames[j - 1] = userNames[j];
                userPasswords[j - 1] = userPasswords[j];
            }
            cout << "User was found and successfully removed!" << endl;
            currentUsers--;
            storeUserDataEnc(currentUsers, userNames, userPasswords);
            return;
        }
    }
    cout << "User was not found!" << endl;
}

// Notification Pane

void notificationPane(int inventorySize, int quantityInStock[], int productId[], string productNames[], int &signUpRequests, string signUpRequestData[][2]){
    int coordX = 50, coordY = 1;
    COORD savedPosition = getCursorPosition();
    
    
    gotoxy(coordX, coordY);
    cout << "_______________________" << endl;
    coordY++;
    gotoxy(coordX, coordY);
    cout << "   Notification Pane   " << endl;
    coordY++;
    gotoxy(coordX, coordY);
    cout << "_______________________" << endl;
    coordY++;
    
    generateColors(4);
    stockNotification(coordX, coordY, inventorySize, quantityInStock, productId, productNames);
    
    generateColors(5);
    coordY++;
    signUpNotification(coordX, coordY, signUpRequests, signUpRequestData);

    gotoxy(savedPosition.X, savedPosition.Y);
    generateColors(14);

}

void signUpNotification(int &coordX, int &coordY, int signUpRequests, string signUpRequestData[][2]){
    if(signUpRequests > 0){
        gotoxy(coordX, coordY);
        cout << "Requests for new sign up: " << endl;
        coordY++;
        for(int i = 0; i < signUpRequests; i++){    
            gotoxy(coordX, coordY);
            cout << "Name: " << signUpRequestData[i][0] << endl;
            coordY++;
        }
    }
}

void stockNotification(int &coordX , int &coordY, int inventorySize, int quantityInStock[], int productId[], string productNames[]){
    int minQuantity = 2;
    int isLow = 0;

    for(int i = 0; i < inventorySize; i++){
        if(quantityInStock[i] <= minQuantity){
            isLow++;
            if(isLow == 1){
                gotoxy(coordX, coordY);
                cout << "Quantity of these products is critically low:" << endl;
                coordY++;
            }
            gotoxy(coordX, coordY);
            cout << "ID: " << productId[i] << ". " << productNames[i] << ". " << "Quantiy: " << quantityInStock[i] << endl;
            coordY++;
        }
    }
}

// ======== Utility functions

string encriptPassword(){
    string pass;
    char dig; 

    while((dig = getch()) != '\r'){
        if(dig == '\b'){
            if(pass.length() > 0){
                pass.pop_back();
                cout << "\b \b";
            }
        }else if(dig != '\r'){
            cout << "*";
            pass += dig;
        }
    }
    cout << endl;
    return pass;
}

bool checkDataWidth(int dataWidth, string data){
    if(data.length() > dataWidth){
      cout << "Data exceeded the maximum width of " << dataWidth << " characters" << endl;
      stopExecution();
      return false;
    }
    return true;
}

bool productExists(string productName, string productNames[], int inventorySize){
    for(int i = 0; i < inventorySize; i++){
        if(productNames[i] == productName) return true;
    }
    return false;
}

void ValidateInputStream(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void stopExecution(){
    if(!cin) cin.clear();
    cout << "Press enter to continue...";
    cin.get();
}

void stopExecutionWithIgnore(){
    if(!cin) cin.clear();
    cout << "Press enter to continue...";
    cin.ignore();
    cin.get();
}

COORD getCursorPosition(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    
    // Get info about the console screen buffer
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        // Return the dwCursorPosition member
        return csbi.dwCursorPosition;
    } else {
        // Return (0, 0) on error
        return {0, 0}; 
    }
}

void gotoxy(int x, int y){
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void generateColors(int color){
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // pick the colorattribute k you want
    SetConsoleTextAttribute(hConsole, color);
}