#include "mydatastore.h"
#include "util.h"
#include <iostream>

MyDataStore::~MyDataStore() {
    for(unsigned int i = 0; i < products.size(); i++) {
        delete products[i];
    }
    for(std::map<std::string, User*>::iterator it = users.begin(); it != users.end(); ++it) {
        delete it->second;
    }
}

void MyDataStore::addProduct(Product* p) {
    products.push_back(p);
    std::set<std::string> kwords = p->keywords();
    for(std::set<std::string>::iterator it = kwords.begin(); it != kwords.end(); ++it) {
        keywordMap[*it].insert(p);
    }
}

void MyDataStore::addUser(User* u) {
    users[convToLower(u->getName())] = u;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::set<Product*> result;
    
    if(terms.empty()) {
        return std::vector<Product*>();
    }
    
    if(type == 0) {
        if(keywordMap.find(terms[0]) != keywordMap.end()) {
            result = keywordMap[terms[0]];
        }
        for(unsigned int i = 1; i < terms.size(); i++) {
            if(keywordMap.find(terms[i]) != keywordMap.end()) {
                result = setIntersection(result, keywordMap[terms[i]]);
            } else {
                result.clear();
                break;
            }
        }
    } else {
        for(unsigned int i = 0; i < terms.size(); i++) {
            if(keywordMap.find(terms[i]) != keywordMap.end()) {
                result = setUnion(result, keywordMap[terms[i]]);
            }
        }
    }
    
    return std::vector<Product*>(result.begin(), result.end());
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>" << std::endl;
    for(unsigned int i = 0; i < products.size(); i++) {
        products[i]->dump(ofile);
    }
    ofile << "</products>" << std::endl;
    ofile << "<users>" << std::endl;
    for(std::map<std::string, User*>::iterator it = users.begin(); it != users.end(); ++it) {
        it->second->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}

void MyDataStore::addToCart(std::string username, Product* p) {
    carts[convToLower(username)].push_back(p);
}

void MyDataStore::viewCart(std::string username) {
    User* u = getUser(username);
    if(u == NULL) {
        std::cout << "Invalid username" << std::endl;
        return;
    }
    
    std::deque<Product*>& cart = carts[convToLower(username)];
    for(unsigned int i = 0; i < cart.size(); i++) {
        std::cout << "Item " << (i+1) << std::endl;
        std::cout << cart[i]->displayString() << std::endl;
        std::cout << std::endl;
    }
}

void MyDataStore::buyCart(std::string username) {
    User* u = getUser(username);
    if(u == NULL) {
        std::cout << "Invalid username" << std::endl;
        return;
    }
    
    std::deque<Product*>& cart = carts[convToLower(username)];
    std::deque<Product*> remainingCart;
    
    for(unsigned int i = 0; i < cart.size(); i++) {
        Product* p = cart[i];
        if(p->getQty() > 0 && u->getBalance() >= p->getPrice()) {
            p->subtractQty(1);
            u->deductAmount(p->getPrice());
        } else {
            remainingCart.push_back(p);
        }
    }
    
    cart = remainingCart;
}

User* MyDataStore::getUser(std::string username) {
    std::string lowerName = convToLower(username);
    if(users.find(lowerName) != users.end()) {
        return users[lowerName];
    }
    return NULL;
}