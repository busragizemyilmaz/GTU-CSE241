#include "ConnectFourDiag.h"

namespace Game {

    ConnectFourDiag::ConnectFourDiag() : ConnectFourAbstract() { }

    ConnectFourDiag::ConnectFourDiag(int row, int col) : ConnectFourAbstract(row, col) { }

    ConnectFourDiag::ConnectFourDiag(std::string fileName) : ConnectFourAbstract(fileName) { }

    bool ConnectFourDiag::isGameEnded() {
        CellState targetState;

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (gameBoard[i][j].getState() != CellState::empty)
                {
                    targetState = gameBoard[i][j].getState();
                    
                    if ((i + 3 < row) && (j + 3 < col)) //dioganal down-right
                    {
                        if ((gameBoard[i + 1][j + 1].getState() == targetState) &&
                            (gameBoard[i + 2][j + 2].getState() == targetState) &&
                            (gameBoard[i + 3][j + 3].getState() == targetState)) 
                        {
                            return true;
                        }
                    }

                    if ((i + 3 < row) && (j - 3 >= 0)) //dioganal down-left
                    {
                        if ((gameBoard[i + 1][j - 1].getState() == targetState) &&
                            (gameBoard[i + 2][j - 2].getState() == targetState) &&
                            (gameBoard[i + 3][j - 3].getState() == targetState)) 
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
