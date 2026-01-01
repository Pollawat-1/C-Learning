#include <iostream>

// Function: Calculate Factorial
// We use unsigned long long to support larger numbers (up to 20!)
unsigned long long calculateFactorial(int n) {
    // Standard integer (int) max value is ~2 billion
    // Factorial grows very fast (13! > 6 billion)
    // Using int would cause Overflow (wrong negative numbers)
    
    unsigned long long result = 1;
    
    // Manual loop multiplication
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    int n;
    std::cout << "Enter number (0-20): ";
    std::cin >> n;
    
    if (n < 0) {
        std::cout << "\nError: Factorial of negative number doesn't exist.";
    } 
    else if (n > 20) {
        // Prevent overflow even for long long
        std::cout << "\nError: Number is too large for this variable type.";
    } 
    else {
        // Call function
        std::cout << "\nResult: " << calculateFactorial(n);
    }
    std::cout << std::endl;
    return 0;
}