#include "motion.h"
#include <stdio.h>

PIT pit[PITITEM];
u8 NMatchcount = 0;
int absl(int num)
{
	if(num>=0)
		return num;
	else
		return -num;
}

void DampAutoPos(void)
{
	int i,count = 0;
	float step;
	for(i=0;i<PITITEM;i++)
	{
		if(pit[i].channel == 0)
		{
			step = absl(pit[i].target-pit[i].current)/10+1;
			
			if(pit[i].target > pit[i].current+step)
			{
				pit[i].current += step;
				pit[i].match = False;
			}
			else if(pit[i].target < pit[i].current-step)
			{
				pit[i].current -= step;
				pit[i].match = False;
			}
			else if(absl(pit[i].target-pit[i].current)<=step)
			{
				pit[i].current = pit[i].target;
				pit[i].match = True;
			}
		}
	}
	for(i=0;i<PITITEM;i++)
	{
		if(pit[i].channel == 0)
		{
			if(!pit[i].match)
			{
				count++;
//				printf("i=%d,Traget=%f,Current=%f\r\n",i,pit[i].target,pit[i].current);
			}
			if(count>3)
			 break;
//			printf("Match\r\n");
		}
	}
	NMatchcount = count;
}

void DampMPos(float step)
{
	int i,count = 0;
	for(i=0;i<PITITEM;i++)
	{
		if(pit[i].channel == 0)
		{
			if(pit[i].target > pit[i].current+step)
			{
				pit[i].current += step;
				pit[i].match = False;
			}
			else if(pit[i].target < pit[i].current-step)
			{
				pit[i].current -= step;
				pit[i].match = False;
			}
			else if(absl(pit[i].target-pit[i].current)<=step)
			{
				pit[i].current = pit[i].target;
				pit[i].match = True;
			}
		}
	}
	for(i=0;i<PITITEM;i++)
	{
		if(pit[i].channel == 0)
		{
			if(!pit[i].match)
			{
				count++;
			}
			if(count>3)
			 break;
//			printf("Match\r\n");
		}
	}
	NMatchcount = count;
}

void DampCustormPos(u16 index,float step)
{
	if(pit[index].target > pit[index].current+step)
	{
		pit[index].current += step;
		pit[index].match = False;
	}
	else if(pit[index].target < pit[index].current-step)
	{
		pit[index].current -= step;
		pit[index].match = False;
	}
	else if(absl(pit[index].target-pit[index].current)<=step)
	{
		pit[index].current = pit[index].target;
		pit[index].match = True;
	}
}

void SetCurrent(u8 index,float value)
{
	pit[index].current = value;
}

void SetTarget(u8 index,float value)
{
	pit[index].target = value;
}

void SetChannel(u8 index,u8 channel)
{
	pit[index].channel = channel;
}
