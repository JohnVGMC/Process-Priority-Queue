#include "ReadyQueue.h"
#include "PCB.h"
#include <iostream>

//Default Constructor
ReadyQueue::ReadyQueue()
{
  // only thing to do is initialize count
  count = 0;
}

//Destructor
ReadyQueue::~ReadyQueue()
{
  // nothing to do
}

// the PCB parameter is added as the last element of the ReadyQueue
// Then it is trickled up to put it in it's proper place in the queue according to its priority
void ReadyQueue::insertProc(PCB newProcess)
{
  if(count < QUEUE_SIZE) //if the Queue is not already full (should ONLY happen when every process is already in the queue)
    {
      //count will already hold the value of the index right after the last element of the queue.
      queue[count] = newProcess;
      count++;
      trickleUp();
    }
  else{ //An attempt to add a PCB to the queue was made, even though it's already full. This should NOT happen because then every process is already in the queue. Print an Error
    std::cout << "ERROR: Queue is already full." << std::endl;
  }
}

//Removes the first element of the array (the highest priority), then proceeds to call to reheapify the tree.
//the main function will already check .size() to see whether it's already empty
PCB ReadyQueue::removeHighestProc()
{
  PCB removedProc = queue[0];
  count--; // The last element hasn't been "removed" yet, as it makes its way to the top and trickle down to its proper location overwriting the 0th's index's contents 
  reheapify(); // After reheapify, the previously last index will now be considered nonexistant to the queue outside count's scope (only being relevant when an item is added and overwriting its previous contents)
  return removedProc;
}

//Returns the value of count
int ReadyQueue::size()
{
  return count;
}

//Displays the contents of the ReadyQueue (each PCB's PID and priorities are shown)
void ReadyQueue::displayQueue()
{
  std::cout << "ReadyQueue:\n";
  if(count > 0)
    {
      std::cout << "[";
      for(int i = 0; i < count; i++)
	{
	  std::cout << " (#" << queue[i].getPID() << " Priority " << queue[i].getPriority() << ")";
	}
      std::cout << " ]" << std::endl;
    }
  else // Queue is empty
    {
      std::cout << "[ empty ]" << std::endl;
    }
}

//Returns true if the number is even (if dividing it by 2 yields no remainder)
//Otherwise, false will be returned
bool ReadyQueue::isEven(int num)
{
  if(num % 2 == 0)
    return true;
  return false;
}

//Checks the priority of the Left and Right children of the parent process
//Returns the index of the Left child if it has higher priority (it's value for priority is smaller) than the Right child
//Returns Right child's index instead, assumes that has priority or even equal priority
int ReadyQueue::smallerChild(int parent)
{
  int Lchild = (parent * 2) + 1;
  int Rchild = (parent * 2) + 2;
  if(queue[Lchild].getPriority() < queue[Rchild].getPriority()) // if the Left child has a smaller priority number, meaning higher priority
    return Lchild;
  return Rchild;
}

//Moves the newly added process up the queue in proper order until it's hit it's highest possible spot (either below its higher priority processes or already reaching the top index)
void ReadyQueue::trickleUp()
{
  int currentIndex = count - 1; // Points to the index of the newly added element of the queue
  int parentIndex;
  if(isEven(currentIndex))
    parentIndex = (currentIndex - 2) / 2;
  else
    parentIndex = (currentIndex - 1) / 2;
  while( currentIndex > 0 ) //Continue going only when you haven't reached the top index already
    {
      if( queue[currentIndex].getPriority() < queue[parentIndex].getPriority() ) //If the current Child has a lower priority value (meaning higher priority)
	{
	  // swap the two PCBs of the child and parent
	  PCB temp = queue[currentIndex];
	  queue[currentIndex] = queue[parentIndex];
	  queue[parentIndex] = temp;
	  // the current index is now the parentIndex, also calculate the new parent index
	  currentIndex = parentIndex;
	  if(isEven(currentIndex))
	    parentIndex = (currentIndex - 2) / 2;
	  else
	    parentIndex = (currentIndex - 1) / 2;
	}
      else //the parent is already at a higher priority
	{
	  currentIndex = 0; // do nothing else than to set the index to 0 to exit the loop
	}
    }
}

void ReadyQueue::reheapify()
{
  // set index values
  int currentIndex = 0; //trickling down the top element
  int lastElement = count; // since count was already decremented, count points to the last index that will overwrite the top element
  
  //replace the top element with the last element
  queue[currentIndex] = queue[lastElement];
  lastElement--;

  //Trickle the element down until it's either reached the bottom, or reached a point where it's a higher priority than its children
  //At this point, the old last element has already replaced the top element, and count was already adjusted to indicate that the old last element is now nonexistant in the queue
  bool keepRunning = true;
  while(keepRunning)
    {
      if( ((currentIndex*2)+1) <= lastElement ) // currentElement has at least a left child
	{
	  int childElem;
	  if( ((currentIndex*2)+2) <= lastElement ) // currentElement also has a right child
	    childElem = smallerChild(currentIndex);
	  else // only has a left child
	    childElem = (currentIndex * 2) + 1;

	  // child index is set for comparison
	  if(queue[currentIndex].getPriority() > queue[childElem].getPriority()) // if the parent has a bigger priority value (lower priority)
	    {
	      PCB temp = queue[currentIndex];
	      queue[currentIndex] = queue[childElem];
	      queue[childElem] = temp;
	      // set the new index
	      currentIndex = childElem;
	    }
	  else // parent already has higher priority than its children
	    {
	      keepRunning = false;
	    }
	}
      else // element has already reached a bottom
	{
	  keepRunning = false;
	}
    }
}
