#pragma once
#include <regex>

#include "commands.h"
using namespace std;

void userInput();
void displayMenu();
void commandParse(string& command);
void goodbyeMessage();

void userInput()
{
    displayMenu();
    string command;
    cin >> command;
    if (regex_match(command, std::regex("[1-6]")))
        commandParse(command);
    else {
        cout << "Invalid Input: enter 1-6." << endl;
        cout << "" << endl;
        userInput();
    }
}

void displayMenu()
{
    cout <<
"        _        ," << endl <<
"(_\\______/________" << endl <<
"  \\-|-|/|-|-|-|-|/" << endl <<
"   \\==/-|-|-|-|-/ " << endl <<
"    \\/|-|-|-|,-' " << endl <<
"     \\--|-'''    " << endl <<
"      \\_j________" << endl <<
"      (_)     (_) " << endl <<
"\n"
    "===========================================\n"
    "        Welcome To Reliable Retail\n"
    "===========================================\n"
    "\n"
    "    Select an option:\n"
    "\n"
    "1. Load Transaction Data\n"
    "2. Vectorize Transactions\n"
    "3. Build Similarity Index\n"
    "4. Show Top-N Similar Transactions\n"
    "5. Unify Purchases\n"
    "6. Exit\n"
    "\n"
    "Enter your choice [1-6]: ";
}

void commandParse(string& command)
{
    bool exit = false;
    static std::unordered_map<std::string, std::vector<SalesItem>> invoiceData;

    if (command == "1")
    {
        invoiceData = parseSalesData("Online_Retail_Data2.txt");
    }
    else if (command == "2")
    {
        std::unordered_map<std::string, std::unordered_map<std::string, int>> graph = buildCoPurchaseGraph(invoiceData);
        longestCoPurchaseSimplePath(graph);
    }
    else if (command == "3")
        buildSimilarityIndex();
    else if (command == "4")
        showSimilarTransactions();
    else if (command == "5")
    {
        cout << "Choose an invoice number for the sample cart:\n"
        "536520\n"
        "536522\n"
        "536535\n"
        "Enter your selection here: ";
        string sampleInvoice;
        cin >> sampleInvoice;
        unifyPurchases(sampleInvoice);
    }
    else if (command == "6")
    {
        exit = true;
    }
    if (!exit)
    {
        string exitString;
        cout << "Press [Y] to continue or any other key to exit: ";
        cin >> exitString;
        if (exitString != "Y" && exitString != "y")
            exit = true;
    }
    if (exit)
        goodbyeMessage();
    else
        userInput();
}

void goodbyeMessage()
{
    cout << "Thank you for using Reliable Retail!" << endl;
    cout << "Goodbye!" << endl;
}





