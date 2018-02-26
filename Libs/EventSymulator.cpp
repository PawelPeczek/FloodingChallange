#include "EventSymulator.h"
#include <iostream>
#include <cfloat>

int MinPriorityQueue::Left(int i) {
    return 2 * i + 1;
}

int MinPriorityQueue::Right(int i) {
    return 2 * i + 2;
}

int MinPriorityQueue::Parent(int i) {
    return (i - 1) / 2;
}

MinPriorityQueue::MinPriorityQueue() : MinPriorityQueue::MinPriorityQueue(50){}

MinPriorityQueue::MinPriorityQueue(int max_size) {
    T = new Event[max_size];
    MaxSize = max_size;
    N = 0;
}

MinPriorityQueue::~MinPriorityQueue() {
    delete[] T;
}

Event MinPriorityQueue::Minimum() {
    return T[0];
}

Event MinPriorityQueue::ExtractMin() {
    Event RES = T[0];
    std::swap(T[0], T[N - 1]);
    N--;
    MinHeapify(0);
    return RES;
}

bool MinPriorityQueue::Empty() {
    return N == 0;
}

bool MinPriorityQueue::Full() {
    return N == MaxSize;
}

void MinPriorityQueue::MinHeapify(int idx) {
    int l = Left(idx);
    int r = Right(idx);
    int min = idx;
    if(l < N && T[l].Key < T[idx].Key) min = l;
    if(r < N && T[r].Key < T[min].Key) min = r;
    if(min != idx){
        std::swap(T[idx], T[min]);
        MinHeapify(min);
    }
}

void MinPriorityQueue::DecreaseKey(int idx, float new_key) {
    // only if this operation makes sense
    if(T[idx].Key > new_key){
        T[idx].Key = new_key;
        // while T[idx] is not a root of heap and MinHeap constrains are violated
        while(idx > 0 && T[Parent(idx)].Key > T[idx].Key){
            std::swap(T[idx], T[Parent(idx)]);
            idx = Parent(idx);
        }
    }
}

void MinPriorityQueue::Insert(Event e) {
    float new_key = e.Key;
    e.Key = FLT_MAX ;
    T[N] = e;
    DecreaseKey(N, new_key);
    N++;
}