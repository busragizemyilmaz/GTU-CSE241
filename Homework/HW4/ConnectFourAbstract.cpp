#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> //for rand()
#include "ConnectFourAbstract.h"

using std::cerr;
using std::ifstream;
using std::string;
using std::ofstream;
using std::cout;
using std::cin;
using std::endl;

namespace Game {

    ConnectFourAbstract::ConnectFourAbstract(int row, int col) : row(row), col(col) { 
        gameBoard = new Cell*[row];
        for (int i = 0; i < row; i++)
            gameBoard[i] = new Cell[col];

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                gameBoard[i][j] = Cell('A' + j, row - i, CellState::empty);
            }
        }
    }

    ConnectFourAbstract::ConnectFourAbstract() : ConnectFourAbstract(5, 5) { }

    ConnectFourAbstract::ConnectFourAbstract(std::string fileName) {
        ifstream file;
        string line;
        int numberOfRows = 0;
        int numberOfCols = 0;

        file.open(fileName);
        if (!file.is_open())
        {
            cerr << "File does not open!";
            exit(1);
        }

        while(getline(file, line)) 
        {
            if (!line.empty())
            {
                numberOfRows++;

                if (line.length() > numberOfCols)
                    numberOfCols = line.length();
            }
        }
        file.close();

        row = numberOfRows;
        col = numberOfCols;
        if (row == 0 || col == 0)
        {
            cerr << "Row or col can not be 0!";
            exit(1);
        }

        gameBoard = new Cell*[row];
        for (int i = 0; i < row; i++)
            gameBoard[i] = new Cell[col];

        file.open(fileName);
        if (!file.is_open())
        {
            cerr << "File does not open!";
            exit(1);
        }

        int i = 0;
        while(getline(file, line))
        {
            for (int j = 0; j < col; j++)
            {
                CellState state_to_set = CellState::invalid;

                if (j < line.length()) 
                {                
                    if (line[j] == '*') 
                        state_to_set = CellState::empty;
                    else if (line[j] == 'X')
                        state_to_set = CellState::user1;
                    else if (line[j] == 'O')
                        state_to_set = CellState::user2;
                    else if (line[j] == 'C')
                        state_to_set = CellState::computer;
                } 

                gameBoard[i][j] = Cell('A' + j, row - i, state_to_set);
            }
            i++;
        }
    }

    ConnectFourAbstract::~ConnectFourAbstract() {
        for (int i = 0; i < row; i++)
            delete [] gameBoard[i];
        delete [] gameBoard;
    }

    ConnectFourAbstract::ConnectFourAbstract(const ConnectFourAbstract& other) {
        row = other.row;
        col = other.col;

        gameBoard = new Cell*[row];
        for (int i = 0; i < row; i++)
            gameBoard[i] = new Cell[col];

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                gameBoard[i][j] = other.gameBoard[i][j];
            }
        }
    }

    ConnectFourAbstract& ConnectFourAbstract::operator=(const ConnectFourAbstract& other) {
        if (this == &other)
            return *this;
        
        for (int i = 0; i < row; i++)
            delete [] gameBoard[i];
        delete [] gameBoard;

        row = other.row;
        col = other.col;

        gameBoard = new Cell*[row];
        for (int i = 0; i < row; i++)
            gameBoard[i] = new Cell[col];

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                gameBoard[i][j] = other.gameBoard[i][j];
            }
        }

        return *this;
    }

    void ConnectFourAbstract::readFromFile(string fileName) {
        ifstream file;
        string line;
        int numberOfRows = 0;
        int numberOfCols = 0;

        for (int i = 0; i < row; i++)
            delete [] gameBoard[i];
        delete [] gameBoard;

        file.open(fileName);
        if (!file.is_open())
        {
            cerr << "File does not open!";
            exit(1);
        }

        while(getline(file, line))
        {
            numberOfRows++;

            if(line.length() > numberOfCols)
                numberOfCols = line.length();
        }
        file.close();

        if (numberOfRows == 0 || numberOfCols == 0)
        {
            cerr << "Row or col can not be 0!";
            exit(1);
        }
        
        row = numberOfRows;
        col = numberOfCols;

        gameBoard = new Cell*[row];
        for (int i = 0; i < row; i++)
            gameBoard[i] = new Cell[col];

        file.open(fileName);
        if (!file.is_open())
        {
            cerr << "File does not open!";
            exit(1);
        }

        int i = 0;
        while(getline(file, line))
        {
            for (int j = 0; j < col; j++)
            {
                CellState state_to_set = CellState::invalid;

                if (j < line.length())
                {
                    if (line[j] == '*')
                    state_to_set = CellState::empty;
                    else if (line[j] == 'X')
                        state_to_set = CellState::user1;
                    else if (line[j] == 'O')
                        state_to_set = CellState::user2;
                    else if (line[j] == 'C')
                        state_to_set = CellState::computer;
                }

                gameBoard[i][j] = Cell('A' + j, row - i, state_to_set);
            }
            i++;
        }
        file.close();
    }

    void ConnectFourAbstract::writeToFile(string fileName) {
        ofstream file;
        CellState currentState;
        char ch;

        file.open(fileName);
        if (!file.is_open())
        {
            cerr << "File does not open!";
            exit(1);
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                currentState = gameBoard[i][j].getState();

                switch(currentState)
                {
                    case CellState::empty:
                        ch = '*';
                        break;
                    case CellState::user1:
                        ch = 'X';
                        break;
                    case CellState::user2:
                        ch = 'O';
                        break;
                    case CellState::computer:
                        ch = 'C';
                        break;
                    case CellState::invalid:
                        ch = ' ';
                        break;
                }
                file << ch;
            }
            file << endl;
        }

        file.close();
    }

    int ConnectFourAbstract::getRow() const { return row; }

    int ConnectFourAbstract::getCol() const { return col; }

    void ConnectFourAbstract::printBoard() {
        cout << "  ";
        for (int i = 0; i < col; i++)
            cout << (char)('a' + i) << " ";
        cout << endl;

        for (int i = 0; i < row; i++)
        {
            cout << row - i << " ";
            for (int j = 0; j < col; j++)
            {
                cout << gameBoard[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool ConnectFourAbstract::play() { 
        int col_index = -1;
        int final_col_index = -1;
        int row_index = -1;

        for (int attempts = 0; attempts < col * 2; attempts++) 
        {
            
            col_index = rand() % col;

            if (gameBoard[row - 1][col_index].getState() == CellState::invalid)
                continue; 
        
            if (gameBoard[0][col_index].getState() != CellState::empty)
                continue;
            
            final_col_index = col_index;
            break;
        }

        if (final_col_index == -1) 
            return false;

        for (int i = row - 1; i >= 0; i--) 
        {
            if (gameBoard[i][final_col_index].getState() == CellState::empty) 
            {
                row_index = i;
                break;
            }
        }

        if (row_index != -1) 
        {
            gameBoard[row_index][final_col_index] = Cell(gameBoard[row_index][final_col_index].getPosition(), 
                                                        gameBoard[row_index][final_col_index].getRow(),
                                                        CellState::computer);
            return true;
        }
        
        return false;
    }

    bool ConnectFourAbstract::play(char position, CellState player) {
        int col_index = position - 'a';
        int row_index = -1;

        if (col_index < 0 || col_index >= col)
        {
            cerr << "Invalid position!\n";
            return false;
        }

        for (int i = row - 1; i >= 0; i--)
        {
            if (gameBoard[i][col_index].getState() == CellState::empty)
            {
                row_index = i;
                break;
            }
        }

        if (row_index == -1) 
        {
            if (gameBoard[row - 1][col_index].getState() == CellState::invalid) {
                cerr << "Cannot play in this column (Invalid area).\n";
            } else {
                cerr << "Column is full. Choose another position.\n";
            }
            return false;
        }

        gameBoard[row_index][col_index] = Cell(gameBoard[row_index][col_index].getPosition(),
                                                gameBoard[row_index][col_index].getRow(),
                                                player);

        return true;
    }

    void ConnectFourAbstract::playGame() {
        int option;
        string fileName;
        string position;
        char ch;
        bool user1Turn = true;
        CellState currentPlayer;
        bool valid_input;
        bool isBoardFull = true;
        CellState winner;

        cout << "OPTIONS\n" << "1. Computer - User" << endl 
                            << "2. User1 - User2" << endl 
                            << "Please enter option: ";
        cin >> option;
        cout << "Enter file name: ";
        cin >> fileName;

        if (option != 1 && option != 2)
        {
            cerr << "Invalid option!";
            exit(1);
        }

        readFromFile(fileName);
        if (option == 1)
        {
            while (!isGameEnded())
            {
                printBoard();
                
                if (user1Turn)
                {
                    currentPlayer = CellState::user1;

                    valid_input = false;
                    while(!valid_input)
                    {
                        cout << "Enter position: ";
                        cin >> position;

                        if (position.length() == 1)
                        {
                            ch = position[0];

                            if (ch >= 'a' && ch < col + 'a')
                                valid_input = true;
                            else 
                                cerr << "Invalid position.";
                        }

                        else 
                            cerr << "Invalid input. Please enter single digit for position.";
                    }

                    if(play(ch, CellState::user1))
                    {
                        if (isGameEnded())
                        {
                            winner = CellState::user1;
                            break;
                        }
                        user1Turn = false;
                    }
                }
            
                else
                {
                    currentPlayer = CellState::computer;
                    play();
                    if (isGameEnded())
                    {
                        winner = CellState::computer;
                        break;
                    }

                    user1Turn = true;
                }
            }
            printBoard();
            writeToFile("afterGame.txt");
        }

        else
        {
            while (!isGameEnded())
            {
                printBoard();
                
                if (user1Turn)
                {
                    currentPlayer = CellState::user1;

                    valid_input = false;
                    while(!valid_input)
                    {
                        cout << "Enter position: ";
                        cin >> position;

                        if (position.length() == 1)
                        {
                            ch = position[0];

                            if (ch >= 'a' && ch < col + 'a')
                                valid_input = true;
                            else 
                                cerr << "Invalid position.";
                        }

                        else 
                            cerr << "Invalid input. Please enter single digit for position.";
                    }

                    if(play(ch, CellState::user1))
                    {
                        if (isGameEnded())
                        {
                            winner = CellState::user1;
                            break;
                        }
                        user1Turn = false;
                    }
                }
            
                else
                {
                    currentPlayer = CellState::user2;

                    valid_input = false;
                    while(!valid_input)
                    {
                        cout << "Enter position: ";
                        cin >> position;

                        if (position.length() == 1)
                        {
                            ch = position[0];

                            if (ch >= 'a' && ch < col + 'a')
                                valid_input = true;
                            else 
                                cerr << "Invalid position.";
                        }

                        else 
                            cerr << "Invalid input. Please enter single digit for position.";
                    }

                    if(play(ch, CellState::user2))
                    {
                        if (isGameEnded())
                        {
                            winner = CellState::user2;
                            break;
                        }
                        user1Turn = true;
                    }
                }
            }
            printBoard();
            writeToFile("afterGame.txt");
        }

        for (int i = 0; i < col; i++)
        {
            if (gameBoard[0][i].getState() == CellState::empty)
            {
                isBoardFull = false;
                break;
            }
        }

        if (isBoardFull)
        {
            cout << "Board is full. Tie!" << endl;
        }

        else
        {
            cout << "Winner is ";
            switch(winner)
            {
                case CellState::user1:
                    cout << "User1!" << endl;
                    break;
                case CellState::user2:
                    cout << "User2!" << endl;
                    break;
                case CellState::computer:
                    cout << "Computer!" << endl;
                    break;
            }
        }
    }

    bool operator==(const ConnectFourAbstract& game1, const ConnectFourAbstract& game2) {
        if ((game1.col == game2.col) && (game1.row == game2.row))
        {
            for (int i = 0; i < game1.row; i++)
            {
                for (int j = 0; j < game1.col; j++)
                {
                    if (!(game1.gameBoard[i][j] == game2.gameBoard[i][j]))
                        return false;
                }
            }
        }

        else
            return false;

        return true;
    }

    bool operator!=(const ConnectFourAbstract& game1, const ConnectFourAbstract& game2) {
        return !(game1 == game2);
    }

}