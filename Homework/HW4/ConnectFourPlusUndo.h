#ifndef PLUS_UNDO_H
#define PLUS_UNDO_H

#include "ConnectFourPlus.h"

namespace Game {

    class ConnectFourPlusUndo : public ConnectFourPlus {
    public:
        ConnectFourPlusUndo();
        ConnectFourPlusUndo(int row, int col);
        ConnectFourPlusUndo(std::string fileName);
        ~ConnectFourPlusUndo();
        ConnectFourPlusUndo(const ConnectFourPlusUndo& other);
        ConnectFourPlusUndo& operator=(const ConnectFourPlusUndo& other);
        bool play() override;
        bool play(char position, CellState player) override;
        bool undoLastMove();
    private:
        int *moveColHistory;
        int historyCapacity;
        int moveCount;
    };

}

#endif