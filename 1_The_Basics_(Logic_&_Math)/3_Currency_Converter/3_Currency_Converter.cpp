#include <iostream>
#include <iomanip> // For std::fixed and setprecision

// Global Constants for Rates (Easier to update)
const double USD_TO_THB = 34.50;

void convertCurrency(double &money) {
    // Pass by Reference (&money) isn't strictly necessary for 'double' (8 bytes)
    // but good practice if we were modifying the original variable.
    
    double result = money * USD_TO_THB;
    
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n" << money << " USD = " << result << " THB";
}

int main() {
    double amount;
    std::cout << "Enter amount in USD: ";
    std::cin >> amount;
    
    if (amount < 0) {
        std::cout << "\nError: Money cannot be negative.";
    } else {
        convertCurrency(amount);
    }
    std::cout << std::endl;
    return 0;
}