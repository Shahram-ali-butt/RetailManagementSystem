#include <iostream>
#include "../include/crypto_functions.h"
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;

const string adminFile = "data/admin.txt";
const string userFile = "data/users.txt";
const string signUpFile = "data/signUpData.txt";


// CAESAR CIPHER

string caesarEncrypt(string text, int shift){
    char character, shiftedChar;
    int ascii;
    string result = "";
    shift = shift % 26;
    
    for (int i = 0; i < text.length(); i++){
        character = text[i];
        if(isupper(character)){
            ascii = character - int('A');
            ascii = (ascii + shift) % 26;
            shiftedChar = 'A' + ascii;
            result += shiftedChar;
        }else{
            ascii = character - int('a');
            ascii = (ascii + shift) % 26;
            shiftedChar = 'a' + ascii;
            result += shiftedChar;
        } 
    }
    return result;
}

string caesarDecrypt(string text, int shift) {
    char character, shiftedChar;
    int ascii;
    string result = "";
    shift = shift % 26;
    
    for(int i = 0; i < text.length(); i++){
        character = text[i];
        if(isupper(character)){
            ascii = character - int('A');
            ascii = (ascii - shift) % 26;
            shiftedChar = 'A' + ascii;
            result += shiftedChar;
        }else{
            ascii = character - int('a');
            ascii = (ascii - shift) % 26;
            shiftedChar = 'a' + ascii;
            result += shiftedChar;
        } 
    }
    return result;
}

// VIGENERE CIPHER 

string vigenereEncrypt(string text, string key) {
    char character, shiftedChar;
    string result = "";
    int keyIndex = 0, shift, ascii, idx;
    
    for(int i = 0; i < text.length(); i++){
        character = text[i];
        idx = keyIndex % key.length();
        shift = toupper(key[idx]) - 'A';
        
        if(isupper(character)){
            ascii = character - int('A');
            ascii = (ascii + shift + 26) % 26;
            shiftedChar = 'A' + ascii;
            result += shiftedChar;
        }else{
            ascii = character - int('a');
            ascii = (ascii + shift + 26) % 26;
            shiftedChar = 'a' + ascii;
            result += shiftedChar;
        }

        keyIndex++;
    }

    return result;
}

string vigenereDecrypt(string text, string key) {
    char character, shiftedChar;
    string result = "";
    int keyIndex = 0, shift, ascii, idx;
    
    for(int i = 0; i < text.length(); i++){
        character = text[i];
        idx = keyIndex % key.length();
        shift = toupper(key[idx]) - 'A';
        
        if(isupper(character)){
            ascii = character - int('A');
            ascii = (ascii - shift + 26) % 26;
            shiftedChar = 'A' + ascii;
            result += shiftedChar;
        }else{
            ascii = character - int('a');
            ascii = (ascii - shift + 26) % 26;
            shiftedChar = 'a' + ascii;
            result += shiftedChar;
        }

        keyIndex++;
    }
    return result;
}

// AFFINE CIPHER IMPLEMENTATION

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // No inverse exists
}

string affineEncrypt(string text, int a, int shift) {
    string result = "";
    char character, shiftedChar;
    int ascii;
    
    // Check if 'a' and 26 are coprime
    if (gcd(a, 26) != 1) {
        return "'a' must be coprime with 26";
    }
    
    for (int i = 0; i < text.length(); i++){
        character = text[i];
        if(isupper(character)){
            ascii = character - int('A');
            ascii = (a * ascii + shift + 26) % 26;
            shiftedChar = 'A' + ascii;
            result += shiftedChar;
        }else{
            ascii = character - int('a');
            ascii = (a * ascii + shift + 26) % 26;
            shiftedChar = 'a' + ascii;
            result += shiftedChar;
        } 
    }

    return result;
}

string affineDecrypt(string text, int a, int shift) {
    string result = "";
    char character, shiftedChar;
    int ascii;

    int aInv = modInverse(a, 26);
    if (aInv == -1) {
        return "No modular inverse exists for 'a'";
    }

    for (int i = 0; i < text.length(); i++){
        character = text[i];
        if(isupper(character)){
            ascii = character - int('A');
            ascii = (aInv * (ascii - shift + 26)) % 26;
            shiftedChar = 'A' + ascii;
            result += shiftedChar;
        }else{
            ascii = character - int('a');
            ascii = (aInv * (ascii - shift + 26)) % 26;
            shiftedChar = 'a' + ascii;
            result += shiftedChar;
        } 
    }
    
    return result;
}

// HASHING

string hashPassword(string password){
    long long hash = 0;
    long long prime = 31;
    long long mod = 1000007;
    
    for (int i = 0; i < password.length(); i++) {
        hash = (hash * prime + (long long)password[i]) % mod;
    }
    
    return to_string(hash);
}

//  PASSWORD MANAGEMENT

void storeUserDataEnc(int currentUsers, string userNames[], string userPasswords[]) {
    ofstream file(userFile, ios::out);
    if (!file.is_open()) {
        cout << "File: "<< userFile << " not found" << endl;
    }
    
    string encryptedName, encryptedPassword, userNameFixed;

    file << currentUsers << '\n';

    for(int i = 0; i < currentUsers; i++){
        for(int j = 0; j < userNames[i].length(); j++){
            if(userNames[i][j] == ' ') userNameFixed += 'X';
            else userNameFixed += userNames[i][j];
    }

        encryptedName = affineEncrypt(userNameFixed, 5, 8);
        encryptedPassword = userPasswords[i];

        file << encryptedName << ',' << encryptedPassword << '\n';
        userNameFixed = "";
    }

    file.close();
}

