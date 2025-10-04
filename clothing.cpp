#include "clothing.h"
#include "util.h"
#include <sstream>
#include <iomanip>

Clothing::Clothing(const std::string name, double price, int qty,
                   const std::string size, const std::string brand) :
    Product("clothing", name, price, qty),
    size_(size),
    brand_(brand)
{
}

std::set<std::string> Clothing::keywords() const {
    std::set<std::string> result = parseStringToWords(name_);
    std::set<std::string> brandWords = parseStringToWords(brand_);
    result = setUnion(result, brandWords);
    return result;
}

std::string Clothing::displayString() const {
    std::stringstream ss;
    ss << name_ << "\n"
       << "Size: " << size_ << " Brand: " << brand_ << "\n"
       << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Clothing::dump(std::ostream& os) const {
    Product::dump(os);
    os << size_ << "\n" << brand_ << std::endl;
}