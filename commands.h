#pragma once
#include <fstream>
#include <sstream>
#include <regex>
#include "SalesItem.h"

bool regexCheck(std::string input)
{
    std::regex obj = std::regex("-?\\d+");
    return regex_match(input, obj);
}

std::unordered_map<std::string, std::vector<SalesItem>> parseSalesData(const std::string& filename) {
    std::unordered_map<std::string, std::vector<SalesItem>> invoiceData;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
        return invoiceData;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;

        std::string invoiceNo;
        std::string stockCode;
        std::string description;
        std::string quantityStr;
        std::string invoiceDate;
        std::string unitPriceStr;
        std::string customerIDStr;
        std::string country;
        std::string subCategory;

        std::getline(ss, invoiceNo, ',');
        std::getline(ss, stockCode, ',');
        std::getline(ss, description, ',');
        std::getline(ss, quantityStr, ',');
        if (description[0] == '"')
            while (!regexCheck(quantityStr))
            {
                description += " " + quantityStr;
                std::getline(ss, quantityStr, ',');
            }
        std::getline(ss, invoiceDate, ',');
        std::getline(ss, unitPriceStr, ',');
        std::getline(ss, customerIDStr, ',');
        std::getline(ss, country, ',');
        std::getline(ss, subCategory);

        int quantity = std::stoi(quantityStr);
        double unitPrice = std::stod(unitPriceStr);
        int customerID = 0; // Default value if field is empty or not present
        if (!customerIDStr.empty()) {
            customerID = std::stoi(customerIDStr);
        }
        SalesItem item(stockCode, description, quantity, invoiceDate, unitPrice, customerID, country, subCategory);
        invoiceData[invoiceNo].push_back(item);
    }

    file.close();
    return invoiceData;
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

void unifyPurchases()
{
    std::unordered_map<std::string, std::vector<SalesItem>> invoiceData = parseSalesData("Online_Retail_Data2.txt");
    std::unordered_map<std::string, std::unordered_map<std::string, int>> allInvoiceCat;
    for (auto i : invoiceData) //iterates through all the invoices
    {
        std::unordered_map<std::string, int> oneInvoiceCat;
        for (auto j : i.second)         // create a map count of items in each category for a single invoice
        {
            oneInvoiceCat[j.SubCategory]++;
        }
        allInvoiceCat[i.first] = oneInvoiceCat;     // push each count with the invoice number as key
    }
    // use invoice 536365 as an sample cart
    // create findDistance function to calculate "distance" (similarity) between example and all other invoices
    // compare sample cart and most similar other invoice. cart suggestion is missing item of least contrast.

    /*--------Print used for debugging---------
    int count = 0;
    while (count < 50)
    {
        for (auto i : allInvoiceCat)
        {
            for (auto j : i.second)
            {
                std::cout << i.first << " " << j.first << " " << j.second << std::endl;
            }
        }
        count++;
    }
    -----------------------*/
}

void exportResults()
{
    //Export Results
}
