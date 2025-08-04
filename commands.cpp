#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
#include <cmath>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "commands.h"
#include <queue>
#include "SalesItem.h"

std::vector<std::string> subCategories = {
    "Home Decor", "Lighting", "Candles & Scents", "Baking & Cooking",
    "Toys", "Winter", "Storage & Organization", "Kids & Baby", "Vintage & Retro"
};
std::unordered_map<std::string, std::unordered_map<std::string, int>> allInvoiceCat;


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
    std::unordered_map<std::string, std::vector<SalesItem>> invoiceData = parseSalesData("Online_Retail_Data2.txt");

    allInvoiceCat.clear();

    for (const auto& invoicePair : invoiceData) {
        std::unordered_map<std::string, int> oneInvoiceCat;

        for (const auto& item : invoicePair.second) {
            oneInvoiceCat[item.SubCategory]++;
        }

        for (const auto& cat : subCategories) {
            if (oneInvoiceCat.find(cat) == oneInvoiceCat.end())
                oneInvoiceCat[cat] = 0;
        }

        allInvoiceCat[invoicePair.first] = oneInvoiceCat;
    }

    std::cout << "Similarity Index was successfully built using category count vectors." << std::endl;
}


void showSimilarTransactions()
{   // Preparation: Build Similarity Index if it does not exist yet
    if (allInvoiceCat.empty()) {
        buildSimilarityIndex();
    }

    std::string baseInvoice;
    std::cout << "Enter base invoice number (e.g., 536365): ";
    std::cin >> baseInvoice;

    int topN;
    std::cout << "How many similar transactions would you like to see? ";

    while (!(std::cin >> topN) || topN <= 0) {
        std::cout << "Please enter a valid positive number: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    // If the entered invoice does not exist
    if (allInvoiceCat.find(baseInvoice) == allInvoiceCat.end()) {
        std::cout << "Invoice " << baseInvoice << " not found in the dataset." << std::endl;
        return;
    }
    // Use a priority queue to store distances in ascending order.
    auto comp = [](const std::pair<double, std::string>& a,
                   const std::pair<double, std::string>& b) {
        return a.first > b.first;
    };

    std::priority_queue<
        std::pair<double, std::string>,
        std::vector<std::pair<double, std::string>>,
        decltype(comp)
    > minHeap(comp);
    // Distance calculation and insertion into heap
    for (const auto& pair : allInvoiceCat) {
        const std::string& invoiceID = pair.first;
        const auto& vec = pair.second;
        if (invoiceID == baseInvoice) continue;

        double dist = 0.0;
        for (const auto& cat : subCategories) {
            int diff = allInvoiceCat.at(baseInvoice).at(cat) - vec.at(cat);
            dist += diff * diff;
        }
        dist = std::sqrt(dist);

        minHeap.emplace(dist, invoiceID);
    }
    // Top-N Output
    std::cout << "[Top " << topN << " Similar Transactions using Min-Heap]" << std::endl;
    for (int i = 0; i < topN && !minHeap.empty(); ++i) {
        std::pair<double, std::string> top = minHeap.top();
        minHeap.pop();
        double dist = top.first;
        std::string id = top.second;
        std::cout << "Invoice: " << id
                  << " | Similarity Distance: " << dist << std::endl;
    }
}


std::vector <std::pair<int, std::string>> findSimilar(std::string& sampleInvoice, std::string& simInvoice, std::unordered_map<std::string, std::unordered_map<std::string, int>> allInvoiceCat)
{
    double simIndex = 1337.0;
    std::vector<int> cart;
    std::vector <int> rawDifferences;
    std::vector<std::pair<int, std::string>> simCart;
    for (auto i: subCategories)             // build the sample cart of subCategory weights
        cart.push_back(allInvoiceCat.find(sampleInvoice)->second.find(i)->second);
    for (auto i : allInvoiceCat)
    {
        if (i.first != sampleInvoice){
            double tempSimIndex = 0;
            for (int j = 0; j < subCategories.size(); j++)
            {   // push difference in weights to rawDifferences vector, square and add differences for Euclidean distance
                int tempDifference = cart[j] - i.second.find(subCategories[j])->second;
                rawDifferences.push_back(tempDifference);
                tempSimIndex += pow(tempDifference, 2);
            }
            tempSimIndex = sqrt(tempSimIndex);  //squareroot for Euclidean distance

            if (tempSimIndex < simIndex)
            {
                simIndex = tempSimIndex;
                simInvoice = i.first;           //return (by reference) *this invoice number as the most similar invoice
                simCart.clear();
                for (int j = 0; j < subCategories.size(); j++)
                    simCart.emplace_back(abs(rawDifferences[j]), subCategories[j]); //build most similar cart weights
            }
        }
    }
    sort(simCart.begin(), simCart.end());
    return simCart;
}

void unifyPurchases(std::string& sampleInvoice)
{
    // use invoice 536365 as an example cart
    // use findSimilar function to calculate "distance" (similarity) between example Cart and all other invoices, return simCart vector.
    // simCart vector is sorted by most similar Category to least. cart suggestion is missing item of least contrast.
    std::unordered_map<std::string, std::vector<SalesItem>> invoiceData = parseSalesData("Online_Retail_Data2.txt");

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
    std::vector <std::pair<int, std::string>> simCart = findSimilar(sampleInvoice, simInvoice, allInvoiceCat);
    std::vector <std::string> stockCodeInCart;      //create a vector of stockCodes from the example cart
    std::vector <std::string> addToCart;
    for (auto i : invoiceData.find(sampleInvoice)->second)
        stockCodeInCart.push_back(i.StockCode);
    for (auto i : simCart)          //iterate through simInvoice starting with simCart[0] to find whether there are items to suggest
        {
            for (auto j : invoiceData.find(simInvoice)->second)
                {
                    if (std::find(stockCodeInCart.begin(), stockCodeInCart.end(), j.StockCode) == stockCodeInCart.end())
                    {
                        if (std::find(addToCart.begin(), addToCart.end(), j.StockCode + " " + j.Description) == addToCart.end()) //rejects if already suggested
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

}
