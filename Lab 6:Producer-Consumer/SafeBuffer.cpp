#include "SafeBuffer.h"
#include <iostream>

SafeBuffer::~SafeBuffer() = default;

/*! checks if the queue is empty*/
bool SafeBuffer::isEmpty()
{
    if(head == 0 && tail == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*! checks if the queue is full*/
bool SafeBuffer::isFull()
{
    if(tail == size-1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*! adds an element to the queue*/
void SafeBuffer::enqueue(int val)
{
    if(!isFull())
    {
        arr[tail] = val;
        tail ++;
        backQueue();
    }
}

/*! removes an element from the queue*/
void SafeBuffer::dequeue()
{
    if(!isEmpty())
    {
        frontQueue();
        for(int i = head; i < tail; i ++)
        {
            arr[i] = arr[i+1];
        }
        tail --;
    }
}

/*! outputs the contents of the queue*/
void SafeBuffer::printQueue()
{
    for(int i = 0; i < tail; i ++)
    {
        std::cout << arr[i] << std::endl;
    }
}

/*! outputs first element of the queue*/
void SafeBuffer::frontQueue()
{
    if(!isEmpty())
    {
        std::cout << arr[head] << std::endl;
    }
}

void SafeBuffer::backQueue()
{
    if(!isEmpty())
    {
        std::cout << arr[tail-1] << std::endl;
    }
}

/*! displays details of the queue*/
void SafeBuffer::details()
{
    std::cout << "Tail : " << tail << std::endl;
    std::cout << "Head : " << head << std::endl;
    std::cout << "Size : " << sizeof(arr) << std::endl;
}