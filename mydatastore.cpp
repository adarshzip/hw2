#include <string>
#include <set>
#include <vector>
#include <iostream>
#include "mydatastore.h"
#include "util.h"

using namespace std; 

MyDataStore::MyDataStore() : DataStore() {

}


MyDataStore::~MyDataStore() {
    for (Product* p : products) {
        delete p;
    }

    for (User* u : users) {
        delete u;
    }
}


void MyDataStore::addProduct(Product* p){
    products.push_back(p);
    set<string> keywords = p->keywords(); 
    for (string keyword : keywords){
        if(searchMap.find(keyword) == searchMap.end()){
            searchMap.insert(make_pair(keyword, set<Product*>()));
        }
        searchMap[keyword].insert(p);
    }
}


void MyDataStore::addUser(User* u){
    users.push_back(u);
    cartMap.insert(make_pair(u->getName(), vector<Product*>()));
    userLookup.insert(make_pair(u->getName(), u));
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type){
    set<Product*> searchResults; 

    if(terms.empty()){
        return vector<Product*>();
    }

    if(searchMap.find(terms[0])!= searchMap.end()){
        searchResults = searchMap[terms[0]]; 
    }

    for (size_t i = 1; i < terms.size(); i++){
        set<Product*> termResults; 
        if(searchMap.find(terms[i])!= searchMap.end()){
            termResults = searchMap[terms[i]]; 
        }

        if(type == 0){ // AND search
            searchResults = setIntersection(searchResults, termResults);
        }
        else{
            searchResults = setUnion(searchResults, termResults); 
        }
    }

    return vector<Product*>(searchResults.begin(), searchResults.end());
}

void MyDataStore::dump(ostream& ofile){
    ofile << "<products>" << endl;
    for (Product* p : products) {
        p->dump(ofile);
    }
    ofile << "</products>" << endl;

    ofile << "<users>" << endl;
    for (User* u : users) {
        u->dump(ofile);
    }
    ofile << "</users>" << endl;
}

void MyDataStore::addToCart(vector<Product*> hits, string username, int hitNum){
    if(hitNum > hits.size() or hitNum < 1){ // too big/small hit
        cout << "Invalid Request" << endl;
        return;  
    }

    if(cartMap.find(username) == cartMap.end()){ // username not found
        cout << "Invalid Request" << endl;
        return;  
    }

    Product* prod = hits[hitNum - 1];
    cartMap[username].push_back(prod); 
}

void MyDataStore::viewCart(string username){
    if(cartMap.find(username) == cartMap.end()){ // username not found
        cout << "Invalid Username" << endl;
        return;  
    }

    vector<Product*> cart = cartMap[username]; 

    int idx = 1; 

    for(Product* p : cart){
        cout << "Item " << idx << endl << p->displayString() << endl; 
        idx += 1; 
    }
}

void MyDataStore::buyCart(string username){
    if(cartMap.find(username) == cartMap.end()){ // username not found
        cout << "Invalid Username" << endl;
        return;  
    }

    vector<Product*> cart = cartMap[username]; 
    vector<Product*> unboughtCart; 
    double userMoney = userLookup[username]->getBalance();
    for (Product* p : cart){
        if(p->getQty() == 0){
            unboughtCart.push_back(p); 
            continue;
        }
        else if(p->getPrice() > userMoney){
            unboughtCart.push_back(p); 
            continue;
        }
        else {
            p->subtractQty(1);
            userMoney -= p->getPrice();
            userLookup[username]->deductAmount(p->getPrice());
        }
    }

    cartMap[username] = unboughtCart; 
}