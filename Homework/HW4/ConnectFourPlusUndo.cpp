#include <iostream>
#include "ConnectFourPlusUndo.h"

using std::cerr;

namespace Game {

    ConnectFourPlusUndo::ConnectFourPlusUndo() : ConnectFourPlus() {
        historyCapacity = row;
        moveCount = 0;
        moveColHistory = new int[historyCapacity];
    }

    ConnectFourPlusUndo::ConnectFourPlusUndo(int row, int col) : ConnectFourPlus(row, col) { 
        historyCapacity = row;
        moveCount = 0;
        moveColHistory = new int[historyCapacity];
    }

    ConnectFourPlusUndo::ConnectFourPlusUndo(std::string fileName) : ConnectFourPlus(fileName) {
        historyCapacity = row;
        moveCount = 0;
        moveColHistory = new int[historyCapacity];
    }

    ConnectFourPlusUndo::~ConnectFourPlusUndo() {
        delete [] moveColHistory;
    }

    ConnectFourPlusUndo::ConnectFourPlusUndo(const ConnectFourPlusUndo& other) : ConnectFourPlus(other) {
        historyCapacity = other.historyCapacity;
        moveCount = other.moveCount;

        moveColHistory = new int[historyCapacity];
        for (int i = 0; i < moveCount; i++)
            moveColHistory[i] = other.moveColHistory[i];
    }

    ConnectFourPlusUndo& ConnectFourPlusUndo::operator=(const ConnectFourPlusUndo& other) {
        if (this == &other)
            return *this;

        delete [] moveColHistory;

        ConnectFourPlus::operator=(other);

        historyCapacity = other.historyCapacity;
        moveCount = other.moveCount;

        moveColHistory = new int[historyCapacity];
        for (int i = 0; i < moveCount; i++)
            moveColHistory[i] = other.moveColHistory[i];

        return *this;
    }

    bool ConnectFourPlusUndo::play() {
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

            if (moveCount < historyCapacity) 
            {
                moveColHistory[moveCount] = final_col_index;
                moveCount++;
            }
            
            return true;
        }
        
        return false;
    }

    bool ConnectFourPlusUndo::play(char position, CellState player) {
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

        if (moveCount < historyCapacity) 
        {
            moveColHistory[moveCount] = col_index;
            moveCount++;
        }

        return true;
    }

    bool ConnectFourPlusUndo::undoLastMove() {
        int lastColIndex;
        int row_to_undo;


        if (moveCount == 0) 
        {
            cerr << "Error: No moves to undo (History is empty).\n";
            return false;
        }

        lastColIndex = moveColHistory[moveCount - 1];

        row_to_undo = -1;
        for (int i = 0; i < row; i++) 
        {
            if (gameBoard[i][lastColIndex].getState() != CellState::empty && gameBoard[i][lastColIndex].getState() != CellState::invalid) 
            {
                row_to_undo = i;
                break;
            }
        }

        if (row_to_undo != -1) 
        {
            gameBoard[row_to_undo][lastColIndex] = Cell(gameBoard[row_to_undo][lastColIndex].getPosition(), 
                                                        gameBoard[row_to_undo][lastColIndex].getRow(),
                                                        CellState::empty);

            moveCount--;
            
            return true;
        } 
        
        cerr << "Error: Move history corrupted or tahta is empty.\n";
        return false;
    }

}