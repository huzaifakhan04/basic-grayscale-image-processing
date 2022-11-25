#include<iostream>
#include "Queue.h"
#include "Logger.h"

template <class T>

Queue<T>::~Queue()

{

        logger("Queue destructor called...");
    delete[] this->Array;

}

template <class T>

Queue<T>::Queue(int Size)

{

        logger("Queue constructor called...");
        this->Array=new T[Size];
        this->Capacity=Size;
        this->Front=0;
        this->Rear=-1;
        this->Count=0;

}

template <class T>
  
void Queue<T>::enqueue(T X)

{
        if(isFull())
        {
            std::cout << "Queue overflow!" << std::endl;
            logger("Queue overflow!");
            exit(EXIT_FAILURE);
        }
        this->Rear=(this->Rear+1)%this->Capacity;
        this->Array[this->Rear]=X;
        this->Count++;

}

template <class T>

T Queue<T>::dequeue()

{
        if(isEmpty())
        {
            std::cout << "Queue underflow!" << std::endl;
            logger("Queue underflow!");
            exit(EXIT_FAILURE);
        }
    T X=this->Array[this->Front];
        this->Front=(this->Front+1)%this->Capacity;
        this->Count--;
 
    return X;

}

template <class T>

T Queue<T>::peek()

{
        if(isEmpty())
        {
            std::cout << "Queue underflow!" << std::endl;
            logger("Queue underflow!");
            exit(EXIT_FAILURE);
        }

    return this->Array[this->Front];

}

template <class T>

int Queue<T>::size()

{

    return this->Count;

}

template <class T>

bool Queue<T>::isEmpty()

{

    return (size()==0);

}

template <class T>

bool Queue<T>::isFull()

{

    return (size()==this->Capacity);

}