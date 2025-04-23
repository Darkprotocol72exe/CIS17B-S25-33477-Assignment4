// This program models a Storage Management System for organizing and retrieving physical objects efficiently.
// Hugo Willis
// CIS-17B-33477
// LMD: 04/21/25
#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <memory>
#include <stdexcept>
#include <limits>

using namespace std;

class DuplicateItemException : public exception {
public:
    const char* what() const noexcept override {
        return "DuplicateItemException: Item ID already exists.";
    }
};

class ItemNotFoundException : public exception {
public:
    const char* what() const noexcept override {
        return "ItemNotFoundException: Item ID not found.";
    }
};

class StoredItem {
private:
    string id_, description_, location_;

public:
    StoredItem(const string& id,
               const string& description,
               const string& location)
        : id_(id), description_(description), location_(location)
    {}

    string getId() const          { return id_; }
    string getDescription() const { return description_; }
    string getLocation() const    { return location_; }
};

class StorageManager {
private:
    unordered_map<string, shared_ptr<StoredItem>> itemById_;
    map<string, shared_ptr<StoredItem>>           itemByDescription_;

public:
    void addItem(const shared_ptr<StoredItem>& item) {
        const auto& id   = item->getId();
        const auto& desc = item->getDescription();

        if(itemById_.count(id))
            throw DuplicateItemException();

        itemById_[id]            = item;
        itemByDescription_[desc] = item;
    }

    shared_ptr<StoredItem> findById(const string& id) const {
        auto it = itemById_.find(id);
        if(it == itemById_.end())
            throw ItemNotFoundException();
        return it->second;
    }

    void removeItem(const string& id) {
        auto it = itemById_.find(id);
        if(it == itemById_.end())
            throw ItemNotFoundException();

        itemByDescription_.erase(it->second->getDescription());
        itemById_.erase(it);
    }

    void listItemsByDescription() const {
        if(itemByDescription_.empty()) {
            cout << "No items in storage.\n";
            return;
        }
        cout << "\nItems (A→Z by description):\n";
        for(const auto& [desc, item] : itemByDescription_) {
            cout << "  [" << item->getId() << "] "
                 << desc << " @ " << item->getLocation() << "\n";
        }
    }
};

int main(){
    StorageManager manager;
    bool running = true;

    while(running){
        cout << "\n=== Warehouse Menu ===\n"
             << "1) Add item\n"
             << "2) Find item by ID\n"
             << "3) Remove item by ID\n"
             << "4) List items by description\n"
             << "5) Quit\n"
             << "Choose an option: ";

        int choice;
        if(!(cin >> choice)){
            // invalid integer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number 1–5.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice){
            case 1: {
                // Add
                string id, desc, loc;
                cout << "Enter new item ID: ";
                getline(cin, id);
                cout << "Enter description: ";
                getline(cin, desc);
                cout << "Enter location: ";
                getline(cin, loc);

                try {
                    auto item = make_shared<StoredItem>(id, desc, loc);
                    manager.addItem(item);
                    cout << "Item added.\n";
                } catch(const exception& e){
                    cout << "Error: " << e.what() << "\n";
                }
                break;
            }

            case 2: {
                // Find
                string id;
                cout << "Enter item ID to find: ";
                getline(cin, id);
                try {
                    auto item = manager.findById(id);
                    cout << "Found: [" << item->getId() << "] "
                         << item->getDescription()
                         << " @ " << item->getLocation() << "\n";
                } catch(const exception& e){
                    cout << "Error: " << e.what() << "\n";
                }
                break;
            }

            case 3: {
                // Remove
                string id;
                cout << "Enter item ID to remove: ";
                getline(cin, id);
                try {
                    manager.removeItem(id);
                    cout << "Item removed.\n";
                } catch(const exception& e){
                    cout << "Error: " << e.what() << "\n";
                }
                break;
            }

            case 4:
                // List
                manager.listItemsByDescription();
                break;

            case 5:
                running = false;
                cout << "Warehouse Menu Terminated \n";
                break;

            default:
                cout << "Invalid choice; please select 1–5.\n";
        }
    }

    return 0;
}
