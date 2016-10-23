//
//  wordlist.cpp
//  Project3a
//
//  Created by Tuan Dao on 10/6/15.
//  Copyright (c) 2015 Tuan Dao. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include "wordlist.h"
#include "sortHelper.h"
#include "searchHelper.h"
#include "hashtable.hpp"

// Default constructor with built in filename
wordlist::wordlist()
{
    readFromFile("dictionary.txt");
}

// void wordlist::readFromFile(std::string filename)
// Reads from the filename passed.
// File must be in the same directory as the executable.
// Only read in a word if it's longer than 4 chars.
// If fails in anyway the program will exit.
void wordlist::readFromFile(std::string filename)
{
    std::ifstream input(filename, std::ifstream::in);
    std::string temp;
    
    if (input.fail()) {
        std::cout << "Error accessing file!\n";
        exit(-1);
    }
    
    while (input >> temp)
        if (temp.length() > 4)
            v.push_back(temp);
    
    input.close();
}

// Overloaded operator <<
// Prints out the object to the designated stream.
std::ostream& operator<<(std::ostream& os, const wordlist& wl)
{
    long size = wl.v.size();
    for (int i = 0; i < size; i++)
        os << i << ": " << wl.v[i] << "\n";
    return os;
};

// void wordlist::sortInsertion(void)
// Sorts the wordlist using insertiion sort.
// Also print out the time taken.
void wordlist::sortInsertion(void)
{
    std::cout << "Warning: insertion sort is very slow!\n";
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    insertionsort<std::string>(v);
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "Insertion sort took " << (double)duration/1000.0f << " seconds.\n";
}

// void wordlist::sortMerge(void)
// Sorts the wordlist using mergesort.
// Also print out the time taken.
void wordlist::sortMerge(void)
{
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    mergesort<std::string>(v);
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "Mergesort took " << (double)duration/1000.0f << " seconds.\n";
}

// void wordlist::sortQuick(void)
// Sorts the wordlist using quicksort.
// Also print out the time taken.
void wordlist::sortQuick(void)
{
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    quicksort<std::string>(v);
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "Quicksort took " << (double)duration/1000.0f << " seconds.\n";
}

// void wordlist::sortHeap(void)
// Sorts the wordlist using heapsort.
// Also print out the time taken.
void wordlist::sortHeap(void)
{
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    heapsort<std::string>(v);
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "Heapsort took " << (double)duration/1000.0f << " seconds.\n";
}

// bool wordlist::search(std::string key)
// Binary search function to lookup the wordlist for a keyword.
// Returns 1 if found, 0 otherwise.
bool wordlist::search(std::string key)
{
    return bSearch(v, key, 0, (int)v.size()-1);
}

// bool wordlist::partialSearch(std::string key)
// Binary search function to lookup the wordlist for a PARTIAL keyword.
// Returns 1 if found, 0 otherwise.
bool wordlist::partialSearch(std::string key)
{
    return pSearch(v, key, (int)key.length(), 0, (int)v.size()-1);
}

// void wordlist::toHashtable(hashtable<std::string> &h)
// Put the words from the wordlist into a hashtable.
void wordlist::toHashtable(hashtable<std::string> &h)
{
    int size = (int)v.size();
    for (int i = 0; i < size; i++)
        h.addItem(v[i]);
}
