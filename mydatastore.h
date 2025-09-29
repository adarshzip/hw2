#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include "datastore.h"

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();
    void addProduct(Product* p);
    void addUser (User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    void addToCart(std::vector<Product*> hits, std::string username, int hitNum);
    void viewCart(std::string username);
    void buyCart(std::string username);
private:
    std::vector<User*> users; 
    std::vector<Product*> products; 
    std::map<std::string, User*> userLookup;
    std::map<std::string, std::vector<Product*>> cartMap;
    std::map<std::string, std::set<Product*>> searchMap; 
};
#endif