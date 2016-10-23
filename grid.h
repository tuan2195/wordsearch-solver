//
//  grid.h
//  Project3a
//
//  Created by Tuan Dao on 10/9/15.
//  Copyright (c) 2015 Tuan Dao. All rights reserved.
//

#ifndef __Project3a__grid__
#define __Project3a__grid__

#include <stdio.h>
#include "d_matrix.h"

class grid
{
public: // See grid.cpp for declration and explaination
    grid();
    grid(std::string filename);
    void readFromFile(std::string filename);
    char get(int x, int y);
    int getSize(bool dim);
private:
    int x, y;       // Size of the matrix
    matrix<char> m; // The matrix itself
};

#endif /* defined(__Project3a__grid__) */
