#include <iostream>
#include <cassert>
#include "Hashtable.h"
#include "Product.h"
#include "InventoryManager.h"

void testHashTable() {
    std::cout << "Testing HashTable..." << std::endl;
    
    HashTable<std::string, int> table;
    
    // Test insertion and finding
    table.insert("key1", 100);
    table.insert("key2", 200);
    table.insert("key3", 300);
    
    int value;
    assert(table.find("key1", value) && value == 100);
    assert(table.find("key2", value) && value == 200);
    assert(table.find("key3", value) && value == 300);
    assert(!table.find("key4", value));
    
    // Test updating existing key
    table.insert("key1", 150);
    assert(table.find("key1", value) && value == 150);
    
    // Test removal
    assert(table.remove("key2"));
    assert(!table.find("key2", value));
    assert(!table.remove("key2")); // Already removed
    
    // Test clear
    table.clear();
    assert(!table.find("key1", value));
    assert(!table.find("key3", value));
    
    std::cout << "All HashTable tests passed!" << std::endl;
}

void testProduct() {
    std::cout << "Testing Product class..." << std::endl;
    
    // Test category parsing
    std::vector<std::string> fields(25, "test");
    fields[4] = "Toys & Games | Learning & Education | Science Kits & Toys";
    
    Product product(fields);
    auto categories = product.getCategories();
    assert(categories.size() == 3);
    assert(categories[0] == "Toys & Games");
    assert(categories[1] == "Learning & Education");
    assert(categories[2] == "Science Kits & Toys");
    
    // Test empty category
    fields[4] = "";
    Product product2(fields);
    auto categories2 = product2.getCategories();
    assert(categories2.size() == 1);
    assert(categories2[0] == "NA");
    
    std::cout << "All Product tests passed!" << std::endl;
}

void testInventoryManager() {
    std::cout << "Testing InventoryManager..." << std::endl;
    
    InventoryManager manager;
    
    // Create test products
    std::vector<std::string> fields1(25, "test");
    fields1[0] = "test_id_1";
    fields1[1] = "Test Product 1";
    fields1[4] = "Category A|Category B";
    
    std::vector<std::string> fields2(25, "test");
    fields2[0] = "test_id_2";
    fields2[1] = "Test Product 2";
    fields2[4] = "Category A|Category C";
    
    Product p1(fields1);
    Product p2(fields2);
    
    manager.addProduct(p1);
    manager.addProduct(p2);
    
    // Test finding products
    Product found;
    assert(manager.findProduct("test_id_1", found));
    assert(found.getProductName() == "Test Product 1");
    
    assert(manager.findProduct("test_id_2", found));
    assert(found.getProductName() == "Test Product 2");
    
    assert(!manager.findProduct("nonexistent", found));
    
    // Test category indexing
    auto categoryAProducts = manager.getProductsByCategory("Category A");
    assert(categoryAProducts.size() == 2);
    
    auto categoryBProducts = manager.getProductsByCategory("Category B");
    assert(categoryBProducts.size() == 1);
    
    auto categoryDProducts = manager.getProductsByCategory("Category D");
    assert(categoryDProducts.empty());
    
    std::cout << "All InventoryManager tests passed!" << std::endl;
}

int main() {
    testHashTable();
    testProduct();
    testInventoryManager();
    
    std::cout << "\nAll tests completed successfully!" << std::endl;
    return 0;
}