#include <iostream>
#include "./Libs/EventSymulator.h"

/*
 * Time complexity O(N*lgN)
 * Space complexity O(N)
 *
 * Overview of solution:
 * Each water container is defined by coordinates of two points (opposite vertexes of cuboid).
 * MinPriorityQueue implemented on binary heap act as an event simulator in this case.
 * We simulate flooding of containers to figure out which are filled with water to the full.
 * Each container has two events associated with it. First determines the start of flooding
 * the container, whereas the second - end of this process. Stages of flooding are determined
 * by events occurrences - at those points the amount of water that left for following stages
 * are computed. It's also important to compute the square of "summary" base of cuboid - by
 * adding the base of just started container - or subtracting the one that has just ended up
 * (according to the event extracted from queue). The height of "summary" cuboid is determined
 * by the difference between height of current event and a previous one (point that the height
 * - Y coord is a key in queue). When the simulation ends processing a container - if more er equal
 * to zero amount of water left - the filled container counter is incremented.
 */

using namespace std;

struct Point{
    float X, Y, Z;
};

MinPriorityQueue* ProcessInputEvents(){
    int N;
    scanf("%i", &N);
    // Each container -> two events : begin and end processing
    MinPriorityQueue *q = new MinPriorityQueue(2 * N);
    Point x1, x2;
    Event e1, e2;
    for (int i = 0; i < N; ++i) {
        // Input cuboid in format : (lower - leftmost - the most in front point) x (upper - rightmost - the most in back point)
        scanf("%f %f %f %f %f %f", &x1.X, &x1.Y, &x1.Z, &x2.X, &x2.Y, &x2.Z);

        e1.Type = Begin;
        e1.Key = x1.Y;
        e1.Width = x2.X - x1.X;
        e1.Depth = x1.Z - x2.Z;
        q->Insert(e1);

        e2.Type = End;
        e2.Key = x2.Y;
        e2.Width = x2.X - x1.X;
        e2.Depth = x1.Z - x2.Z;
        q->Insert(e2);
    }
    return q;
}

int NumberOfContainersFull(MinPriorityQueue *Q, float Query){
    int RES = 0;
    // The CapacityPerHUnit variable holds the amount of water at height unit across single stage of simulation
    float SquarePerHUnit, LastHeight;
    // Valid input -> first event is a beginning of container
    Event e = Q->ExtractMin();
    SquarePerHUnit = e.Width * e.Depth;
    LastHeight = e.Key;
    while(!Q->Empty() && Query > 0){
        e = Q->ExtractMin();
        // Update of the amount of water that left (as some amount was used to fill some subset of containers to some level)
        Query -= (e.Key - LastHeight) * SquarePerHUnit;
        LastHeight = e.Key;
        if(e.Type == Begin){
            // this type of event means that we add a container
            SquarePerHUnit += e.Width * e.Depth;
        } else {
            // this type of event means that we probably filled to the full a container (or possibly no water left for this event)
            SquarePerHUnit -= e.Width * e.Depth;
            if(Query >= 0) RES++;
        }
    }
    if(Query > 0) printf("[Warning!] Overflow!\n");
    return RES;
}

int main() {
    // Processing input events
    MinPriorityQueue *Q = ProcessInputEvents();
    // Processing query
    float Query;
    scanf("%f", &Query);
    // Computing answer
    printf("Number of water containers which are full of water: %i\n", NumberOfContainersFull(Q, Query));
    system("pause");
    return 0;
}