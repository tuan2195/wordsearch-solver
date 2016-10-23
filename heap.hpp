//
//  heap.hpp
//  Project3b
//
//  Created by Tuan Dao on 10/16/15.
//  Copyright © 2015 Tuan Dao. All rights reserved.
//

#ifndef heap_hpp
#define heap_hpp

#include <stdio.h>
#include <vector>

template <typename T> class heap
{
public:
    int parent(int i);
    int left(int i);
    int right(int i);
    T getItem(int i);
    void push(T t);
    void init(std::vector<T> &s);
    void maxheapify(int i);
    void buildMaxheap(void);
    void initMaxheap(std::vector<T> &s);
    void minheapify(int i);
    void buildMinheap(void);
    void initMinheap(std::vector<T> &s);
    void sort(void);
private:
    int heapsize;
    std::vector<T> v;
};

// Index-return functions
template <typename T> int heap<T>::parent(int i)
{
    return i/2;
}

template <typename T> int heap<T>::left(int i)
{
    return 2*i;
}

template <typename T> int heap<T>::right(int i)
{
    return 2*i+1;
}

// Object-return function
template <typename T> T heap<T>::getItem(int i)
{
    return v[i];
}

// Initiazlize function
// Put all the elements in the vector s into the vector v
template <typename T> void heap<T>::init(std::vector<T> &s)
{
    v.clear();
    heapsize = (int)s.size();
    for (int i = 0; i < heapsize; i++) {
        v.push_back(s[i]);
    }
}

// Maxheapify function
// Rearrages the vector so it has the heap property.
// Starts at index i.
template <typename T> void heap<T>::maxheapify(int i)
{
    int l = left(i), r = right(i), largest = i;
    if (l < heapsize && v[l] > v[largest]) {
        largest = l;
    }
    if (r < heapsize && v[r] > v[largest]) {
        largest = r;
    }
    if (largest != i) {
        T temp = v[i];
        v[i] = v[largest];
        v[largest] = temp;
        maxheapify(largest);
    }
}

// BuildMaxheap function
// Build a max heap from the vector object.
template <typename T> void heap<T>::buildMaxheap(void)
{
    for (int i = heapsize/2; i >= 0; i--) {
        maxheapify(i);
    }
}

// initMaxheap function
// Build a max heap from the passed vector.
template <typename T> void heap<T>::initMaxheap(std::vector<T> &s)
{
    init(s);
    buildMaxheap();
}

// Minheapify function
// Rearrages the vector so it has the heap property.
// Starts at index i.
template <typename T> void heap<T>::minheapify(int i)
{
    int l = left(i), r = right(i), smallest = i;
    if (l < heapsize && v[l] < v[smallest]) {
        smallest = l;
    }
    if (r < heapsize && v[r] < v[smallest]) {
        smallest = r;
    }
    if (smallest != i) {
        T temp = v[i];
        v[i] = v[smallest];
        v[smallest] = temp;
        maxheapify(smallest);
    }
}


// BuildMinheap function
// Build a min heap from the vector object.
template <typename T> void heap<T>::buildMinheap(void)
{
    for (int i = heapsize/2; i >= 0; i--) {
        minheapify(i);
    }
}

// initMinheap function
// Build a min heap from the passed vector.
template <typename T> void heap<T>::initMinheap(std::vector<T> &s)
{
    init(s);
    buildMinheap();
}

// Sort function
// Performs a heapsort on the heap by using maxheapify function
// Rearranges the array to the osrted order.
template <typename T> void heap<T>::sort(void)
{
    buildMaxheap();
    std::vector<T> tv;
    T temp;
    int size = (int)v.size()-1;
    for (int i = size; i > 0; i--) {
        temp = v[i];
        v[i] = v[0];
        v[0] = temp;
        heapsize--;
        maxheapify(0);
    }
    heapsize = (int)v.size();
}
#endif /* heap_hpp */
