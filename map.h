#pragma once

#include <vector>
#include "cell.h"
#include "character.h"


struct Map
{
    public:

        Map(int r, int c);

        int rows, columns;
        char matrix;

        void showInfo();
};