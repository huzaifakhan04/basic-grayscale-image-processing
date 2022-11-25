#include<iostream>
#include "Stack.h"
#include "Logger.h"

template <class T>

Stack<T>::~Stack()

{

        logger("Stack destructor called...");
    delete [] this->Array;

}

template <class T>

Stack<T>::Stack(int Size)

{

        logger("Stack constructor called...");
        this->Array=new T[Size];
        this->Capacity=Size;
        Top=-1;

}

template <class T>
  
bool Stack<T>::push(T X)

{

        if(this->Top>=(this->Capacity-1))
        {

                std::cout << "Stack overflow!";
                logger("Stack overflow!");
            return false;
        }
        else
        {
                this->Array[++Top]=X;
            return true;
        }

}

template <class T>
  
T Stack<T>::pop()

{

        if(this->Top<0)
        {
                std::cout << "Stack underflow!";
                logger("Stack underflow!");
            return (T)0;
        }
        else
        {
                T X=this->Array[Top--];
            return X;
        }

}

template <class T>

T Stack<T>::top()

{

        if(this->Top<0)
        {
                std::cout << "Stack is empty!";
                logger("Stack is empty!");
            return (T)0;
        }
        else
        {
                T X=this->Array[Top];
            return X;
        }

}

template <class T>

bool Stack<T>::empty()

{

    return (this->Top<0);

}