//
//  searchHelper.h
//  Project3a
//
//  Created by Tuan Dao on 10/10/15.
//  Copyright (c) 2015 Tuan Dao. All rights reserved.
//

#ifndef Project3a_searchHelper_h
#define Project3a_searchHelper_h

// BINARY SEARCH HELPER FUNCTIONS

bool pSearch(std::vector<std::string> &v, std::string key, int length, int right, int left)
{
    int pos = (right+left)/2;
    int len = (int)key.length();
    
    while (key.compare(0, len, v[pos], 0, len) && (right <= left)) {
        if (key.compare(0, len, v[pos], 0, len) < 0) {
            left = pos - 1;
        } else {
            right = pos + 1;
        }
        pos = (left+right)/2;
    }
    
    if (right <= left) {
        if (key.compare(0, len, v[pos], 0, len) == 0) {
            return 1;
        } else return 0;
    } else return 0;
    return 0;
}

bool bSearch(std::vector<std::string> &v, std::string key, int right, int left)
{
    int pos = (right+left)/2;
    while (!(key == v[pos]) && (right <= left)) {
        if (key.compare(v[pos]) < 0) {
            left = pos - 1;
        } else {
            right = pos + 1;
        }
        pos = (left+right)/2;
    }
    
    if (right <= left) {
        if (key == v[pos]) {
            return 1;
        } else return 0;
    } else return 0;
    return 0;
}

#endif
