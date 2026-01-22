#ifndef ABSTRACT_H
#define ABSTRACT_H

#include "Cell.h"

namespace Game {

    class ConnectFourAbstract {
    public:
        ConnectFourAbstract(); //5x5
        ConnectFourAbstract(int row, int col);
        ConnectFourAbstract(std::string fileName);
        virtual ~ConnectFourAbstract();
        ConnectFourAbstract(const ConnectFourAbstract& other);
        ConnectFourAbstract& operator=(const ConnectFourAbstract& other);
        void readFromFile(std::string fileName);
        void writeToFile(std::string fileName);
        int getRow() const;
        int getCol() const;
        void printBoard();
        virtual bool play(); //computer
        virtual bool play(char position, CellState player); //user
        virtual bool isGameEnded() = 0; //pure virtual
        void playGame();
        friend bool operator==(const ConnectFourAbstract& game1, const ConnectFourAbstract& game2);
        friend bool operator!=(const ConnectFourAbstract& game1, const ConnectFourAbstract& game2);
    protected:
        Cell **gameBoard;
        int row; //height
        int col; //width
    };

}

#endif