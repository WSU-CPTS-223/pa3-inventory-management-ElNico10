#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include "Hashtable.h"
#include "CategoryIndex.h"
#include "Product.h"
#include <string>
#include <vector>

class InventoryManager {
private:
    HashTable<std::string, Product> productTable;
    CategoryIndex<std::string, std::string> categoryIndex;
    
public:
    InventoryManager() : productTable(10007), categoryIndex(10007) {}
    
    bool loadFromCSV(const std::string& filename);
    void addProduct(const Product& product);
    bool findProduct(const std::string& uniqId, Product& product) const;
    std::vector<std::string> getProductsByCategory(const std::string& category) const;
    void displayProduct(const std::string& uniqId) const;
    void listCategoryProducts(const std::string& category) const;
    
    // Proper statistics and management methods
    size_t getProductCount() const { return productTable.getSize(); }
    size_t getCategoryCount() const { return categoryIndex.getCategoryCount(); }
    size_t getTotalCategoryAssociations() const { return categoryIndex.getTotalProductAssociations(); }
    
    bool containsProduct(const std::string& uniqId) const {
        Product product;
        return productTable.find(uniqId, product);
    }
    
    bool containsCategory(const std::string& category) const {
        return categoryIndex.containsCategory(category);
    }
    
    std::vector<std::string> getAllCategories() const {
        return categoryIndex.getAllCategories();
    }
    
    void removeProduct(const std::string& uniqId) {
        Product product;
        if (productTable.find(uniqId, product)) {
            // Remove from category index first
            auto categories = product.getCategories();
            for (const auto& category : categories) {
                categoryIndex.removeProduct(category, uniqId);
            }
            // Then remove from product table
            productTable.remove(uniqId);
        }
    }
    
    void clear() {
        productTable.clear();
        categoryIndex.clear();
    }
    
    bool isEmpty() const {
        return productTable.isEmpty();
    }
    
    void displayStats() const;
    void debugCategories() const;
};

#endif