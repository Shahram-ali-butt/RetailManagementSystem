#ifndef CRYPTO_FUNCTIONS_H
#define CRYPTO_FUNCTIONS_H

#include <string>
using namespace std;

// CAESAR CIPHER
string caesarEncrypt(string text, int shift);
string caesarDecrypt(string text, int shift);

// VIGENERE CIPHER
string vigenereEncrypt(string text, string key);
string vigenereDecrypt(string text, string key);

// AFFINE CIPHER
string affineEncrypt(string text, int a, int shift);
string affineDecrypt(string text, int a, int shift);

int modInverse(int a, int m);

int gcd(int a, int b);

//  HASHING
string hashPassword(string password);

// PASSWORD MANAGEMENT
void storeUserDataEnc(int currentUsers, string userNames[], string userPasswords[]);
bool verifyUser(string &currentUser, string userName, string userPassword);
void storeSignUpDataEnc(int signUpRequests, string signUpRequestData[][2]);
void loadSignUpDataDec(int &signUpRequests, string signUpRequestData[][2]);
bool verifyAdmin(string password);
void changeAdminEnc(string password);
bool checkUserExists(string userName);
void loadUserDataDec(int &currentUsers, string userNames[], string userPasswords[]);

#endif 
