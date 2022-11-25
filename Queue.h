//  Header file for the class defined for the queue data structure.

#ifndef QUEUE_H
#define QUEUE_H

#define SIZE 10000000

template <class T>

class Queue

{

    public:

        T *Array;
        int Capacity;
        int Front;
        int Rear;
        int Count;
        
            Queue(int Size=SIZE);
            ~Queue();
            void enqueue(T X);
            T dequeue();
            T peek();
            int size();
            bool isEmpty();
            bool isFull();

};

#endif