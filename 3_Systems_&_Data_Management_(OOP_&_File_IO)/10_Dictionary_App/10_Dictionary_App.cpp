#include <iostream>
#include <map>          // key-value storage
#include <string>
#include <fstream>      // File I/O
#include <algorithm>    // For transforming text to lowercase

// Global Dictionary Map
// Key (string) = The Word
// Value (string) = The Definition
std::map<std::string, std::string> dictionary;

// Helper: Convert string to lowercase so "Apple" and "apple" are the same
std::string toLower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// === FILE HANDLING ===
void saveDictionary() {
    std::ofstream file("dictionary_data.txt");
    if (file.is_open()) {
        // Iterate through the map using an iterator
        // 'pair.first' is the Word, 'pair.second' is the Definition
        for (const auto& pair : dictionary) {
            file << pair.first << "\n";
            file << pair.second << "\n";
        }
        file.close();
    }
}

void loadDictionary() {
    std::ifstream file("dictionary_data.txt");
    if (file.is_open()) {
        std::string word, definition;
        while (getline(file, word)) {
            if (getline(file, definition)) {
                dictionary[word] = definition;
            }
        }
        file.close();
    }
}

// === APP FEATURES ===

void addWord() {
    std::string word, definition;
    std::cout << "\n--- Add New Word ---" << std::endl;
    std::cout << "Enter Word: ";
    std::cin >> word;
    
    // Clear buffer before getline
    std::cin.ignore(); 
    
    std::cout << "Enter Definition: ";
    std::getline(std::cin, definition);

    // Store in map (Auto-converts to lowercase key)
    std::string key = toLower(word);
    
    // Check if word already exists
    if (dictionary.find(key) != dictionary.end()) {
        std::cout << "Word already exists! Updating definition..." << std::endl;
    }
    
    // Insert or Update
    dictionary[key] = definition;
    saveDictionary();
    std::cout << "Word saved successfully." << std::endl;
}

void searchWord() {
    std::string word;
    std::cout << "\n--- Search Dictionary ---" << std::endl;
    std::cout << "Enter Word to find: ";
    std::cin >> word;

    std::string key = toLower(word);

    // .find(key) returns an iterator. 
    // If it reaches .end(), the word is NOT found.
    auto it = dictionary.find(key);

    if (it != dictionary.end()) {
        std::cout << "-------------------------" << std::endl;
        std::cout << "Word: " << word << std::endl;
        std::cout << "Definition: " << it->second << std::endl; // it->second gives the value
        std::cout << "-------------------------" << std::endl;
    } else {
        std::cout << "Word not found in dictionary." << std::endl;
    }
}

void viewAll() {
    std::cout << "\n=== ALL WORDS (" << dictionary.size() << ") ===" << std::endl;
    if (dictionary.empty()) {
        std::cout << "Dictionary is empty." << std::endl;
        return;
    }

    int count = 1;
    for (const auto& pair : dictionary) {
        std::cout << count++ << ". " << pair.first << ": " << pair.second << std::endl;
    }
}

int main() {
    loadDictionary();

    int choice;
    do {
        std::cout << "\n=== C++ DICTIONARY APP ===" << std::endl;
        std::cout << "1. Add / Update Word" << std::endl;
        std::cout << "2. Search Word" << std::endl;
        std::cout << "3. View All Words" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Choice: ";
        std::cin >> choice;

        switch(choice) {
            case 1: addWord(); break;
            case 2: searchWord(); break;
            case 3: viewAll(); break;
            case 4: std::cout << "Exiting..." << std::endl; break;
            default: std::cout << "Invalid choice." << std::endl;
        }
    } while (choice != 4);

    return 0;
}