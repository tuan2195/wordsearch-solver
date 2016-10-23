//
//  grid.cpp
//  Project3a
//
//  Created by Tuan Dao on 10/9/15.
//  Copyright (c) 2015 Tuan Dao. All rights reserved.
//

#include "grid.h"
#include <fstream>

// Default constructor
grid::grid() {}

// Constructor with filename argument
grid::grid(std::string filename)
{
    readFromFile(filename);
}

// void wordlist::readFromFile(std::string filename)
// Reads from the filename passed to the matrix.
// File must be in the same directory as the executable.
// If fails in anyway the program will exit.
void grid::readFromFile(std::string filename)
{
    std::ifstream input(filename, std::ifstream::in);
    std::string temp;
    
    if (input.fail()) {
        std::cout << "Error accessing file!\n";
        exit(-1);
    }
    
    input >> x;
    input >> y;
    
    m.resize(x, y); // Resizes the matrix (y, x)
    
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            input >> m[i][j];
        }
    }
    
    input.close();
}

// char grid::get(int x, int y)
// Returns the character at coordinates (x, y)
char grid::get(int x, int y)
{
    return m[x][y];
}

// int grid::getSize(bool dim)
// Returns the size of the matrix.
// 0 for x, 1 for y
int grid::getSize(bool dim)
{
    if (dim) {
        return y;
    } else return x;
}