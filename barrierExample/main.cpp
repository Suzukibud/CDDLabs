#Author : Damien Doran
#Date : 13/11/20


/*! \file main.cpp
*/
/*
 This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/.
*/
/*!

*/

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>


static const int num_threads = 100;
int barrierCount;

/*! \fn updateTask
    \brief An Implementation of a Barrier using Semaphores

//   Uses C++11 features such as mutex and condition variables to implement an example of a rendezvous for threads

*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void updateTask(std::shared_ptr<Semaphore> aMutexSem, std::shared_ptr<Semaphore> firstSem, int taskNum, int threadCount){
    std::cout <<taskNum;

    //BARRIER CODE
    aMutexSem->Wait();
    barrierCount ++;
    if(barrierCount == threadCount){//all are here now
        std::cout<< std::endl;
        barrierCount--;
        firstSem->Signal();
        aMutexSem->Signal();
        //firstSem->Wait();
    }else{//Wait for the rest to arrive
        aMutexSem->Signal();
        firstSem->Wait();
        aMutexSem->Wait();
        --barrierCount;
        if(barrierCount!=0)firstSem->Signal();
        aMutexSem->Signal();
    }
    aMutexSem->Signal();
    /*!
        barrier here --all task numbers printed before any A's
        if everyone else is here then we all go
        if not we wait!!
        BARRIER CODE END
    */
    std::cout << "A" << std::endl;
}


int main(void){
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Semaphore> aSemaphore( new Semaphore);
  std::shared_ptr<Semaphore> aMutexSem( new Semaphore(1));
  /**< Launch the threads  */
  int i=0;
  barrierCount =0;
  for(std::thread& t: vt){
      t=std::thread(updateTask,aMutexSem, aSemaphore,i++,num_threads);
  }

  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  return 0;
}
