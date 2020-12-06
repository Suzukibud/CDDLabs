/* SafeBuffer.h --- 
 * 
 * Filename: SafeBuffer.h
 * Description: 
 * Author: Damien Doran
 */


/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Code: */
#include <array>

class SafeBuffer
{
    /* Declaring Queues attributes */
    int head;
    int tail;
    int size;
    int arr[1000];

    public: SafeBuffer()
    {
        head = 0;
        tail = 0;
        size = 1000;
        arr[0] = 0;
    }
    /* Declaring queues methods */
    ~SafeBuffer();
    bool isEmpty();
    bool isFull();
    void enqueue(int val);
    void dequeue();
    void printQueue();
    void frontQueue();
    void backQueue();
    void details();
};



/* SafeBuffer.h ends here */
