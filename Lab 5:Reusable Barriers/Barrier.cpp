// Barrier.cpp --- 
// 
// Filename: Barrier.cpp
// Description: 
// Author: Joseph
// Maintainer: 
// Created: Tue Jan  8 12:14:02 2019 (+0000)
// Version: 
// Package-Requires: ()
// Last-Updated: Tue Jan  8 12:15:21 2019 (+0000)
//           By: Joseph
//     Update #: 2
// URL: 
// Doc URL: 
// Keywords: 
// Compatibility: 
// 
// 

// Commentary: 
// 
// 
// 
// 

// Change Log:
// 
// 
// 
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.
// 
// 

// Code:
#include "Semaphore.h"
#include "Barrier.h"
#include <iostream>

/*!
    this method will destroy the barrier when finished so there is no memory wasted
    */
Barrier::~Barrier()
{
}
/*!
    Phase one, the mutex lock was initialised with 1 so when wait is called by the first thread
    it can be locked, the value is incremented, compared. if not correct number of threads entered
    the turnstile allows another thread in next to continue same process
    */
void Barrier::phaseOne()
{
    theLock.Wait();
    ++threadCount;
    if( threadCount == threadTotal)
    {
        std::cout << std::endl;
        turnstileTwo.Wait();
        turnstileOne.Signal();
    }
    theLock.Signal();
    turnstileOne.Wait();
    turnstileOne.Signal();
}

void Barrier::phaseTwo()
{
    theLock.Wait();
    --threadCount;
    if(threadCount == 0)
    {
        turnstileOne.Wait();
        turnstileTwo.Signal();
    }
    if(threadCount < 0)
    {
        std::cout << std::endl;
    }
    theLock.Signal();
    turnstileTwo.Wait();
    turnstileTwo.Signal();
}

void Barrier::wait()
{
    phaseOne();
    phaseTwo();
}


// 
// Barrier.cpp ends here
