#ifndef CATEGORYINDEX_H
#define CATEGORYINDEX_H

#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include "Product.h"
#include "Hashtable.h"

template<typename K, typename V>
class CategoryIndex {
private:
    HashTable<K, std::vector<V>> index;

public:
    CategoryIndex(size_t initialCapacity = 10007) : index(initialCapacity) {}
    
    void addProduct(const K& category, const V& productId) {
        std::vector<V> products;
        if (index.find(category, products)) {
            // Check if product already exists to avoid duplicates
            if (std::find(products.begin(), products.end(), productId) == products.end()) {
                products.push_back(productId);
                index.insert(category, products);
            }
        } else {
            index.insert(category, std::vector<V>{productId});
        }
    }
    
    bool getProducts(const K& category, std::vector<V>& products) const {
        return index.find(category, products);
    }
    
    bool removeProduct(const K& category, const V& productId) {
        std::vector<V> products;
        if (index.find(category, products)) {
            auto it = std::find(products.begin(), products.end(), productId);
            if (it != products.end()) {
                products.erase(it);
                if (products.empty()) {
                    return index.remove(category);
                } else {
                    index.insert(category, products);
                    return true;
                }
            }
        }
        return false;
    }
    
    void clear() {
        index.clear();
    }
    
    size_t getCategoryCount() const {
        return index.getSize();
    }
    
    bool isEmpty() const {
        return index.isEmpty();
    }
    
    bool containsCategory(const K& category) const {
        return index.contains(category);
    }
    
    // Get all categories in the index
    std::vector<K> getAllCategories() const {
        return index.getKeys();
    }
    
    // Get total number of product-category associations
    size_t getTotalProductAssociations() const {
        size_t total = 0;
        auto categories = getAllCategories();
        for (const auto& category : categories) {
            std::vector<V> products;
            if (getProducts(category, products)) {
                total += products.size();
            }
        }
        return total;
    }
};

#endif