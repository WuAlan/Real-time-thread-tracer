#include "atom.h"


#define MAX_TASKS 20
#define MAX_EVENT 200

//redefine the critical section function.
#define CriticalEnter() CRITICAL_START()
#define CriticalExit() CRITICAL_END()

//redefine the function names
#define GetTimeStamp() GetTime()

//Redefine the task control block
typedef ATOM_TCB TASK;

