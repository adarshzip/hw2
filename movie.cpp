#include <sstream>
#include <iomanip>
#include <string>
#include "movie.h"
#include "util.h"

using namespace std; 

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) : 
    Product(category, name, price, qty), 
    genre_(genre),
    rating_(rating)
    { 
}; 


 Movie::~Movie(){

}


set<string> Movie::keywords() const {
    string keywordCombo = name_;
    set<string> keywordReturn =  parseStringToWords(keywordCombo);

    keywordReturn.insert(convToLower(genre_));

    return keywordReturn;
}

string Movie::displayString() const {
    string retVal = name_ + "\nGenre: " + genre_ + "\t Rating: " + rating_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left";

    return retVal;
}

void Movie::dump(ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ <<  "\n" << genre_ << "\n" << rating_ << endl;
}

string Movie::getGenre() const {
    return genre_;
}

string Movie::getRating() const {
    return rating_;
}