bool verifyUser(string &currentUser, string userName, string userPassword) {
    ifstream file(userFile);
    bool verified = false;
    if (!file.is_open()){
        cout << "File: " << userFile << " not found" << endl;;
    }
    
    string line;
    string storedUser, encriptedUser, storedHash;
    string decryptedPassword;

    userPassword = hashPassword(userPassword);

    getline(file, line);

    while (getline(file, line)){
        stringstream ss(line);
        
        getline(ss, encriptedUser, ',');
        getline(ss, storedHash);
        
        storedUser = affineDecrypt(encriptedUser, 5, 8);

        for(int j = 0; j < storedUser.length(); j++){
            if(storedUser[j] == 'X') storedUser[j] = ' ';
        }

        if (storedUser == userName && userPassword == storedHash) {
            verified = true;
            currentUser = storedUser;
            break;
        }  
    }
    
    file.close();
    return verified;
}

bool verifyAdmin(string password) {
    ifstream file(adminFile);
    bool verified = false;
    if (!file.is_open()){
        cout << "File: " << adminFile << " not found" << endl;;
    }
    
    string storedHash;

    password = hashPassword(hashPassword(password));

    getline(file, storedHash);

    if (password == storedHash) {
        verified = true;
    }  
    
    file.close();
    return verified;
}

void changeAdminEnc(string password) {
    ofstream file(adminFile);

    if (!file.is_open()){
        cout << "File: " << adminFile << " not found" << endl;;
    }
    
    password = hashPassword(hashPassword(password));

    file << password;
    
    file.close();
}

void storeSignUpDataEnc(int signUpRequests, string signUpRequestData[][2]) {
    ofstream file(signUpFile, ios::out);
    if (!file.is_open()) {
        cout << "File: " << signUpFile << " not found" << endl;
    }
    
    string encryptedName, encryptedPassword, userNameFixed;

    file << signUpRequests << '\n';

    for(int i = 0; i < signUpRequests; i++){
        for(int j = 0; j < signUpRequestData[i][0].length(); j++){
            if(signUpRequestData[i][0][j] == ' ') userNameFixed += 'X';
            else userNameFixed += signUpRequestData[i][0][j];
        }
        
        encryptedName = affineEncrypt(userNameFixed, 9, 15);
        encryptedPassword = signUpRequestData[i][1];

        file << encryptedName << ',' << encryptedPassword << '\n';
        userNameFixed = "";
    }

    file.close();
}

void loadSignUpDataDec(int &signUpRequests, string signUpRequestData[][2]) {
    ifstream file(signUpFile);
    if (!file.is_open()){
        cout << "File: " << signUpFile << " not found" << endl;;
    }
    
    string line;
    string storedUser, encriptedUser, storedPassword;
    string decryptedPassword;

    file >> signUpRequests;
    file.ignore(numeric_limits<streamsize>::max(), '\n');

    for(int i = 0; i < signUpRequests; i++){
        getline(file, line);
        stringstream ss(line);
        
        getline(ss, encriptedUser, ',');
        getline(ss, storedPassword);

        storedUser = affineDecrypt(encriptedUser, 9, 15);

        for(int j = 0; j < storedUser.length(); j++){
            if(storedUser[j] == 'X') storedUser[j] = ' ';
        }
        
        signUpRequestData[i][0] = storedUser;
        signUpRequestData[i][1] = storedPassword;

    }
         
    file.close();
}

bool checkUserExists(string userName) {
    ifstream file(userFile);
    bool exists = false;
    if (!file.is_open()){
        cout << "File: " << userFile << " not found" << endl;;
    }
    
    string line, storedHash, encriptedUser, storedUser;

    getline(file, line);

    while (getline(file, line)){
        stringstream ss(line);
        
        getline(ss, encriptedUser, ',');
        getline(ss, storedHash);
        
        storedUser = affineDecrypt(encriptedUser, 5, 8);

        for(int j = 0; j < storedUser.length(); j++){
            if(storedUser[j] == 'X') storedUser[j] = ' ';
        }

        if (storedUser == userName) {
            exists = true;
            break;
        }  
    }
    
    file.close();
    return exists;
}

void loadUserDataDec(int &currentUsers, string userNames[], string userPasswords[]) {
    ifstream file(userFile);
    if (!file.is_open()){
        cout << "File: " << userFile << " not found" << endl;;
    }
    
    string line;
    string storedUser, encriptedUser, storedPassword;

    file >> currentUsers;
    file.ignore(numeric_limits<streamsize>::max(), '\n');

    for(int i = 0; i < currentUsers; i++){
        getline(file, line);
        stringstream ss(line);
        
        getline(ss, encriptedUser, ',');
        getline(ss, storedPassword);

        storedUser = affineDecrypt(encriptedUser, 5, 8);

        for(int j = 0; j < storedUser.length(); j++){
            if(storedUser[j] == 'X') storedUser[j] = ' ';
        }
        
        userNames[i] = storedUser;
        userPasswords[i] = storedPassword;
    }
         
    file.close();
}
