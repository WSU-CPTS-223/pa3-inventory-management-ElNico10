#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <algorithm>
#include "Product.h"

template<typename K, typename V>
class HashNode {
public:
    K key;
    V value;
    HashNode* next;
    
    HashNode(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
};

template<typename K, typename V>
class HashTable {
private:
    std::vector<HashNode<K, V>*> table;
    size_t capacity;
    size_t size;
    
    size_t hash(const K& key) const {
        return std::hash<K>{}(key) % capacity;
    }
    
    void rehash() {
        size_t oldCapacity = capacity;
        capacity *= 2;
        std::vector<HashNode<K, V>*> oldTable = table;
        table = std::vector<HashNode<K, V>*>(capacity, nullptr);
        size = 0;
        
        for (size_t i = 0; i < oldCapacity; ++i) {
            HashNode<K, V>* node = oldTable[i];
            while (node != nullptr) {
                insert(node->key, node->value);
                HashNode<K, V>* temp = node;
                node = node->next;
                delete temp;
            }
        }
    }

public:
    HashTable(size_t initialCapacity = 10007) : capacity(initialCapacity), size(0) {
        table.resize(capacity, nullptr);
    }
    
    // Copy constructor
    HashTable(const HashTable& other) : capacity(other.capacity), size(0) {
        table.resize(capacity, nullptr);
        for (size_t i = 0; i < other.capacity; ++i) {
            HashNode<K, V>* node = other.table[i];
            while (node != nullptr) {
                insert(node->key, node->value);
                node = node->next;
            }
        }
    }
    
    // Assignment operator
    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            clear();
            capacity = other.capacity;
            table.resize(capacity, nullptr);
            for (size_t i = 0; i < other.capacity; ++i) {
                HashNode<K, V>* node = other.table[i];
                while (node != nullptr) {
                    insert(node->key, node->value);
                    node = node->next;
                }
            }
        }
        return *this;
    }
    
    ~HashTable() {
        clear();
    }
    
    void insert(const K& key, const V& value) {
        if (static_cast<double>(size) / capacity > 0.7) {
            rehash();
        }
        
        size_t index = hash(key);
        HashNode<K, V>* node = table[index];
        HashNode<K, V>* prev = nullptr;
        
        // Check if key already exists
        while (node != nullptr) {
            if (node->key == key) {
                node->value = value; // Update existing
                return;
            }
            prev = node;
            node = node->next;
        }
        
        // Insert new node
        HashNode<K, V>* newNode = new HashNode<K, V>(key, value);
        if (prev == nullptr) {
            table[index] = newNode;
        } else {
            prev->next = newNode;
        }
        size++;
    }
    
    bool find(const K& key, V& value) const {
        size_t index = hash(key);
        HashNode<K, V>* node = table[index];
        
        while (node != nullptr) {
            if (node->key == key) {
                value = node->value;
                return true;
            }
            node = node->next;
        }
        return false;
    }
    
    bool contains(const K& key) const {
        V value;
        return find(key, value);
    }
    
    bool remove(const K& key) {
        size_t index = hash(key);
        HashNode<K, V>* node = table[index];
        HashNode<K, V>* prev = nullptr;
        
        while (node != nullptr) {
            if (node->key == key) {
                if (prev == nullptr) {
                    table[index] = node->next;
                } else {
                    prev->next = node->next;
                }
                delete node;
                size--;
                return true;
            }
            prev = node;
            node = node->next;
        }
        return false;
    }
    
    void clear() {
        for (size_t i = 0; i < capacity; ++i) {
            HashNode<K, V>* node = table[i];
            while (node != nullptr) {
                HashNode<K, V>* temp = node;
                node = node->next;
                delete temp;
            }
            table[i] = nullptr;
        }
        size = 0;
    }
    
    bool isEmpty() const {
        return size == 0;
    }
    
    size_t getSize() const { return size; }
    size_t getCapacity() const { return capacity; }
    
    // Get all keys in the hash table
    std::vector<K> getKeys() const {
        std::vector<K> keys;
        for (size_t i = 0; i < capacity; ++i) {
            HashNode<K, V>* node = table[i];
            while (node != nullptr) {
                keys.push_back(node->key);
                node = node->next;
            }
        }
        return keys;
    }
    
    // For testing and debugging
    void displayStats() const {
        std::cout << "HashTable Stats: Size=" << size << ", Capacity=" << capacity 
                  << ", Load Factor=" << (static_cast<double>(size) / capacity) << std::endl;
        
        size_t maxChain = 0;
        size_t emptyBuckets = 0;
        
        for (size_t i = 0; i < capacity; ++i) {
            size_t chainLength = 0;
            HashNode<K, V>* node = table[i];
            while (node != nullptr) {
                chainLength++;
                node = node->next;
            }
            if (chainLength == 0) emptyBuckets++;
            if (chainLength > maxChain) maxChain = chainLength;
        }
        
        std::cout << "Longest Chain: " << maxChain << ", Empty Buckets: " << emptyBuckets << std::endl;
    }
};

#endif