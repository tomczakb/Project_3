#pragma once
#include <fstream>
#include <sstream>
#include <regex>
#include <cmath>
#include <vector>
#include <algorithm>
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

std::unordered_map<std::string, std::unordered_map<std::string, int>> buildCoPurchaseGraph(const std::unordered_map<std::string, std::vector<SalesItem>>& invoiceData) {
    std::unordered_map<std::string, std::unordered_map<std::string, int>> graph;

    for (const auto& pair : invoiceData) {
        const std::vector<SalesItem>& items = pair.second;
        std::unordered_set<std::string> uniqueStockCodes;
        for (const auto& item : items) {
            uniqueStockCodes.insert(item.StockCode);
        }

        std::vector<std::string> stockCodesVec(uniqueStockCodes.begin(), uniqueStockCodes.end());

        for (size_t i = 0; i < stockCodesVec.size(); ++i) {
            for (size_t j = i + 1; j < stockCodesVec.size(); ++j) {
                const std::string& item1 = stockCodesVec[i];
                const std::string& item2 = stockCodesVec[j];

                graph[item1][item2]++;
                graph[item2][item1]++;
            }
        }
    }

    return graph;
}

std::vector<std::string> longestCoPurchaseSimplePath(const std::string& startItem, const std::unordered_map<std::string, std::unordered_map<std::string, int>>& graph) {
    std::vector<std::string> path;
    if (graph.find(startItem) == graph.end()) {
        return path;
    }

    std::unordered_set<std::string> visited;
    std::string currentItem = startItem;
    path.push_back(currentItem);
    visited.insert(currentItem);

    while (true) {
        const auto& neighbors = graph.at(currentItem);
        std::string nextItem = "";
        int maxWeight = 0;

        for (const auto& neighbor_pair : neighbors) {
            const std::string& neighbor = neighbor_pair.first;
            int weight = neighbor_pair.second;

            if (visited.find(neighbor) == visited.end() && weight > maxWeight) {
                maxWeight = weight;
                nextItem = neighbor;
            }
        }

        if (nextItem.empty()) {
            break;
        }

        currentItem = nextItem;
        path.push_back(currentItem);
        visited.insert(currentItem);
    }

    return path;
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


std::vector <std::pair<int, std::string>> findSimilar(std::string& simInvoice, std::unordered_map<std::string, std::unordered_map<std::string, int>> allInvoiceCat)
{
    double simIndex = 1337.0;
    std::vector<int> cart;
    std::vector<std::pair<int, std::string>> simCart;
    cart.push_back(allInvoiceCat.find("536365")->second.find("Home Decor")->second);
    cart.push_back(allInvoiceCat.find("536365")->second.find("Lighting")->second);
    cart.push_back(allInvoiceCat.find("536365")->second.find("Candles & Scents")->second);
    cart.push_back(allInvoiceCat.find("536365")->second.find("Baking & Cooking")->second);
    cart.push_back(allInvoiceCat.find("536365")->second.find("Toys")->second);
    cart.push_back(allInvoiceCat.find("536365")->second.find("Winter")->second);
    cart.push_back(allInvoiceCat.find("536365")->second.find("Storage & Organization")->second);
    cart.push_back(allInvoiceCat.find("536365")->second.find("Kids & Baby")->second);
    cart.push_back(allInvoiceCat.find("536365")->second.find("Vintage & Retro")->second);
    for (auto i : allInvoiceCat)
    {
        //instantiate variables in tempBR etc for each invoice and compare "distance"
        int tempHome = cart[0]-i.second.find("Home Decor")->second;
        int tempLight = cart[1]-i.second.find("Lighting")->second;
        int tempCandles = cart[2]-i.second.find("Candles & Scents")->second;
        int tempBaking = cart[3]-i.second.find("Baking & Cooking")->second;
        int tempToys = cart[4]-i.second.find("Toys")->second;
        int tempWinter = cart[5]-i.second.find("Winter")->second;
        int tempStor = cart[6]-i.second.find("Storage & Organization")->second;
        int tempKids = cart[7]-i.second.find("Kids & Baby")->second;\
        int tempVint = cart[8]-i.second.find("Vintage & Retro")->second;

        double tempSimIndex = sqrt(abs(pow(tempHome, 2) + pow(tempLight, 2) + pow(tempCandles, 2) +
            pow(tempBaking, 2)+ pow(tempToys,2) + pow(tempWinter, 2) + pow(tempStor, 2) +
            pow(tempKids, 2) + pow(tempVint, 2)));
        if (tempSimIndex < simIndex)
        {
            simIndex = tempSimIndex;
            simInvoice = i.first;
            simCart.emplace_back(tempHome, "Home Decor");
            simCart.emplace_back(tempLight, "Lighting");
            simCart.emplace_back(tempCandles, "Candles & Scents");
            simCart.emplace_back(tempBaking, "Baking & Cooking");
            simCart.emplace_back(tempToys, "Toys");
            simCart.emplace_back(tempWinter, "Winter");
            simCart.emplace_back(tempStor, "Storage & Organization");
            simCart.emplace_back(tempKids, "Kids & Baby");
            simCart.emplace_back(tempVint, "Vintage & Retro");
        }
    }
    sort(simCart.begin(), simCart.end());
    return simCart;
}

void unifyPurchases()
{
    // use invoice 536365 as an example cart
    // use findSimilar function to calculate "distance" (similarity) between example Cart and all other invoices, return simCart vector.
    // simCart vector is sorted by most similar Category to least. cart suggestion is missing item of least contrast.
    std::unordered_map<std::string, std::vector<SalesItem>> invoiceData = parseSalesData("Online_Retail_Data2.txt");
    std::unordered_map<std::string, std::unordered_map<std::string, int>> allInvoiceCat;
    std::vector<std::string> subCategories {"Home Decor", "Lighting", "Candles & Scents",  "Baking & Cooking",
        "Toys",  "Winter",  "Storage & Organization", "Kids & Baby", "Vintage & Retro"};
    for (auto i : invoiceData) //iterates through all the invoices
    {
        std::unordered_map<std::string, int> oneInvoiceCat;
        for (auto j : i.second)         // create a map count of items in each SubCategory for a single invoice
        {
            oneInvoiceCat[j.SubCategory]++;
        }
        for (auto j : subCategories)    // for vector of subcategories, if subcategory not found, pushback oneInvoiceCat[i]=0;
        {
            if (oneInvoiceCat.find(j) == oneInvoiceCat.end())
                oneInvoiceCat[j] = 0;
        }
        allInvoiceCat[i.first] = oneInvoiceCat;     // push each count with the invoice number as key
    }
    std::string simInvoice;
    std::vector <std::pair<int, std::string>> simCart = findSimilar(simInvoice, allInvoiceCat);
    std::vector <std::string> stockCodeInCart;      //create a vector of stockCodes from the example cart
    std::vector <std::string> addToCart;
    for (auto i : invoiceData.find("536535")->second)
    {
        stockCodeInCart.push_back(i.StockCode);
    }
    for (auto i : simCart)          //iterate through simInvoice starting with simCart[0] to find whether there are items to suggest
        {
            for (auto j : invoiceData.find(simInvoice)->second)
                {
                    if (std::find(stockCodeInCart.begin(), stockCodeInCart.end(), j.StockCode) == stockCodeInCart.end())
                    {
                        if (std::find(addToCart.begin(), addToCart.end(), j.StockCode + " " + j.Description) == addToCart.end())
                        {
                            addToCart.push_back(j.StockCode + " " + j.Description);
                        }
                    }
                }
        }
    std::cout << "\nOther customers with similar carts also ordered the follow items:" << std::endl;
    if (addToCart.size() > 3)
        for (int i = 0; i < 3; i++)
            std::cout << addToCart[i] << std::endl;
    else
        for (auto i : addToCart)
            std::cout << i << std::endl;
    if (addToCart.size() > 1)
        std::cout << "These may be useful additions to your cart.\n" << std::endl;
    else
        std::cout << "This may be a useful addition to your cart.\n" << std::endl;

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
