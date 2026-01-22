#include <iostream>
#include "Cell.h"

namespace Game {

    Cell::Cell() : position('\0'), row(0), state(CellState::empty) { }

    Cell::Cell(char p, int r, CellState s) : position(p), row(r), state(s) { }

    char Cell::getPosition() const { return position ;}

    int Cell::getRow() const { return row; }

    CellState Cell::getState() const { return state; }

    Cell& Cell::operator++() {
        switch(state) {
            case CellState::empty:
                state = CellState::user1;
                break;
            case CellState::user1:
                state = CellState::user2;
                break;
            case CellState::user2:
                state = CellState::computer;
                break;
            case CellState::computer:
                state = CellState::empty;
                break;  
        }

        return *this;
    }

    Cell Cell::operator++(int) {
        Cell temp = *this;

        ++(*this);

        return temp;
    }

    Cell& Cell::operator--() {
        switch(state) {
            case CellState::empty:
                state = CellState::computer;
                break;
            case CellState::user1:
                state = CellState::empty;
                break;
            case CellState::user2:
                state = CellState::user1;
                break;
            case CellState::computer:
                state = CellState::user2;
                break;  
        }

        return *this;
    }

    Cell Cell::operator--(int) {
        Cell temp = *this;

        --(*this);

        return temp;
    }

    bool operator==(const Cell& cell1, const Cell& cell2) {
        return ((cell1.position == cell2.position) &&
                (cell1.row == cell2.row) &&
                (cell1.state == cell2.state));
    }

    std::ostream& operator<<(std::ostream& os, const Cell& other) {
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

    std::istream& operator>>(std::istream& is, Cell& other) {
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

}
