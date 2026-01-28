#include <iostream>
#include <cstdlib> // Required for system()
#include <sstream>
#include "../include/convertingHtmlToPDF.h"

using namespace std;

void printBillToPdf(const string&htmlFilename, const string &pdfFilename) {
    // 1. Construct the command string
    // wkhtmltopdf [input_file.html] [output_file.pdf]
    
    // We can add options like '--page-width 80mm' for receipt style if wkhtmltopdf is compiled with patched qt
    // For standard version, keep it simple:
    stringstream command;
    command << "wkhtmltopdf " << htmlFilename << " " << pdfFilename;

    // cout << "Executing command: " << command.str() << endl;

    // 2. Execute the command
    // The system() function runs a command in the operating system's shell.
    int result = system(command.str().c_str());

    // 3. Check the result
    if (result == 0) {
        cout << "Successfully generated PDF: " << pdfFilename << endl;
    } else {
        cerr << "ERROR: PDF generation failed. (Exit code: " << result << "). Check if wkhtmltopdf is in your PATH." << endl;
    }
}