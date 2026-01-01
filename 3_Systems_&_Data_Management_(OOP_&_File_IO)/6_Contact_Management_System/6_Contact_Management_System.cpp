#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct Contact {
    std::string name;
    std::string phoneNumber;
};

// Function to overwrite the ENTIRE file with the current list
// We use this after deleting a contact to update the file
void saveAllContactsToFile(const std::vector<Contact>& contactList) {
    // std::ios::trunc mode deletes the old file content and starts fresh
    std::ofstream file("contacts.txt", std::ios::trunc);
    
    if (file.is_open()) {
        for (const auto& contact : contactList) {
            file << contact.name << " " << contact.phoneNumber << std::endl;
        }
        file.close();
    } else {
        std::cout << "Error: Could not update file." << std::endl;
    }
}

// Function to add a single contact (Append mode)
// We keep this for efficiency so we don't rewrite the whole file just to add one person
void addContact(std::vector<Contact>& contactList) {
    Contact newContact;
    
    std::cout << "Enter Name (No spaces, use underscores e.g. John_Doe): ";
    std::cin >> newContact.name; 
    
    std::cout << "Enter Phone Number: ";
    std::cin >> newContact.phoneNumber;

    contactList.push_back(newContact);
    
    // Append just this one contact to the file
    std::ofstream file("contacts.txt", std::ios::app);
    if (file.is_open()) {
        file << newContact.name << " " << newContact.phoneNumber << std::endl;
        file.close();
    }
    
    std::cout << "Contact added successfully!" << std::endl;
}

void displayContacts(const std::vector<Contact>& contactList) {
    std::cout << "\n=== Contact List ===" << std::endl;
    if (contactList.empty()) {
        std::cout << "No contacts found." << std::endl;
    } else {
        for (size_t i = 0; i < contactList.size(); ++i) {
            std::cout << i + 1 << ". " << contactList[i].name 
                      << " (" << contactList[i].phoneNumber << ")" << std::endl;
        }
    }
    std::cout << "====================" << std::endl;
}

// Function to delete a contact
void deleteContact(std::vector<Contact>& contactList) {
    displayContacts(contactList); // Show list so user knows the ID number
    
    if (contactList.empty()) return;

    int index;
    std::cout << "Enter the ID number of the contact to delete: ";
    std::cin >> index;

    // Adjust for 0-based indexing (User sees 1, Computer sees 0)
    int vectorIndex = index - 1;

    // Validation: Check if the ID actually exists
    if (vectorIndex >= 0 && vectorIndex < contactList.size()) {
        
        // Remove from memory
        // .erase() requires an iterator, so we use .begin() + index
        contactList.erase(contactList.begin() + vectorIndex);
        
        // Save the new list to the hard drive (Overwrite mode)
        saveAllContactsToFile(contactList);
        
        std::cout << "Contact deleted successfully." << std::endl;
    } else {
        std::cout << "Error: Invalid ID." << std::endl;
    }
}

void loadContactsFromFile(std::vector<Contact>& contactList) {
    std::ifstream file("contacts.txt");
    Contact temp;
    if (file.is_open()) {
        while (file >> temp.name >> temp.phoneNumber) {
            contactList.push_back(temp);
        }
        file.close();
    }
}

int main() {
    std::vector<Contact> myContacts;
    int choice;

    loadContactsFromFile(myContacts);

    do {
        std::cout << "\n=== Contact Manager ===" << std::endl;
        std::cout << "1. Add Contact" << std::endl;
        std::cout << "2. View Contacts" << std::endl;
        std::cout << "3. Delete Contact" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch(choice) {
            case 1: addContact(myContacts); break;
            case 2: displayContacts(myContacts); break;
            case 3: deleteContact(myContacts); break;
            case 4: std::cout << "Exiting..." << std::endl; break;
            default: std::cout << "Invalid choice." << std::endl;
        }
    } while (choice != 4);

    return 0;
}