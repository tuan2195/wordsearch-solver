//
//  main.cpp
//  Project3a
//
//  Created by Tuan Dao on 10/6/15.
//  Copyright (c) 2015 Tuan Dao. All rights reserved.
//

#include <iostream>     // Program IO
#include <vector>       // Vectors
#include <chrono>       // High resolution timing library
#include "wordlist.h"   // Wordlist object
#include "grid.h"       // Grid object
#include "d_matrix.h"   // Matrix object
#include "heap.hpp"     // Heap object
#include "hashtable.hpp"// Hashtable object
#include "sortHelper.h" // Sort function templates
#include "helper.h"     // Miscellaneous fucntions

void wordsearch(std::string filename, int sortAlgo, bool useHash, bool debugPrint);
void findMatches(wordlist dict, grid g, bool debugPrint);
void findMatchesHash(hashtable<std::string> dict, grid g, bool debugPrint);

// Main function
// Prompts the user to choose the sort algorithm
// Then calls the search function
int main(int argc, const char * argv[])
{
    auto usageTxt = "Usage: word filename sortAlgorithm useHastable debugPrint\n"
                    "  sortAlgorithm: choose the sort algorithm used to sort dictionary\n"
                    "      0 for insertion sort\n"
                    "      1 for merge sort\n"
                    "      2 for quicksort\n"
                    "      3 for heapsort\n"
                    "  useHastable: choose whether to use hash table to help with dictionary search\n"
                    "      0 to not use hastable\n"
                    "      1 to use hastable\n"
                    "  debugPrint: choose whether to print debug messeages i.e. list of words found\n"
                    "      0 to not print debug\n"
                    "      1 to print debug\n";

    if (argc != 5)
    {
        std::cout << usageTxt;
        return -1;
    }

    std::string filename(argv[1]);
    int sortAlgo = atoi(argv[2]);
    int useHash = atoi(argv[3]);
    int debugPrint = atoi(argv[4]);

    if (sortAlgo < 0   || sortAlgo > 3 || 
        useHash < 0    || useHash > 1  ||
        debugPrint < 0 || debugPrint > 1)
    {
        std::cout << "Invalid arguments!\n" << usageTxt;
        return -1;
    }

    wordsearch(filename, sortAlgo, useHash, debugPrint);
}

// void wordsearch(std::string filename int sel, bool useHash)
// Prompts the user to enter the filename then load the file with that name
// into a grid object. It will also load the dictionary file and sort it
// using the chosen sort method. It will then fall the findMatches function.
// After the function returns it will stop the timer and prints out the total time taken.
void wordsearch(std::string filename, int sortAlgo, bool useHash, bool debugPrint)
{
    grid puzzle(filename);
    wordlist dict;
    hashtable<std::string> hdict(10000);
    dict.toHashtable(hdict);

    // Timer starts
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    switch (sortAlgo) { // Choose the wanted sort algorithm
        case 0:
            dict.sortInsertion();   
            break;
        case 1:
            dict.sortMerge();       
            break;
        case 2:
            dict.sortQuick();       
            break;
        case 3:
            dict.sortHeap();        
            break;
        default:
            undefinedBehavior();    
            break;
    }
    
    if (debugPrint) 
        std::cout << dict;
    
    if (useHash)
        findMatchesHash(hdict, puzzle, debugPrint);
    else
        findMatches(dict, puzzle, debugPrint);
    
    // Timer ends
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "Total time taken: " << (double)duration/1000.0f << " seconds.\n";
}

