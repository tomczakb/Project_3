#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "SalesItem.h"

extern std::vector<std::string> subCategories;
extern std::unordered_map<std::string, std::unordered_map<std::string, int>> allInvoiceCat;
bool regexCheck(std::string input);
std::unordered_map<std::string, std::vector<SalesItem>> parseSalesData(const std::string& filename);
std::unordered_map<std::string, std::unordered_map<std::string, int>> buildCoPurchaseGraph(
    const std::unordered_map<std::string, std::vector<SalesItem>>& invoiceData);
std::vector<std::string> longestCoPurchaseSimplePath(
    const std::string& startItem,
    const std::unordered_map<std::string, std::unordered_map<std::string, int>>& graph);
void buildSimilarityIndex();
void scoreNewTransaction();
void showSimilarTransactions();
void visualizeSuccessPatterns();
std::vector<std::pair<int, std::string>> findSimilar(
    std::string& simInvoice,
    std::unordered_map<std::string, std::unordered_map<std::string, int>> allInvoiceCat);
void unifyPurchases();
void exportResults();