#include <iostream>
#include <limits>
#include <fstream>
#include <sstream>
#include "fileHandling.h"
using namespace std;

const string productsFile = "data/products.txt";


void saveProductData(int inventorySize, string productNames[], int productIds[], float prices[], int quantityInStock[]){
    ofstream ofile(productsFile);
    string productNameFixed;

    if (!ofile.is_open()) {
        cerr << "Failed to open " << productsFile << endl;
        return;
    }

    ofile << inventorySize << '\n';

    for(int i = 0; i < inventorySize; i++){
        for(int j = 0; j < productNames[i].length(); j++){
            if(productNames[i][j] == ' ') productNameFixed += '_';
            else productNameFixed += productNames[i][j];
        }

        ofile << productIds[i] << ',' << productNameFixed << ',' << prices[i] << ',' << quantityInStock[i] << '\n';
        productNameFixed = "";
    }

    ofile.close();
}

string getProductFields(int fieldNo){
    ifstream ifile(productsFile);
    string line, field, outString;

    if (!ifile.is_open()) {
        cerr << "Failed to open " << productsFile << endl;
    }

    ifile >> line;
    ifile.ignore(numeric_limits<streamsize>::max(), '\n'); 

    while(getline(ifile, line)){
        stringstream ss(line);
        int currentField = 1;

        while(getline(ss, field, ',')){
            if(currentField == fieldNo){
                outString += field + " ";
                break;
            }
            currentField++;
        }
    }

    ifile.close();
    return outString;
}

void loadProductRecords(int &inventorySize, string productNames[], int productIds[], float prices[], int quantityInStock[]){
    ifstream ifile(productsFile);
    string line;

    if (!ifile.is_open()) {
        cerr << "Failed to open " << productsFile << endl;
        return;
    }

    ifile >> inventorySize;
    ifile.ignore(numeric_limits<streamsize>::max(), '\n');

    for(int i = 0; i < inventorySize; i++){
        getline(ifile, line);

        stringstream ostring(line);
        string field;

        getline(ostring, field, ',');
        productIds[i] = stoi(field);

        getline(ostring, field, ',');
        for(int j = 0; j < field.length(); j++){
            if(field[j] == '_') field[j] = ' ';
        }
        productNames[i] = field;

        getline(ostring, field, ',');
        prices[i] = stof(field);

        getline(ostring, field);
        quantityInStock[i] = stoi(field);
    }

    ifile.close();
}
