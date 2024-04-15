#ifndef ZAD1_DYNAMICPROGRAMMING_H
#define ZAD1_DYNAMICPROGRAMMING_H

#include "../tools/costMatrix.h"

class dynamicProgramming {
    int atsp(int, int, costMatrix);

public:
    void dynamicProgrammingAlgorithm(costMatrix);
};


#endif //ZAD1_DYNAMICPROGRAMMING_H
