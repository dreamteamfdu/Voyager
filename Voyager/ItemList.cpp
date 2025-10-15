#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "json.hpp"
#include "Item.h"

using namespace std;
using json = nlohmann::json;

class ItemList {
private:
    unordered_map<string, Item> items;  // Store items by name

public:
    // Load items from a JSON file
    void loadFromJson(const string& filename) {
        ifstream file(filename);

        // Check if the file exists
        if (!file.is_open()) {
            cout << "ERROR: Unable to open file " << filename << ". Creating a new file." << endl;

            // Create a new file with an empty JSON object if it doesn't exist
            json j;
            ofstream newFile(filename);
            if (newFile.is_open()) {
                newFile << j.dump(4); // Write an empty JSON object to the file with indentation for readability
                newFile.close();
                cout << "A new empty inventory file has been created." << endl;
            }
            else {
                cout << "ERROR: Unable to create the file " << filename << endl;
                return;
            }
        }
        else {
            // File opened successfully, load the JSON data
            json j;
            file >> j;

            for (auto& item : j.items()) {
                string name = item.key();
                int count = item.value().get<int>();
                items[name] = Item(name, count);
            }

            file.close();
        }
    }

    // Get an item by name
    Item* getItem(const string& name) {
        if (items.find(name) != items.end()) {
            return &items[name];
        }
        return nullptr; // Item not found
    }

    // Method to list all items and their counts
    void listItems() {
        if (items.empty()) {
            cout << "No items in the inventory!" << endl;
            return;
        }
        cout << "Items in inventory: " << endl;
        for (auto& item : items) {
            cout << item.second.getName() << " - " << item.second.getCount() << endl;
        }
    }
};