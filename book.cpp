#include <sstream>
#include <iomanip>
#include <string>
#include "book.h"
#include "util.h"

using namespace std; 

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author) : 
    Product(category, name, price, qty), 
    isbn_(isbn),
    author_(author)
    { 
}; 


Book::~Book(){

}


set<string> Book::keywords() const {
    string keywordCombo = name_ + " " + author_;
    set<string> keywordReturn =  parseStringToWords(keywordCombo);
    keywordReturn.insert(isbn_);

    return keywordReturn;
}

string Book::displayString() const {
    string retVal = name_ + "\nAuthor: " + author_ + "\t ISBN: " + isbn_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left";

    return retVal;
}

void Book::dump(ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ <<  "\n" << isbn_ << "\n" << author_ << endl;
}

string Book::getAuthor() const {
    return author_;
}

string Book::getISBN() const {
    return isbn_;
}