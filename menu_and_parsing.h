#pragma once
#include "commands.h"
using namespace std;

void userInput();
void displayMenu();
bool regexCheck();
void commandParse(bool exit, string& command);
void goodbyeMessage();

void userInput()
{
    bool exit = false;
    displayMenu();
    string command;
    cin >> command;
    if (&regexCheck)
        commandParse(exit, command);
    else
    {
        cout << "Invalid Input: enter 1-8." << endl;
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
    "4. Score New Transaction\n"
    "5. Show Top-N Similar Transactions\n"
    "6. Visualize Success Patterns\n"
    "7. Export Results\n"
    "8. Exit\n"
    "\n"
    "Enter your choice [1-8]: ";
}

bool regexCheck()
{
    bool validInput = true;
    //insert regexCheck for invalid inputs
    return validInput;
}

void commandParse(bool exit, string &command)
{
    if (command == "1")
        loadTransactionData();
    else if (command == "2")
        vectorizeTransactions();
    else if (command == "3")
        buildSimilarityIndex();
    else if (command == "4")
        scoreNewTransaction();
    else if (command == "5")
        showSimilarTransactions();
    else if (command == "6")
        visualizeSuccessPatterns();
    else if (command == "7")
        exportResults();
    else if (command == "8")
    {
        exit = true;
    }
    if (!exit)
    {
        string exitString;
        cout << "Press Y to continue or any other key to exit: ";
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





