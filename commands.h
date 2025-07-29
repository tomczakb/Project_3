#pragma once
#include <fstream>
#include <sstream>
#include "SalesItem.h"

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

        std::getline(ss, invoiceNo, ',');
        std::getline(ss, stockCode, ',');
        std::getline(ss, description, ',');
        std::getline(ss, quantityStr, ',');
        std::getline(ss, invoiceDate, ',');
        std::getline(ss, unitPriceStr, ',');
        std::getline(ss, customerIDStr, ',');
        std::getline(ss, country);

        int quantity = std::stoi(quantityStr);
        double unitPrice = std::stod(unitPriceStr);
        int customerID = 0; // Default value if field is empty or not present
        if (!customerIDStr.empty()) {
            customerID = std::stoi(customerIDStr);
        }

        SalesItem item(stockCode, description, quantity, invoiceDate, unitPrice, customerID, country);

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

void exportResults()
{
    //Export Results
}
