/*
#Author : Damien Doran
#Date : 13/11/20
 This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/.
*/

/*! \file main.cpp
*/

#include "SafeBuffer.h"
#include "Semaphore.h"
#include "Event.h"
#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>


static const int num_threads = 15;
const int size=20;
int num = 0;


/*! \fn producer
    \brief Creates events and adds them to buffer
*/

void producer(std::shared_ptr<SafeBuffer> queue, std::shared_ptr<Semaphore> mutex,
 std::shared_ptr<Semaphore> consumer, std::shared_ptr<Semaphore> space)
{
  /*
 The producer method uses a mutex to allow one thread at a time while adding values to
  the queue, each thread with a different value
 */
  mutex->Wait();
  num += 10;
  std::cout << "Enqueue : ";
  queue->enqueue(num);
  mutex->Signal();
  consumer->Signal();
}

/*! \fn consumer
    \brief Takes events from buffer and consumes them
*/

void consumer(std::shared_ptr<SafeBuffer> queue, std::shared_ptr<Semaphore> mutex,
 std::shared_ptr<Semaphore> consumer, std::shared_ptr<Semaphore> space)
{
  /*
 The consumer method uses a mutex to allow one thread at a time which will remove
 an element from the queue
 */
  consumer->Wait();
  mutex->Wait();
  std::cout << "Dequeued";
  queue->dequeue();
  mutex->Signal();
}

void testingQueue(SafeBuffer queue)
{
  /*
 this method is to demonstrate the functions used on a testing queue
 */
  queue.printQueue();
  queue.details();
  queue.enqueue(1);
  queue.details();
  queue.enqueue(2);
  queue.details();
  queue.enqueue(3);
  queue.details();
  queue.enqueue(4);
  queue.details();
  queue.enqueue(5);
  queue.details();
  queue.enqueue(5);
  queue.details();
  queue.enqueue(5);
  queue.details();
}

int main(void)
{
  std::vector<std::thread> vproducer(num_threads);
  std::vector<std::thread> vcsonsumer(num_threads);
  std::shared_ptr<SafeBuffer> queue (new SafeBuffer());
  std::shared_ptr<Semaphore> mutex (new Semaphore(1));
  std::shared_ptr<Semaphore> consumers (new Semaphore(0));
  std::shared_ptr<Semaphore> space (new Semaphore(1));

  int i = 0;
  for(std::thread& t : vproducer)
  {
    t=std::thread(producer,queue,mutex,consumers,space);
  }

  for(std::thread& t : vcsonsumer)
  {
    t=std::thread(consumer,queue,mutex,consumers,space);
  }

  for(auto& v :vproducer)
  {
    v.join();
  }

  for(auto& v : vcsonsumer)
  {
    v.join();
  }

  return 0;
}
