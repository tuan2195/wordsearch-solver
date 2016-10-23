//
//  wordlist.h
//  Project3a
//
//  Created by Tuan Dao on 10/6/15.
//  Copyright (c) 2015 Tuan Dao. All rights reserved.
//

#ifndef __Project3a__wordlist__
#define __Project3a__wordlist__

#include <stdio.h>
#include <iostream>
#include <vector>
#include "hashtable.hpp"

class wordlist
{
public: // See wordlist.cpp for declration and explaination
    wordlist();
    void readFromFile(std::string filename);
    void sortInsertion(void);
    void sortQuick(void);
    void sortMerge(void);
    void sortHeap(void);
    friend std::ostream& operator<<(std::ostream& os, const wordlist& wl);
    bool search(std::string key);
    bool partialSearch(std::string key);
    void toHashtable(hashtable<std::string> &h);
private:
    std::vector<std::string> v; // string vector to store words
};


#endif /* defined(__Project3a__wordlist__) */
