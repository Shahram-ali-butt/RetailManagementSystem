// convertingToHtml.h

#ifndef CONVERTINGTOHTML_H
#define CONVERTINGTOHTML_H

#include <string>
// Include all necessary headers for types used in the function signatures

// Function declarations (prototypes)
std::string generateHtmlReceipt(float totalAmount, int inventoryLimit, std::string orderProductNames[], int orderProductsQuantity[],
                            float orderPrices[], int orderProductsCount, std::string customerName, std::string userName, const std::string& formattedDate);
void writeHtmlFile(const std::string& filename, const std::string& content);

#endif // CONVERTINGTOHTML_H