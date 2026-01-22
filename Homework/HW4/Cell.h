#ifndef CELL_H
#define CELL_H

#include <iostream>

enum class CellState {empty, user1, user2, computer, invalid};

namespace Game {

    class Cell {
    public:
        Cell();
        Cell(char p, int r, CellState s);
        char getPosition() const;
        int getRow() const;
        CellState getState() const ;
        Cell& operator++();
        Cell operator++(int);
        Cell& operator--();
        Cell operator--(int);
        friend bool operator==(const Cell& cell1, const Cell& cell2);
        friend std::ostream& operator<<(std::ostream& os, const Cell& other);
        friend std::istream& operator>>(std::istream& is, Cell& other);
    private:
        char position;
        int row;
        CellState state;
    };
    
}

#endif