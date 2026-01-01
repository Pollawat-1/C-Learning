#include <iostream>
#include <random> // Modern random generation
#include <ctime>  // Time for seeding

// Function to generate the computer's move using std::mt19937
// Returns: 1 (Rock), 2 (Paper), or 3 (Scissors)
int getComputerChoice() {
    std::random_device rd;
    static std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
    std::uniform_int_distribution<> distr(1, 3);
    return distr(gen);
}

// Function to determine winner AND update scores
// Note: We use '&' (Pass by Reference) so we can modify the original variables from main
void processRound(int userChoice, int computerChoice, int &userScore, int &compScore) {
    
    // Display Computer's choice
    std::cout << "Computer chose: ";
    switch(computerChoice) {
        case 1: std::cout << "Rock"; break;
        case 2: std::cout << "Paper"; break;
        case 3: std::cout << "Scissors"; break;
    }
    std::cout << std::endl;

    // Logic logic
    if (userChoice == computerChoice) {
        std::cout << "Result: It's a Tie! (No points awarded)" << std::endl;
    }
    else if ((userChoice == 1 && computerChoice == 3) ||
             (userChoice == 2 && computerChoice == 1) ||
             (userChoice == 3 && computerChoice == 2)) {
        std::cout << "Result: You Win this round!" << std::endl;
        userScore++; // Increment user score directly
    }
    else {
        std::cout << "Result: Computer Wins this round!" << std::endl;
        compScore++; // Increment computer score directly
    }
}

int main() {
    int userChoice;
    char playAgain;
    
    // Initialize scores
    int userScore = 0;
    int computerScore = 0;

    do {
        // Display Current Scoreboard
        std::cout << "\n=========================================" << std::endl;
        std::cout << " SCOREBOARD | You: " << userScore << " | Computer: " << computerScore << std::endl;
        std::cout << "=========================================" << std::endl;

        std::cout << "1. Rock" << std::endl;
        std::cout << "2. Paper" << std::endl;
        std::cout << "3. Scissors" << std::endl;
        std::cout << "Enter your choice (1-3): ";
        std::cin >> userChoice;

        if (userChoice < 1 || userChoice > 3) {
            std::cout << "Error: Invalid input. Please enter 1, 2, or 3." << std::endl;
        } else {
            int computerChoice = getComputerChoice();
            // Pass scores by reference so they get updated
            processRound(userChoice, computerChoice, userScore, computerScore);
        }

        std::cout << "\nPlay again? (y/n): ";
        std::cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    // Final Score Summary
    std::cout << "\n=== FINAL SCORE ===" << std::endl;
    std::cout << "You: " << userScore << std::endl;
    std::cout << "Computer: " << computerScore << std::endl;
    
    if (userScore > computerScore) {
        std::cout << "Congratulations! You won the match." << std::endl;
    } else if (computerScore > userScore) {
        std::cout << "Game Over. The Computer won the match." << std::endl;
    } else {
        std::cout << "The match ended in a draw." << std::endl;
    }

    return 0;
}