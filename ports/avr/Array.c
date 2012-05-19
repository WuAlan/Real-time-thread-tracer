#include "Array.h"

static uint32_t array[100];
static int length=0;
void Add(uint32_t data)
{
	array[length]=data;
	length++;
	if(length==99)
		length=0;
}

uint32_t Get(int i)  
{
	if(i>=0&&i<100)
		return array[i];
	return 0;
}
