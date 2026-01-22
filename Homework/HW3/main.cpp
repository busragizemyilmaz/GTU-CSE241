#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include "game.h"  // Contains the ConnectFour class definition

using namespace std;

// Global file names for testing
const string SHAPE_FILE = "file2.txt";

int main() 
{
    // Initialize the random number generator (Required for computer moves)
    srand(time(0)); 
    
    // --- Testing ConnectFour Objects (Minimum 5 objects required by homework) ---
    
    // Constructor 1: Default (5x5)
    ConnectFour game1;
    cout << "--- GAME 1: Default (5x5) ---" << endl;
    game1.printBoard();
    
    // Constructor 2: Size parameters (8x6)
    ConnectFour game2(8, 6);
    cout << "\n--- GAME 2: 8x6 Board ---" << endl;
    game2.printBoard();
 
    // Constructor 3: Read from file (Requires shape_board.txt to exist)
    ConnectFour game3(SHAPE_FILE);
    cout << "\n--- GAME 3: From File (" << SHAPE_FILE << ") ---" << endl;
    game3.printBoard();

    // Test 4: Copy Constructor
    ConnectFour game4 = game2; 
    cout << "\n--- GAME 4: Copy of Game 2 ---" << endl;
    game4.printBoard();
    
    // Test 5: Assignment Operator
    ConnectFour game5; 
    game5 = game2; 
    cout << "\n--- GAME 5: Assignment from Game 2 ---" << endl;
    game5.printBoard();
    
    // --- Testing Operators ---
    cout << "\n--- Operator Tests ---" << endl;
    if (game2 == game4) 
    {
        cout << "Game 2 and Game 4 are equal (True)." << endl;
    } 
    else 
    {
        cout << "Game 2 and Game 4 are not equal (False)." << endl;
    }
    
    if (game1 != game2) 
    {
        cout << "Game 1 and Game 2 are not equal (True)." << endl;
    }
    else 
    {
        cout << "Game 1 and Game 2 are equal (False)." << endl;
    }
    
    // --- Running Simultaneous Games ---
    // NOTE: These tests run sequentially, as one game must finish before the next can start. 
    cout << "\n--- Starting Sequential Games (playGame) ---" << endl;
    
    cout << "\n*** Starting Game 1 ***" << endl;
    game1.playGame(); 
    
    cout << "\n*** Starting Game 2 ***" << endl;
    game2.playGame(); 
    
    cout << "\n*** Starting Game 4 (Copy Test) ***" << endl;
    game4.playGame();
    
    return 0;
}