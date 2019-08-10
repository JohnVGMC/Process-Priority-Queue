#include "PCB.h"

//DEFAULT CONSTRUCTOR, sets all values to zero and state to NEW
PCB::PCB()
{
  PID = 0;
  state = NEW;
  priority = 0;
}

//Destructor
PCB::~PCB()
{
  //Nothing to add
}

//Sets the value of PID to the newID
void PCB::setPID(int newID)
{
  PID = newID;
}

//Returns the value of PID
int PCB::getPID()
{
  return PID;
}

//Sets the value of state to the newState
void PCB::setState(State newState)
{
  state = newState;
}

//Returns the value of state
State PCB::getState()
{
  return state;
}

//Sets the value of priority to the newPriority
void PCB::setPriority(int newPriority)
{
  priority = newPriority;
}

//Returns the value of priority
int PCB::getPriority()
{
  return priority;
}
