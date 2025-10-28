#include "InventoryManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

bool InventoryManager::loadFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }
    
    std::string line;
    // Skip header line
    if (!std::getline(file, line)) {
        std::cerr << "Error: Empty file or cannot read header" << std::endl;
        return false;
    }
    
    std::cout << "CSV format detected: Comma-delimited with quoted fields" << std::endl;
    
    size_t lineCount = 0;
    size_t successCount = 0;
    size_t naCategoryCount = 0;
    
    while (std::getline(file, line)) {
        lineCount++;
        
        // Skip empty lines
        if (line.empty()) continue;
        
        std::vector<std::string> fields;
        std::string field;
        bool inQuotes = false;
        char quoteChar = '"';
        char delimiter = ',';
        
        // Parse CSV line with proper quote handling
        for (size_t i = 0; i < line.length(); ++i) {
            char c = line[i];
            
            if (c == quoteChar) {
                // Handle escaped quotes (two consecutive quotes)
                if (inQuotes && i + 1 < line.length() && line[i + 1] == quoteChar) {
                    field += quoteChar;
                    i++; // Skip the next quote
                } else {
                    inQuotes = !inQuotes;
                }
            } else if (c == delimiter && !inQuotes) {
                fields.push_back(field);
                field.clear();
            } else {
                field += c;
            }
        }
        fields.push_back(field); // Add the last field
        
        // We need at least the first 5 fields for a valid product
        if (fields.size() >= 5) {
            Product product(fields);
            
            // Check if product was created successfully (has an ID)
            if (!product.getUniqId().empty()) {
                addProduct(product);
                successCount++;
                
                // Count NA categories
                auto categories = product.getCategories();
                for (const auto& cat : categories) {
                    if (cat == "NA") {
                        naCategoryCount++;
                    }
                }
            }
        }
        
        if (lineCount % 1000 == 0) {
            std::cout << "Processed " << lineCount << " lines, " << successCount << " successful products..." << std::endl;
        }
    }
    
    file.close();
    std::cout << "Final result: Processed " << lineCount << " lines, successfully loaded " << successCount << " products." << std::endl;
    std::cout << "Products with NA category: " << naCategoryCount << std::endl;
    
    if (successCount == 0) {
        std::cout << "ERROR: No products were loaded!" << std::endl;
        return false;
    }
    
    return true;
}

void InventoryManager::addProduct(const Product& product) {
    productTable.insert(product.getUniqId(), product);
    
    // Index by categories
    std::vector<std::string> categories = product.getCategories();
    for (const auto& category : categories) {
        if (!category.empty()) {
            categoryIndex.addProduct(category, product.getUniqId());
        }
    }
}

bool InventoryManager::findProduct(const std::string& uniqId, Product& product) const {
    return productTable.find(uniqId, product);
}

std::vector<std::string> InventoryManager::getProductsByCategory(const std::string& category) const {
    std::vector<std::string> products;
    categoryIndex.getProducts(category, products);
    return products;
}

void InventoryManager::displayProduct(const std::string& uniqId) const {
    Product product;
    if (findProduct(uniqId, product)) {
        product.display();
    } else {
        std::cout << "Inventory/Product not found" << std::endl;
    }
}

void InventoryManager::listCategoryProducts(const std::string& category) const {
    std::vector<std::string> productIds = getProductsByCategory(category);
    if (productIds.empty()) {
        std::cout << "Invalid Category: '" << category << "'" << std::endl;
        std::cout << "Note: Category names are case-sensitive and must match exactly." << std::endl;
        return;
    }
    
    std::cout << "Found " << productIds.size() << " products in category '" << category << "':" << std::endl;
    for (const auto& id : productIds) {
        Product product;
        if (findProduct(id, product)) {
            product.displayBasic();
        }
    }
}

void InventoryManager::displayStats() const {
    std::cout << "=== Inventory Manager Statistics ===" << std::endl;
    std::cout << "Total products: " << getProductCount() << std::endl;
    std::cout << "Total categories: " << getCategoryCount() << std::endl;
    std::cout << "Total category associations: " << getTotalCategoryAssociations() << std::endl;
    productTable.displayStats();
}

void InventoryManager::debugCategories() const {
    std::cout << "=== Category Debug Info ===" << std::endl;
    auto categories = getAllCategories();
    std::cout << "Total categories found: " << categories.size() << std::endl;
    
    // Show top 10 categories by product count
    std::vector<std::pair<std::string, size_t>> categoryCounts;
    for (const auto& category : categories) {
        auto products = getProductsByCategory(category);
        categoryCounts.push_back(std::make_pair(category, products.size()));
    }
    
    // Sort by product count (descending) - C++11 compatible lambda
    std::sort(categoryCounts.begin(), categoryCounts.end(),
              [](const std::pair<std::string, size_t>& a, const std::pair<std::string, size_t>& b) { 
                  return b.second < a.second; 
              });
    
    std::cout << "Top 10 categories by product count:" << std::endl;
    for (size_t i = 0; i < std::min(categoryCounts.size(), size_t(10)); i++) {
        std::cout << "  " << categoryCounts[i].first << ": " << categoryCounts[i].second << " products" << std::endl;
    }
}