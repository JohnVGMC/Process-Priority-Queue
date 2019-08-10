#ifndef PCB_H
#define PCB_H

enum State { NEW, READY, RUNNING, WAITING, TERMINATED };

class PCB
{
 private:
  int PID; //Process ID
  State state;
  int priority;

 public:

  //Default Constructor
  PCB();

  //Destructor
  ~PCB();

  //Sets the value of the Process's ID
  //PARAMETER: int variable that overwrites the old PID
  void setPID(int);

  //Returns the Process ID
  int getPID();

  //Sets the state of the process
  //PARAMETER: State variable that tells what state the process is in now
  void setState(State);

  //Returns the state of the process
  State getState();

  //Sets the value of the process's Priority
  //PARAMETER: int variable that overwrites the old priority of the process
  void setPriority(int);
  
  //Returns the priority value of the process
  int getPriority();
};

#endif //PCB_H
