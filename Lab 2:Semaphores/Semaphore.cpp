#Author : Damien Doran
#Date : 23/10/20


/*! \file Semaphore.cpp
    \brief A Documented file detailing how the Wait and Signal function work.

*/

#include "Semaphore.h"
/*! \class Semaphore
    \brief A Semaphore Implementation

   Uses C++11 features such as mutex and condition variables to implement Semaphore

*/



/*!
      The Semaphore wait function is used to decrement the Semaphore integer (s).
      if (s) is now negative the current process is blocked and placed in a q.
*/

void Semaphore::Wait()
{
      std::unique_lock< std::mutex > lock(m_mutex);
      m_condition.wait(lock,[&]()->bool{ return m_uiCount>0; });
      --m_uiCount;
}

template< typename R,typename P >
bool Semaphore::Wait(const std::chrono::duration<R,P>& crRelTime)
{
      std::unique_lock< std::mutex > lock(m_mutex);
      if (!m_condition.wait_for(lock,crRelTime,[&]()->bool{ return m_uiCount>0; })){
	  return false;
      }
      --m_uiCount;
      return true;
}

/*!
      The Semaphore Signal function increments (s).
      if (s) <= 0, then the next blocked process/thread in the queue
      is dequeued and becomes unblocked
*/

void Semaphore::Signal()
{
      std::unique_lock< std::mutex > lock(m_mutex);
      ++m_uiCount;
      m_condition.notify_one();
}
