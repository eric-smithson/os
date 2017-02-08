#include <stdio.h>
#include "assgn1.h"
#include <stdlib.h>

void runFcfs(Process* processArray,int sizeOfProcessArray)
{
	front = rear = NULL;
	int i = 0;
	Process* process;
	for(i = 0; i < sizeOfProcessArray;i++)
	{
		printf("Name: %s, arrival: %d, burst: %d\n",
			(processArray+i)->name,
			(processArray+i)->arrival,
			(processArray+i)->burst);
		process = processArray + i;
		enqueue(process);
	}
	printf("After\n");
	printf("Name: %s, arrival: %d, burst: %d\n",
			(front)->name,
			(front)->arrival,
			(front)->burst);
	dequeue();
		printf("Name: %s, arrival: %d, burst: %d\n",
			(front)->name,
			(front)->arrival,
			(front)->burst);
}
void enqueue(Process* process)
{
	if(process == NULL)
	{
		printf("Process doesnt exist");
		return;
	}
	process->nextNode = NULL;
	if(front == NULL && rear == NULL)
	{
		front = rear = process;
		printf("enqueue sucess\n");
		return;
	}
	else
	{
		rear->nextNode = process;
		rear = process;
		printf("enqueue sucess\n");

	}
}
void dequeue()
{
	Process* temp = front;
	if(front == NULL)
	{
		printf("Queue is empty\n");
		return;
	}
	if(front == rear)
	{
		front = rear = NULL;
		printf("emptied queue\n");
	}
	else
	{
		front = front->nextNode;
		printf("dequeued\n");
	}
	free(temp->name);
	free(temp);
}
char isEmpty()
{
	if(front == NULL && front == NULL)
		return '1';
	else return '0';
}