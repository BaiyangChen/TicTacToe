#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Global game board
vector<vector<char> > board(3, vector<char>(3, ' '));

// Function to display the game board
void displayBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << "|";
        }
        if (i < 2) cout << "\n-+-+-\n";
    }
    cout << "\n";
}

// Function to check if a player has won
bool checkWin(char player) {
    for (int i = 0; i < 3; i++) {
        // Check rows and columns
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            return true;
    }
    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        return true;

    return false;
}

// Function to check for a tie (no empty spaces left)
bool checkTie() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return false;
    return true;
}

// Function for the player's move
void playerMove() {
    int row, col;
    while (true) {
        cout << "Enter row and column indices (0-2, space-separated) for your move: ";
        cin >> row >> col;

        // Check if the input operation failed
        if (cin.fail()) {
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line
            cout << "Invalid input, please enter numbers only." << endl;
            continue; // Go to the next iteration of the loop
        }

        // Check if the chosen position is valid
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
            board[row][col] = 'X'; // Place the player's mark
            break; // Exit the loop
        } else {
            cout << "Invalid move, try again." << endl;
        }
    }
}

// Function for the AI's move
void aiMove() {
    srand(time(0)); // Seed for random number generation
    int row, col;

    // Simple AI: Randomly place a mark on an empty spot
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (board[row][col] != ' ');

    board[row][col] = 'O'; // Place the AI's mark
    cout << "AI placed 'O' at " << row << ", " << col << endl;
}

int main() {
    cout << "Welcome to Tic-Tac-Toe!" << endl;

    while (true) {
        displayBoard();
        playerMove();
        if (checkWin('X')) {
            cout << "Congratulations! You've won!" << endl;
            break;
        } else if (checkTie()) {
            cout << "It's a tie!" << endl;
            break;
        }

        aiMove();
        if (checkWin('O')) {
            cout << "AI wins. Try again!" << endl;
            break;
        } else if (checkTie()) {
            cout << "It's a tie!" << endl;
            break;
        }
    }

    displayBoard(); // Show the final board
    return 0;
}