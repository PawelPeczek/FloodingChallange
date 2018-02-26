#ifndef EVENTSYMULATOR_LIBRARY_H
#define EVENTSYMULATOR_LIBRARY_H

enum EventType{
    Begin,
    End
};

struct Event{
    float Key;
    float Width;
    float Depth;
    EventType Type;
};

/*
 * In this DS it is assumed that before using Insert()/ExtractMin() - appropriate
 * operations Full()/Empty() are done!
 */

class MinPriorityQueue {
    Event *T;
    int N; // number of elements currently in PriorityQueue
    int MaxSize; // MAX size of PriorityQueue
    int Left(int);
    int Right(int);
    int Parent(int);
public:
    MinPriorityQueue();
    MinPriorityQueue(int);
    ~MinPriorityQueue();
    Event Minimum();
    Event ExtractMin();
    bool Empty();
    bool Full();
    void MinHeapify(int idx);
    void DecreaseKey(int idx, float new_key);
    void Insert(Event e);
};

#endif