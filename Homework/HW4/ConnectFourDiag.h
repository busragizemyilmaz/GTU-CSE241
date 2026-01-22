#ifndef DIAG_H
#define DIAG_H

#include "ConnectFourAbstract.h"

namespace Game {

    class ConnectFourDiag : public ConnectFourAbstract {
    public:
        ConnectFourDiag();
        ConnectFourDiag(int row, int col);
        ConnectFourDiag(std::string fileName);
        bool isGameEnded() override;
    };

}

#endif