// void findMatches(wordlist dict, grid g, bool debugPrint)
// Lookup a grid for any word that is in the dictionary.
// Stores those words in a vector, sort and remove duplicate words
// and print out that vector.
void findMatches(wordlist dict, grid g, bool debugPrint)
{
    int dimX = g.getSize(0);
    int dimY = g.getSize(1);
    int iX, iY, x, y;
    
    // Timer starts
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    std::vector<std::string> match;
   
    for (int j = 0; j < dimY; j++) {        // Go along Y
        for (int i = 0; i < dimX; i++) {    // Go along X
            for (int k = 0; k < 8; k++) {   // In each direction...
                std::string temp;           // 5 6 7
                x = i, y = j;               // 4 * 0
                switch (k)                  // 3 2 1
                {   // Select direction, see above for explaination
                    case 0: iX = 0;     iY = 1;     break;
                    case 1: iX = 1;     iY = 1;     break;
                    case 2: iX = 1;     iY = 0;     break;
                    case 3: iX = 1;     iY = -1;    break;
                    case 4: iX = 0;     iY = -1;    break;
                    case 5: iX = -1;    iY = -1;    break;
                    case 6: iX = -1;    iY = 0;     break;
                    case 7: iX = -1;    iY = 1;     break;
                    default: undefinedBehavior();
                }
                
                while (1) 
                {
                    temp += g.get(x, y);
                    if (temp.length() > 4) {            // If the word is long enough
                        if (dict.partialSearch(temp)) { // check if it's partially found
                            if(dict.search(temp)) {     // then check if it's entirely found.
                                match.push_back(temp);  // If yes then push it to the vector.
                            }                           // Otherwise just continue.
                        } else break;                   // If it's not partially found
                    }                                   // then move on to next case.
                    // Move to the next cell with wrapping
                    x = posMod(x+iX, dimX); // Please ignore warning here
                    y = posMod(y+iY, dimY); // Please ignore warning here
                }
            }
        }
    }
    
    // Timer ends
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    if (debugPrint)
    {
        // Sort the word vectors and print out results
        quicksort<std::string>(match);
        for (size_t i = 0; i < match.size(); i++) 
        {
            std::cout << i+1 << ": " << match[i] << std::endl;
        }
    }
    
    std::cout << "Found " << match.size() << " non-unique words in " << (double)duration/1000.0f << " seconds.\n";
}

// void findMatchesHash(hashtable<std::string> dict, grid g, bool debugPrint)
// Lookup a grid for any word that is in hastable based dictionary.
// Stores those words in a vector, sort and remove duplicate words
// and print out that vector.
void findMatchesHash(hashtable<std::string> dict, grid g, bool debugPrint)
{
    auto dimX = g.getSize(0);
    auto dimY = g.getSize(1);
    int iX, iY, x, y;
    
    // Timer starts
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    std::vector<std::string> match;
    
    for (int j = 0; j < dimY; j++) {        // Go along Y
        for (int i = 0; i < dimX; i++) {    // Go along X
            for (int k = 0; k < 8; k++) {   // In each direction...
                std::string temp;           // 5 6 7
                x = i, y = j;               // 4 * 0
                switch (k)                  // 3 2 1
                {   // Select direction, see above for explaination
                    case 0: iX = 0;     iY = 1;     break;
                    case 1: iX = 1;     iY = 1;     break;
                    case 2: iX = 1;     iY = 0;     break;
                    case 3: iX = 1;     iY = -1;    break;
                    case 4: iX = 0;     iY = -1;    break;
                    case 5: iX = -1;    iY = -1;    break;
                    case 6: iX = -1;    iY = 0;     break;
                    case 7: iX = -1;    iY = 1;     break;
                    default: undefinedBehavior();
                }
                
                while (temp.length() < 20) {
                    temp += g.get(x, y);
                    if (temp.length() > 4) {            // If the word is long enough
                        if(dict.inList(temp)) {         // then check if it's entirely found.
                            match.push_back(temp);      // If yes then push it to the vector.
                        }                               // Otherwise just continue.
                    }                                   // then move on to next case.
                    // Move to the next cell with wrapping
                    x = posMod(x+iX, dimX); // Please ignore warning here
                    y = posMod(y+iY, dimY); // Please ignore warning here
                }
            }
        }
    }
    
    // Timer ends
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    
    if (debugPrint)
    {
        // Sort the word vectors and print out results
        quicksort<std::string>(match);
        for (size_t i = 0; i < match.size(); i++) 
        {
            std::cout << i+1 << ": " << match[i] << std::endl;
        }
    }
    
    std::cout << "Found " << match.size() << " non-unique words in " << (double)duration/1000.0f << " seconds.\n";
}
