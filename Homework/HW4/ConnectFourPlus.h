#ifndef PLUS_H
#define PLUS_H

#include "ConnectFourAbstract.h"

namespace Game {

    class ConnectFourPlus : public ConnectFourAbstract {
    public:
        ConnectFourPlus();
        ConnectFourPlus(int row, int col);
        ConnectFourPlus(std::string fileName);
        bool isGameEnded() override;
    };

}

#endif