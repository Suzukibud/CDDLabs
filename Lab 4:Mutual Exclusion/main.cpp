#Author : Damien Doran
#Date : 13/11/20

/*
 This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/.
*/

/*! \file main.cpp
*/

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>


static const int num_threads = 10;
int sharedVariable=0;
std::shared_ptr<Semaphore> mutex ( new Semaphore(1));


/*! \fn updateTask
    \brief An Implementation of Mutual Exclusion using Semaphores

   Uses C++11 features such as mutex and condition variables to implement an example of a mutex for threads

*/
/*! Updates the variable allowing it to be updated within a mutex
    In updateTask, the sharedVariable value begins at one and as each thread accesses this 
    value within the loop, increments it. The mutex ensures only one thread at a time.
*/
void updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates){
  for(int i=0;i<numUpdates;i++){
    mutex->Wait();
    sharedVariable ++;
    mutex->Signal();
  }
}


int main(void){
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Semaphore> aSemaphore( new Semaphore);
  /**< Launch the threads  */
  int i=0;
  for(std::thread& t: vt){
    t=std::thread(updateTask,aSemaphore,1000);
  }
  std::cout << "Launched from the main\n";
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
