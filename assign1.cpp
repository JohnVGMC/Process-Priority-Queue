///////////////////////////////////////
// John Calderon
// 16 September 2017
// CS 433 - Assignment 1
// 
// This program implements a table of Process Control Blocs (PCBs)
// and a ReadyQueue that utilizes a PCB's Priority value to give
// precedence to what job is popped from the queue.
// Said ReadyQueue is implemented as an array with the functionality
// of a Heap Tree so that when jobs are added and removed,
// the Heap Tree keeps the highest priority jobs at the front
// of the ReadyQueue with an ideal access time of O(log N)
// This efficiency is tested with a 1,000,000 iterations test
// that runs 1,000,000 add or remove commands and prints the final
// contents of the ReadyQueue as well as the total time runnning
// the program.
///////////////////////////////////////



#include "PCB.h"
#include "ReadyQueue.h"
#include <string>
#include <iostream> // cin & cout
#include <stdlib.h> // srand, rand
#include <sys/time.h> // for gettimeofday

const int TABLE_SIZE = 20;

using namespace std;

//Displays all the elements of the PCB table
//TABLE_SIZE already defines the size of the table
void displayPCBTable(PCB table[])
{
  cout << "--- PCB Table ---\nPID\tPriority\tState\n";
  for(int i = 0; i < TABLE_SIZE; i++)
    {
      cout << table[i].getPID() << "\t" << table[i].getPriority() << "\t\t";
      switch(table[i].getState())
	{
	case NEW:
	  cout << "NEW\n";
	  break;
        case READY:
          cout << "READY\n";
          break;
        case RUNNING:
          cout << "RUNNING\n";
          break;
        case WAITING:
          cout << "WAITING\n";
          break;
        case TERMINATED:
          cout << "TERMINATED\n";
          break;
	default:
	  cout << "INVALID\n";
	  break;
	}
    }
  cout << "-----------------" << endl;
}

int main()
{
  //Initialize the PCB Table
  PCB pcb_table[TABLE_SIZE];
  PCB lastRunningProcess; //PCB last removed from the queue that's running (only reading its PID, the table entry is what gets updated)
   
  // --- FIRST TEST ---
  cout << "TEST 1\n";
  //Set the PIC of each process in the table to their respective indices.
  //Also sets their priority to the value of their PIDs
  //State is already set to new for every entry when they were created.
  for(int i = 0; i < TABLE_SIZE; i++)
    {
      pcb_table[i].setPID(i+1);
      pcb_table[i].setPriority(i+1);
    }
  //Create ReadyQueue q1
  ReadyQueue q1;
  // (a) add processes 5, 1, 8, 11 & display q1
  pcb_table[4].setState(READY); q1.insertProc(pcb_table[4]);
  pcb_table[0].setState(READY); q1.insertProc(pcb_table[0]);
  pcb_table[7].setState(READY); q1.insertProc(pcb_table[7]);
  pcb_table[10].setState(READY); q1.insertProc(pcb_table[10]);
  q1.displayQueue();
  // (b) Remove the highest priority process and display q1;
  lastRunningProcess = q1.removeHighestProc();
  pcb_table[lastRunningProcess.getPID()-1].setState(RUNNING);
  q1.displayQueue();
  // (c) Remove the highest priority process and display q1
  // Change the previously running process from RUNNING to WAITING
  pcb_table[lastRunningProcess.getPID()-1].setState(WAITING);
  lastRunningProcess = q1.removeHighestProc();
  pcb_table[lastRunningProcess.getPID()-1].setState(RUNNING);
  q1.displayQueue();
  // (d) Insert processes 3, 7, 2, 12, 9 to q1
  pcb_table[2].setState(READY); q1.insertProc(pcb_table[2]); q1.displayQueue();
  pcb_table[6].setState(READY); q1.insertProc(pcb_table[6]);q1.displayQueue();
  pcb_table[1].setState(READY); q1.insertProc(pcb_table[1]); q1.displayQueue();
  pcb_table[11].setState(READY); q1.insertProc(pcb_table[11]); q1.displayQueue();
  pcb_table[8].setState(READY); q1.insertProc(pcb_table[8]); q1.displayQueue();
  // (e) One by one remove the process with the highest priority from the queue q1 and display it after each removal
  while(q1.size() > 0)
    {
      pcb_table[lastRunningProcess.getPID()-1].setState(WAITING);
      lastRunningProcess = q1.removeHighestProc();
      pcb_table[lastRunningProcess.getPID()-1].setState(RUNNING);
      q1.displayQueue();
    }

  // --- TEST 2 ---

  // initialize random seed
  srand (time(NULL));
  // First randomly select 10 process from the pcb_table and add them into q1
  int processToInsert, newPriority;
  for(int i = 1; i <= 10; i++)
    {
      processToInsert = (rand() % TABLE_SIZE); // random index 0-19 for PIDs 1-20 respectively
      while( pcb_table[processToInsert].getState() == READY ) // sequentially search for a PID that's not already in the ready queue, should the random pick already exists in the queue (only when the queue isn't already full)
	{
	  processToInsert = (processToInsert+1) % TABLE_SIZE;
	}
      //but assign each process a random initial priority between 1 and 50
      newPriority = (rand() % 50) + 1;
      pcb_table[processToInsert].setPriority(newPriority);
      pcb_table[processToInsert].setState(READY);
      q1.insertProc(pcb_table[processToInsert]);
    }

  //1,000,000 ITERATIONS TEST
  //To keep track of how long the program runs for
  cout << "\n1,000,000 Iterations Test\n" << endl;

  struct timeval startTime, FinishTime;      
  gettimeofday(&startTime, NULL);

  //Randomly decide to remove a process from or add a process to the ready queue with equal probability
  int choice;
  for(int i = 0; i < 1000000; i++)
    {
      choice = rand() % 2; // 0 for Remove, 1 for Add
      if(choice == 1) //ADD INSTRUCTION
	{
	  if(q1.size() < TABLE_SIZE) //only run if the queue isn't full already (meaning every instruction isn't already in the ready queue)
	    {
	      processToInsert = (rand() % TABLE_SIZE);
	      while( pcb_table[processToInsert].getState() == READY ) // sequentially search for a PID that's not already in the ready queue
		{
		  processToInsert = (processToInsert+1) % TABLE_SIZE;
		}
	      newPriority = (rand() % 50) + 1;
	      pcb_table[processToInsert].setPriority(newPriority);
	      pcb_table[processToInsert].setState(READY);
	      q1.insertProc(pcb_table[processToInsert]);
	    }
	}
      else //REMOVE INSTRUCTION
	{
	  if(q1.size() > 0)
	    {
	      pcb_table[lastRunningProcess.getPID()-1].setState(WAITING);
	      lastRunningProcess = q1.removeHighestProc();
	      pcb_table[lastRunningProcess.getPID()-1].setState(RUNNING);
	    }
	}
    }

  gettimeofday(&FinishTime, NULL);
  double timeElapsed = (FinishTime.tv_sec - startTime.tv_sec) + ((FinishTime.tv_usec - startTime.tv_usec) / 1000000.0);
  cout << timeElapsed << " sec" << endl;
  displayPCBTable(pcb_table); q1.displayQueue();
  
  
  return 0;
}
