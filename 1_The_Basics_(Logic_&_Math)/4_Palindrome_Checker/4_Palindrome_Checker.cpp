#include <iostream>
#include <string>

// Function: Check Palindrome (Manual Logic)
bool Palindrome(std::string &s) {
    // If you don't insert '&' before 's' in 'std::string &s'
    // When you have a string that has 10^9 char length 
    // In main loop when you call this function it can cause
    // Time Limit Exceeded (TLE) because the working is too slow
    // Due to (Because of) everytime when computer call function
    // It will Copy all of the 'string s' to use in function
    
    // Check
    int len = s.length() - 1;
    
    // Two-pointer loop: i starts at 0, z starts at end
    // We stop when i meets z (i < z)
    for (int i = 0, z = len; i < z; i++, z--) {
        // We don't use comma ',' inside condition because that can cause Error.
        if (s[i] != s[z]) {
            return false;
        }
    }
    return true;
}

int main() {
    std::string text;
    std::cout << "Enter Text: ";
    std::cin >> text;
    
    if (Palindrome(text) == true) {
        std::cout << "\nThis text is 'Palindrome'" << std::endl;
    } else {
        std::cout << "\nThis text isn't 'Palindrome'" << std::endl;
    }
    return 0;
}