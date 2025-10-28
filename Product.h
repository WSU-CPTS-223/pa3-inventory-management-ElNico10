#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>

class Product {
private:
    std::string uniqId;
    std::string productName;
    std::string brandName;
    std::string asin;
    std::vector<std::string> categories;
    std::string upcEanCode;
    std::string listPrice;
    std::string sellingPrice;
    std::string quantity;
    std::string modelNumber;
    std::string aboutProduct;
    std::string productSpecification;
    std::string technicalDetails;
    std::string shippingWeight;
    std::string productDimensions;
    std::string image;
    std::string variants;
    std::string sku;
    std::string productUrl;
    std::string stock;
    std::string productDetails;
    std::string dimensions;
    std::string color;
    std::string ingredients;
    std::string directionToUse;

public:
    Product();
    Product(const std::vector<std::string>& fields);
    
    // Getters
    std::string getUniqId() const { return uniqId; }
    std::string getProductName() const { return productName; }
    std::vector<std::string> getCategories() const { return categories; }
    
    // Display methods
    void display() const;
    void displayBasic() const;
    
    // Helper methods
    static std::vector<std::string> parseCategories(const std::string& categoryStr);
};

#endif