#include <stdio.h>
#include "assgn1.h"
#include <stdlib.h>
#include <string.h>

void runFcfs(Process* processArray,int sizeOfProcessArray,int totalRunTime,FILE* fpr)
{
	char ready = 1;
	front = rear = NULL;
	int i = 0;
	int time = 0;
	int numberOfProcessProcessed = 0;
	int wait[sizeOfProcessArray];
	int turnArroundTime[sizeOfProcessArray];

	fprintf(fpr,"%d processes\n",sizeOfProcessArray);
	fprintf(fpr,"Using First Come First Served\n\n");
	for(time = 0; time <= totalRunTime ; time++)
	{
		for(i = 0; i < sizeOfProcessArray;i++)
		{
			if(processArray[i].arrival == time)
			{
				enqueue(processArray+i);
				fprintf(fpr,"Time %d: %s arrived\n",time,processArray[i].name);
				break;
			}
		}
		if(isEmpty() == 0)
		{
			if(front->burst == 0)
			{
				turnArroundTime[numberOfProcessProcessed] = time - processArray[numberOfProcessProcessed].arrival;
				fprintf(fpr,"Time %d: %s finished\n",time,front->name);
				numberOfProcessProcessed++;
				dequeue();

				ready = 1;
				

			}
			if(ready == 1 && numberOfProcessProcessed < sizeOfProcessArray && isEmpty() == 0)
			{
				wait[numberOfProcessProcessed] = time - processArray[numberOfProcessProcessed].arrival;
				fprintf(fpr,"Time %d: %s selected (burst %d)\n",time,front->name,front->burst);
				ready = 0;

			}
			if(isEmpty()== 0)
				(front->burst)--;

		
		}
		else	
			fprintf(fpr,"IDLE\n");
			

	}
	fprintf(fpr,"Finished at time %d\n",totalRunTime);

	fprintf(fpr,"\n");
	for(i = 0; i < numberOfProcessProcessed;i++)
	{
		if(wait[i] >= 0 && turnArroundTime >0)
		fprintf(fpr,"%s wait %d turnaround %d\n"
			,processArray[i].name
			,wait[i]
			,turnArroundTime[i]);
	}
	while(isEmpty() == 0)
	{
		fprintf(fpr,"Process %s did not finished\n",front->name);
		dequeue();
	}


	
}
void enqueue(Process* process)
{
	if(process == NULL)
	{
		printf("Process doesnt exist");
		return;
	}
	Process *temp = malloc(sizeof(Process));
	temp->name = malloc(sizeof(process->name));
	strcpy(temp->name,process->name);
	temp->arrival = process->arrival;
	temp->burst = process->burst;
	process->nextNode = NULL;
	if(front == NULL && rear == NULL)
	{
		front = rear = temp;
		return;
	}

		rear->nextNode = temp;
		rear = temp;

	
}
void dequeue()
{
	temp = front;
	if(temp == NULL)
	{
		//fprintf(fpr,"Queue is empty\n");
		return;
	}
	if(temp->nextNode == NULL)
	{
		free(front->name);
		free(front);

		front = rear = NULL;

	}
	else
	{

		temp = temp->nextNode;
		front->nextNode = NULL;
		free(front->name);
		free(front);
		front = temp;
		//fprintf(fpr,"sucessful dequeue\n");

	}


}
char isEmpty()
{
	if(front == NULL)
		return 1;
	else return 0;
}
