#include "SalesItem.h"
#include <utility>
SalesItem::SalesItem(std::string sc, std::string desc, int qty,
                     std::string idate, double uprice, int custid,
                     std::string country)
    : StockCode(std::move(sc)),
      Description(std::move(desc)),
      Quantity(qty),
      InvoiceDate(std::move(idate)),
      UnitPrice(uprice),
      CustomerID(custid),
      Country(std::move(country))
{

}