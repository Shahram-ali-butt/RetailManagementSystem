#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include <string>

void saveProductData(int inventorySize, std::string productNames[], int productIds[], float prices[], int quantityInStock[]);
std::string getProductFields(int fieldNo);
void loadProductRecords(int &inventorySize, std::string productNames[], int productIds[], float prices[], int quantityInStock[]);

#endif 