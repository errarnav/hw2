#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <map>
#include <vector>
#include <deque>

class MyDataStore : public DataStore {
public:
    ~MyDataStore();
    
    bool isValidUser(std::string username);
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    
    void addToCart(std::string username, Product* p);
    void viewCart(std::string username);
    void buyCart(std::string username);

private:
    std::map<std::string, std::set<Product*>> keywordMap;
    std::vector<Product*> products;
    std::map<std::string, User*> users;
    std::map<std::string, std::deque<Product*>> carts;
    
    User* getUser(std::string username);
};

#endif