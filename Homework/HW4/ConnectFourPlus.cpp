#include "ConnectFourPlus.h"

namespace Game {

    ConnectFourPlus::ConnectFourPlus() : ConnectFourAbstract() { }

    ConnectFourPlus::ConnectFourPlus(int row, int col) : ConnectFourAbstract(row, col) { }

    ConnectFourPlus::ConnectFourPlus(std::string fileName) : ConnectFourAbstract(fileName) { }

    bool ConnectFourPlus::isGameEnded() {
        CellState targetState;

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (gameBoard[i][j].getState() != CellState::empty)
                {
                    targetState = gameBoard[i][j].getState();
                    
                    if (j + 3 < col) //horizontal
                    {
                        if ((gameBoard[i][j + 1].getState() == targetState) &&
                            (gameBoard[i][j + 2].getState() == targetState) &&
                            (gameBoard[i][j + 3].getState() == targetState)) 
                        {
                            return true;
                        }
                    }

                    if (i + 3 < row) //vertical
                    {
                        if ((gameBoard[i + 1][j].getState() == targetState) &&
                            (gameBoard[i + 2][j].getState() == targetState) &&
                            (gameBoard[i + 3][j].getState() == targetState)) 
                        {
                            return true;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (gameBoard[i][j].getState() == CellState::empty)
                    return false;
            }
        }

        return true;
    }

}