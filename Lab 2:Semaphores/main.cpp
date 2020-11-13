#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <unistd.h>

/*! \class Main
    \brief An Implementation of Threads Using Semaphores, containing two tasks displaying how a thread may access a function

   Uses C++11 features such as mutex and condition variables to implement
/ Semaphores in thread functions

*/
/*! displays a message first*/
void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay){
  sleep(delay);
  std::cout <<"I ";
  std::cout << "must ";
  std::cout << "print ";
  std::cout << "first"<<std::endl;
  theSemaphore->Signal(); 
  
/*! 
  This function is used for the thread to generate output, the method signal is
  used to indicate something has happened. Guaranteeing the critical section in
   the code will run before the next thread
*/
}
/*! displays a message second*/
void taskTwo(std::shared_ptr<Semaphore> theSemaphore){
  theSemaphore->Wait();
  std::cout <<"This ";
  std::cout << "will ";
  std::cout << "appear ";
  std::cout << "second"<<std::endl;

  /*! 
  This function is used for the thread to generate output, the method wait is
  used to indicate something needs to happen before continuing, Guaranteeing the critical section in
   the code will run before the next thread
*/

}


int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem( new Semaphore);
  /**< Launch the threads  */
  int taskOneDelay=5;
  threadOne=std::thread(taskTwo,sem);
  threadTwo=std::thread(taskOne,sem,taskOneDelay);
  std::cout << "Launched from the main\n";
   /**< Wait for the threads to finish */
  threadTwo.join();
  threadOne.join();
  return 0;
}
