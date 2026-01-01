#include <iostream>

// GLOBAL CONSTANTS
// We use constants to avoid "Magic Numbers" in the code.
const int SIZE = 3;

// Function: Draw the Board
// We use 'char (&board)[SIZE][SIZE]' to pass the 2D array by Reference.
// If we just used 'char board[SIZE][SIZE]', it would decay to a pointer.
// Using '&' preserves the dimensions and ensures we access the original memory.
void drawBoard(char (&board)[SIZE][SIZE]) {
    std::cout << "\n";
    for (int i = 0; i < SIZE; i++) {
        std::cout << " ";
        for (int j = 0; j < SIZE; j++) {
            std::cout << board[i][j];
            if (j < SIZE - 1) std::cout << " | ";
        }
        std::cout << "\n";
        if (i < SIZE - 1) std::cout << "---|---|---\n";
    }
    std::cout << "\n";
}

// Function: Check for a Winner
// Returns 'X' or 'O' if someone won, or 'D' for Draw, or ' ' (space) for Continue.
char checkWinner(char (&board)[SIZE][SIZE]) {
    // 1. Check Rows (Manual Loop)
    for (int i = 0; i < SIZE; i++) {
        // If row is uniform (all X or all O)
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return board[i][0];
        }
    }

    // 2. Check Columns (Manual Loop)
    for (int i = 0; i < SIZE; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return board[0][i];
        }
    }

    // 3. Check Diagonals
    // Top-Left to Bottom-Right
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return board[0][0];
    }
    // Top-Right to Bottom-Left
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return board[0][2];
    }

    return ' '; // No winner yet
}

// Function: Update the board with player move
bool placeMarker(char (&board)[SIZE][SIZE], int slot, char marker) {
    // Logic to convert Slot Number (1-9) to Grid Coordinates (row, col)
    // Row = (slot - 1) / 3
    // Col = (slot - 1) % 3
    // Example: Slot 5 -> (5-1)/3 = 1 (Row 1), (5-1)%3 = 1 (Col 1)
    
    int row = (slot - 1) / SIZE;
    int col = (slot - 1) % SIZE;

    // Check if slot is already taken (X or O)
    // We check if the char is NOT the original digit
    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = marker;
        return true;
    } else {
        return false;
    }
}

int main() {
    // Initialize Board with numbers 1-9
    char board[SIZE][SIZE] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    char currentPlayer = 'X';
    int slot;
    int turns = 0;
    char winner = ' ';

    std::cout << "=== TIC TAC TOE (Manual Logic) ===\n";

    // Main Game Loop
    // Runs for a maximum of 9 turns or until a winner is found
    while (turns < 9) {
        drawBoard(board);
        
        std::cout << "Player " << currentPlayer << ", enter slot (1-9): ";
        std::cin >> slot;

        // Input Validation
        if (slot < 1 || slot > 9) {
            std::cout << "Invalid slot! Try again.\n";
            continue;
        }

        // Try to place marker
        if (placeMarker(board, slot, currentPlayer)) {
            
            // Check win condition immediately after a valid move
            winner = checkWinner(board);
            if (winner != ' ') {
                drawBoard(board);
                std::cout << "Winner: Player " << winner << "!\n";
                break; // Exit loop
            }

            // Switch Player
            // If current is X, make it O. Otherwise make it X.
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            turns++;
        } else {
            std::cout << "Slot already taken! Try again.\n";
        }
    }

    // Check for Draw
    if (winner == ' ' && turns == 9) {
        drawBoard(board);
        std::cout << "It's a Draw!\n";
    }

    return 0;
}