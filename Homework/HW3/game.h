#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>

enum class CellState {empty, user1, user2, computer, invalid};

class ConnectFour {
public:
    ConnectFour(); //5x5
    ConnectFour(int row, int col);
    ConnectFour(std::string fileName);
    ~ConnectFour();
    ConnectFour(const ConnectFour& other);
    ConnectFour& operator=(const ConnectFour& other);
    void readFromFile(std::string fileName);
    void writeToFile(std::string fileName);
    void printBoard();
    bool play(); //computer
    bool play(char position, CellState player); //user
    bool isGameEnded();
    void playGame();
    friend bool operator==(const ConnectFour& game1, const ConnectFour& game2);
    friend bool operator!=(const ConnectFour& game1, const ConnectFour& game2);
private:
    class Cell {
    public:
        Cell();
        Cell(char p, int r, CellState s);
        char getPosition() const;
        int getRow() const;
        CellState getState() const ;
        Cell& operator++();
        Cell operator++(int);
        
        //I have to use inline function for friend function in Cell class.
        friend bool operator==(const Cell& cell1, const Cell& cell2) {
            return ((cell1.position == cell2.position) &&
            (cell1.row == cell2.row) &&
            (cell1.state == cell2.state));
        }
        friend std::ostream& operator<<(std::ostream& os, const Cell& other) {
            switch(other.state) {
                case CellState::empty:
                    os << '.';
                    break;
                case CellState::user1:
                    os << 'X';
                    break;
                case CellState::user2:
                    os << 'O';
                    break;
                case CellState::computer:
                    os << 'C'; //I use C because of no conflict with user1 or user2
                    break;
                case CellState::invalid:
                    os << ' ';
                    break;
            }

            return os;
        }
        friend std::istream& operator>>(std::istream& is, Cell& other) {
            char ch;

            is >> ch;

            switch(ch) {
                case '.':
                    other.state = CellState::empty;
                    break;
                case 'X':
                    other.state = CellState::user1;
                    break;
                case 'O':
                    other.state = CellState::user2;
                    break;
                case 'C':
                    other.state = CellState::computer;
                    break;
                case ' ':
                    other.state = CellState::invalid;
                    break;
            }

            return is;
        }
    private:
        char position;
        int row;
        CellState state;
    };

    Cell **gameBoard;
    int row;
    int col;
};

#endif