#include <iostream>
#include <string>
#include "InventoryManager.h"

using namespace std;

InventoryManager inventoryManager;

void printHelp()
{
    cout << "Supported list of commands: " << endl;
    cout << " 1. find <inventoryid> - Finds if the inventory exists. If exists, prints details. If not, prints 'Inventory not found'." << endl;
    cout << " 2. listInventory <category_string> - Lists just the id and name of all inventory belonging to the specified category. If the category doesn't exists, prints 'Invalid Category'.\n"
         << endl;
    cout << " Use :quit to quit the REPL" << endl;
}

bool validCommand(string line)
{
    return (line == ":help") ||
           (line.rfind("find", 0) == 0) ||
           (line.rfind("listInventory", 0) == 0);
}

void evalCommand(string line)
{
    if (line == ":help")
    {
        printHelp();
    }
    // if line starts with find
    else if (line.rfind("find", 0) == 0)
    {
        string inventoryId = line.substr(5); // Remove "find "
        inventoryManager.displayProduct(inventoryId);
    }
    // if line starts with listInventory
    else if (line.rfind("listInventory", 0) == 0)
    {
        string category = line.substr(14); // Remove "listInventory "
        inventoryManager.listCategoryProducts(category);
    }
}

void bootStrap()
{
    cout << "\n Welcome to Amazon Inventory Query System" << endl;
    cout << " enter :quit to exit. or :help to list supported commands." << endl;
    cout << "\n> ";
    
    // Load CSV data
    cout << "Loading inventory data from CSV..." << endl;
    if (inventoryManager.loadFromCSV("amazon_products.csv")) {
        cout << "Inventory data loaded successfully!" << endl;
        inventoryManager.displayStats();
    } else {
        cout << "Warning: Could not load inventory data. Some features may not work." << endl;
    }
}

int main()  // Removed unused parameters
{
    string line;
    bootStrap();
    while (getline(cin, line) && line != ":quit")
    {
        if (validCommand(line))
        {
            evalCommand(line);
        }
        else
        {
            cout << "Command not supported. Enter :help for list of supported commands" << endl;
        }
        cout << "> ";
    }
    
    cout << "Goodbye!" << endl;
    return 0;
}