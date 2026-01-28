#include "../include/convertingToHtml.h"
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip> // For setprecision

using namespace std;

// Function to generate the HTML content for the receipt
string generateHtmlReceipt(float totalAmount, int inventoryLimit, string orderProductNames[], int orderProductsQuantity[],
                            float orderPrices[], int orderProductsCount, string customerName, string userName, const string& formattedDate) {
    // 1. Start HTML structure and styling (inline for simplicity)
    string htmlContent = R"(
<!DOCTYPE html>
<html>
<head>
    <title>ORDER RECEIPT</title>
    <style>
        body { font-family: monospace; font-size: 10pt; width: 300px; margin: 0 auto; padding: 20px; }
        .header, .footer { text-align: center; margin-bottom: 10px; }
        .items { width: 100%; border-collapse: collapse; margin-top: 10px; }
        .items th, .items td { border-top: 1px solid #ccc; padding: 5px 0; text-align: left; }
        .items th:nth-child(2), .items td:nth-child(2) { text-align: center; }
        .items th:nth-child(3), .items td:nth-child(3) { text-align: right; }
        .total { font-weight: bold; }
    </style>
</head>
<body>
    <div class="header">
        <h1 style="font-family: 'Arial', sans-serif;">Order Receipt</h1>
        <p>123 UET Main Campus, Lahore</p>
        <p>Date: )" + formattedDate + R"(</p>
    </div>
    
    <p>Customer: )" + customerName + R"(</p>
    <p>CSR: )" + userName + R"(</p>

    <table class="items">
        <thead>
            <tr>
                <th>Product</th>
                <th>Qty</th>
                <th>Price (Total)</th>
            </tr>
        </thead>
        <tbody>
)";

    // 2. Loop through products and add rows
    for (int i = 0; i < orderProductsCount; i++) {
        // Use a stringstream to handle floating point precision
        stringstream priceStream;
        priceStream << fixed << setprecision(2) << orderPrices[i];
        
        htmlContent += "<tr><td>" + orderProductNames[i] + "</td>";
        htmlContent += "<td>" + to_string(orderProductsQuantity[i]) + "</td>";
        htmlContent += "<td>$" + priceStream.str() + "</td></tr>";
    }

    // 3. Add Totals and close HTML
    stringstream totalStream;
    totalStream << fixed << setprecision(2) << totalAmount;
    
    htmlContent += R"(
        </tbody>
    </table>

    <hr>
    <p class="total" style="text-align: right;">GRAND TOTAL: $)" + totalStream.str() + R"(</p>

    <div class="footer">
        <p>Thank You For Your Business!</p>
    </div>
</body>
</html>
)";

    return htmlContent;
}

// Function to write the HTML content to a file
void writeHtmlFile(const string& filename, const string& content) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << content;
        outFile.close();
        // cout << "HTML receipt saved to " << filename << endl;
    } else {
        cerr << "ERROR: Could not write HTML file: " << filename << endl;
    }
}