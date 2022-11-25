//  Header file for the class defined for the queue data structure.

#ifndef STACK_H
#define STACK_H

#define SIZE 10000000

template <class T>

class Stack

{

    public:

        T *Array;
        int Capacity;
        int Top;
  
            ~Stack();
            Stack(int Size=SIZE);
            bool push(T X);
            T pop();
            T top();
            bool empty();

};

#endif