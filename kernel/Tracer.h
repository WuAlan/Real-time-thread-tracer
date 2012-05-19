#include "TracerPort.h"
//
//
//
//
//

#ifndef MAX_TASKS
	#error "Missing definition MAX_TASKS: the max number of tasks."
#endif

#ifndef MAX_EVENT
	#error "Missing definition MAX_TASKS: the max number of Events"
#endif


	
typedef enum {
  Empty=0,
  ETaskPreempted,
  ETaskArrived,
  ETaskResumed,
  ETaskCompleted,
  EMutexCreated,
  EMutexGetted,
  EMutexPutted,
  EMutexDeleted,
  ESemaphoreAcquired,
  ESemaphoreSuspended,
  ESemaphoreReleased,
  EISREnter,
  EISRExit,
  EOtherEvent
} EventType;




typedef struct {
  unsigned long timestamp;
  EventType event;
  void* arg1;
  void* arg2;
  void* arg3;
} Event;


TASK * TaskBuffer[MAX_TASKS];
Event EventBuffer[MAX_EVENT];
int EventIndex;
int EventNumbers;
TASK * ResumedTask;



unsigned long GetTimeStamp();

//Critical Section
extern void ECriticalEnter();
extern void ECriticalExit();


//Tasks
void TaskCreated(TASK * task);
void TaskArrived(TASK * task);
void TaskResumed(TASK * task);
void TaskCompleted(TASK * task);
void TaskPreempted(TASK * OriginalTask,TASK * TargetTask);


//Mutex

void MutexCreated(void * mutex);
void MutexDeleted(void * mutex);
void MutexGetted(void * mutex,TASK * task);
void MutexPutted(void * mutex,TASK * task);


//Other Events 
