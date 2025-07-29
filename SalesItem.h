#ifndef SALESITEM_H
#define SALESITEM_H
#include <string>


struct SalesItem {
    std::string StockCode;
    std::string Description;
    int Quantity;
    std::string InvoiceDate;
    double UnitPrice;
    int CustomerID;
    std::string Country;
    SalesItem(std::string sc = "", std::string desc = "", int qty = 0,
              std::string idate = "", double uprice = 0.0, int custid = 0,
              std::string country = "");
};



#endif //SALESITEM_H
