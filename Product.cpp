#include "Product.h"
#include <iostream>
#include <sstream>

Product::Product() {}

Product::Product(const std::vector<std::string>& fields) {
    if (fields.size() >= 24) {
        uniqId = fields[0];
        productName = fields[1];
        brandName = fields[2];
        asin = fields[3];
        categories = parseCategories(fields[4]);
        upcEanCode = fields[5];
        listPrice = fields[6];
        sellingPrice = fields[7];
        quantity = fields[8];
        modelNumber = fields[9];
        aboutProduct = fields[10];
        productSpecification = fields[11];
        technicalDetails = fields[12];
        shippingWeight = fields[13];
        productDimensions = fields[14];
        image = fields[15];
        variants = fields[16];
        sku = fields[17];
        productUrl = fields[18];
        stock = fields[19];
        productDetails = fields[20];
        dimensions = fields[21];
        color = fields[22];
        ingredients = fields[23];
        directionToUse = fields.size() > 24 ? fields[24] : "";
        
        // Debug first product
        static bool firstProduct = true;
        if (firstProduct && !uniqId.empty()) {
            std::cout << "DEBUG - First product details:" << std::endl;
            std::cout << "  ID: " << uniqId << std::endl;
            std::cout << "  Name: " << productName << std::endl;
            std::cout << "  Categories count: " << categories.size() << std::endl;
            for (const auto& cat : categories) {
                std::cout << "    - " << cat << std::endl;
            }
            firstProduct = false;
        }
    }
}

std::vector<std::string> Product::parseCategories(const std::string& categoryStr) {
    std::vector<std::string> result;
    
    // Handle empty or NA categories
    if (categoryStr.empty() || categoryStr == "NA" || categoryStr == "\"\"") {
        result.push_back("NA");
        return result;
    }
    
    std::string processedStr = categoryStr;
    
    // Remove surrounding quotes if present
    if (processedStr.size() >= 2 && processedStr[0] == '"' && processedStr[processedStr.size()-1] == '"') {
        processedStr = processedStr.substr(1, processedStr.size() - 2);
    }
    
    std::stringstream ss(processedStr);
    std::string category;
    
    while (std::getline(ss, category, '|')) {
        // Trim whitespace
        size_t start = category.find_first_not_of(" \t\r\n");
        size_t end = category.find_last_not_of(" \t\r\n");
        if (start != std::string::npos && end != std::string::npos) {
            std::string trimmed = category.substr(start, end - start + 1);
            if (!trimmed.empty()) {
                result.push_back(trimmed);
            }
        }
    }
    
    // If no categories found, use NA
    if (result.empty()) {
        result.push_back("NA");
    }
    
    return result;
}

void Product::display() const {
    std::cout << "Uniq Id: " << uniqId << std::endl;
    std::cout << "Product Name: " << productName << std::endl;
    std::cout << "Brand Name: " << brandName << std::endl;
    std::cout << "ASIN: " << asin << std::endl;
    
    std::cout << "Categories: ";
    for (size_t i = 0; i < categories.size(); ++i) {
        std::cout << categories[i];
        if (i < categories.size() - 1) std::cout << " | ";
    }
    std::cout << std::endl;
    
    std::cout << "List Price: " << listPrice << std::endl;
    std::cout << "Selling Price: " << sellingPrice << std::endl;
    std::cout << "Model Number: " << modelNumber << std::endl;
    std::cout << "Shipping Weight: " << shippingWeight << std::endl;
    std::cout << "Product Dimensions: " << productDimensions << std::endl;
}

void Product::displayBasic() const {
    std::cout << "ID: " << uniqId << " | Name: " << productName << std::endl;
}