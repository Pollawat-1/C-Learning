#include <iostream>

// Function for addition
double add(double a, double b) {
    return a + b;
}

// Function for subtraction
double subtract(double a, double b) {
    return a - b;
}

int main() {
    double num1, num2;
    char op;

    // Display welcome message
    std::cout << "=== C++ Professional Calculator ===" << std::endl;

    // Get user input
    std::cout << "Enter first number: ";
    std::cin >> num1;

    std::cout << "Enter operator (+, -, *, /): ";
    std::cin >> op;

    std::cout << "Enter second number: ";
    std::cin >> num2;

    // Perform calculation based on operator
    switch(op) {
        case '+':
            // Execute addition
            std::cout << "Result: " << add(num1, num2) << std::endl;
            break;
        case '-':
            // Execute subtraction
            std::cout << "Result: " << subtract(num1, num2) << std::endl;
            break;
        case '*':
            std::cout << "Result: " << num1 * num2 << std::endl;
            break;
        case '/':
            // Check for division by zero
            if (num2 != 0) {
                std::cout << "Result: " << num1 / num2 << std::endl;
            } else {
                std::cout << "Error: Division by zero is not allowed." << std::endl;
            }
            break;
        default:
            // Handle invalid operators
            std::cout << "Error: Invalid operator." << std::endl;
    }

    return 0;
}