#pragma once
#include <fstream>
#include <sstream>
using namespace std;

void loadTransactionData()
{
    ifstream file("Online_Retail_Data.txt");
    string header;
    string line;
    if (file.is_open())
        cout << "File opened successfully." << endl;
    getline(file, header);              // Burn the headers
    cout << "Headers are: " << endl;
    cout << header << endl;

    while (getline(file, line))
    {
        //create cout or comment out to manage data in other functions
    }
}

void vectorizeTransactions()
{
    //Vectorize Transactions
}

void buildSimilarityIndex()
{
    //Build Similarity Inext
}

void scoreNewTransaction()
{
    //Score New Transaction
}

void showSimilarTransactions()
{
    //Show Top-N Similar Transactions
}

void visualizeSuccessPatterns()
{
    //Visualize Success Patterns
}

void exportResults()
{
    //Export Results
}
