#include <sstream>
#include <iomanip>
#include <string>
#include "clothing.h"
#include "util.h"

using namespace std; 

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) : 
    Product(category, name, price, qty), 
    size_(size),
    brand_(brand)
    { 
}; 


Clothing::~Clothing(){

}


set<string> Clothing::keywords() const {
    string keywordCombo = name_ + " " + brand_;
    set<string> keywordReturn =  parseStringToWords(keywordCombo);

    return keywordReturn;
}

string Clothing::displayString() const {
    string retVal = name_ + "\nSize: " + size_ + "\t Brand: " + brand_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left";

    return retVal;
}

void Clothing::dump(ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ <<  "\n" << size_ << "\n" << brand_ << endl;
}

string Clothing::getSize() const {
    return size_;
}

string Clothing::getBrand() const {
    return brand_;
}