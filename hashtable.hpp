//
//  hashtable.hpp
//  Project3b
//
//  Created by Tuan Dao on 10/18/15.
//  Copyright © 2015 Tuan Dao. All rights reserved.
//

#ifndef hashtable_hpp
#define hashtable_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

template <typename T> class hashtable
{
public:
    hashtable(int s);
    void addItem(T item);
    void deleteItem(T item);
    bool inList(T item);
    int hash(T item);
    void setSize(int s);
private:
    std::vector<std::vector<T> > table;
    int tableSize;
};

template <typename T> hashtable<T>::hashtable(int s)
{
    setSize(s);
}

template <typename T> void hashtable<T>::setSize(int s)
{
    tableSize = s;
    table.resize(s);
}

template <typename T> int hashtable<T>::hash(T item)
{
    std::hash<T> hasher;
    return hasher(item) % tableSize;
}

template <typename T> bool hashtable<T>::inList(T item)
{
    int h = hash(item);
    int length = (int)table[h].size();
    for (int i = 0; i < length; i++) {
        if (table[h][i] == item) {
            return 1;
        }
    }
    return 0;
}

template <typename T> void hashtable<T>::addItem(T item)
{
    if (!inList(item))
        table[hash(item)].push_back(item);
}

template <typename T> void hashtable<T>::deleteItem(T item)
{
    if (inList(item)) {
        int h = hash(item);
        int length = table[h].size();
        int i;
        while (i < length) {
            if (table[h][i] == item) {
                table[h].erase(table[h].begin()+i);
            } else i++;
        }
    }
}
#endif /* hashtable_hpp */
