#ifndef READYQUEUE_H
#define READYQUEUE_H

#include "PCB.h"
// The way that the priority queue is being set up is via a Heap Tree, based on Rika Yoshii's pqueue.h file mixed with functions needed for ReadyQueue

const int QUEUE_SIZE = 20; // Set as the same number of processes as the PCB Table for Assignment 1

class ReadyQueue
{
 private:
  PCB queue[QUEUE_SIZE];
  int count;

  // Utility functions for operating the priority queue
  
  // Sorts the priority queue via "heap sort" after a process ID was removed by reheapifying it.
  void reheapify();
  
  // Trickles a PCB up the priority queue After it was added to the rear in order to place it in its proper position according to its priority
  void trickleUp();

  // Returns whether a value is even or not (Needed for finding an elements's "parent" for heap sorting
  // PARAMETER: integer that is being checked if its even or not 
  bool isEven(int);

  // Returns the location of the smaller child of an element (meaning higher priority) by comparing the element's L and R children
  // PARAMETER: integer whose value is the location of the parent element in the queue
  int smallerChild(int);

 public:
  //Default constructor
  ReadyQueue();

  //Destructor
  ~ReadyQueue();

  //Adds the PCB of a process into the ReadyQueue
  //PARAMETER: PCB that is being added to the ReadyQueue
  void insertProc(PCB);

  //Removes and returns the PCB with the highest priority from the queue
  PCB removeHighestProc();

  //Returns the number of elements in the ReadyQueue
  int size();

  //Displays the IDs and Priorities of processes in the queue.
  void displayQueue();
};

#endif //READYQUEUE_H
