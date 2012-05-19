#include "Tracer.h"
#include "StopWatch.h"
void RecordEvent(EventType Type,void* arg1,void* arg2,void* arg3)
{
		CRITICAL_STORE;
		CRITICAL_START();
		EventIndex = (EventIndex+1) % MAX_EVENT;
		EventBuffer[EventIndex].timestamp = GetTime();
		
		if(EventBuffer[EventIndex].event==Empty||EventBuffer[EventIndex].event==NULL)
		{

			EventBuffer[EventIndex].event = Type;
			EventBuffer[EventIndex].arg1 = arg1;
			EventBuffer[EventIndex].arg2 = arg2;
			EventBuffer[EventIndex].arg3 = arg3;
			EventNumbers++;
		}
		CRITICAL_END();
}



//Tasks Event

void TaskCreated(TASK * task)
{
	int i;
	for(i=0;i<MAX_TASKS;i++)
	{
		if(TaskBuffer[i]==NULL)
		{
			TaskBuffer[i]=task;
			break;	
		}

	}
}

void TaskArrived(TASK * task)
{
	if(task->priority!=250)
	{
		RecordEvent(ETaskArrived,task,NULL,NULL);
	}
}

void TaskResumed(TASK * task)
{
	if(task->priority!=250)
	{
		RecordEvent(ETaskResumed,task,NULL,NULL);
	}
}

void TaskCompleted(TASK * task)
{
	if(task->priority!=250)
		RecordEvent(ETaskCompleted,task,NULL,NULL);
}


TASK * OldTask;
TASK * NewTask;
void TaskPreempted(TASK * OriginalTask,TASK * TargetTask)
{
	
	if(OriginalTask->priority==250||TargetTask->priority==250)
	{
		if(OriginalTask->priority!=250)
		{
			OldTask=OriginalTask;

		}
		else if(TargetTask->priority!=250)
		{
			NewTask=TargetTask;
			
		}
		if(OldTask!=NewTask)
		{
			if(OldTask!=NULL&&NewTask!=NULL)
			{
				RecordEvent(ETaskPreempted,OldTask,NewTask,NULL);
				TaskResumed(NewTask);
				OldTask=NULL;
				NewTask=NULL;
			}
		}
		else
		{
			OldTask=NULL;
			NewTask=NULL;
		}

	}
	
	else
	
	{
		OldTask=NULL;
		NewTask=NULL;
		RecordEvent(ETaskPreempted,OriginalTask,TargetTask,NULL);
		TaskResumed(TargetTask);
	}
}


void MutexCreated(void * mutex)
{
	RecordEvent(EMutexCreated,mutex,NULL,NULL);
}
void MutexDeleted(void * mutex)
{
	RecordEvent(EMutexDeleted,mutex,NULL,NULL);
}
void MutexGetted(void * mutex,TASK * task)
{
	if(task->priority!=250)
	{
		RecordEvent(EMutexGetted,mutex,task,NULL);
	}
}
void MutexPutted(void * mutex,TASK * task)
{
	if(task->priority!=250)
	{
		RecordEvent(EMutexPutted,mutex,task,NULL);
	}
}

