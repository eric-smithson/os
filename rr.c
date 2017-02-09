#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assgn1.h"

// comparing the arrival times of the processes so 
// qsort will put them in order based on arrival times
int compare_arrival(const void *a, const void *b)
{
	const Process *p1 = a;
	const Process *p2 = b;

	return p1->arrival < p2->arrival ? -1 : p2->arrival < p1->arrival;
}


void enqueueRoundRobin(Process* process)
{
	if(process == NULL)
	{
		//printf("Process doesnt exist");
		return;
	}

	Process *temp = malloc(sizeof(Process));
	temp->name = malloc(sizeof(process->name));
	strcpy(temp->name,process->name);
	temp->arrival = process->arrival;
	temp->burst = process->burst;
	temp->index = process->index;
	temp->nextNode = NULL;         

	if(front == NULL && rear == NULL)
	{
		front = rear = current = temp;
		return;
	}
		rear->nextNode = temp;
		rear = temp;
}


void dequeueP(Process* process_done)
{
	int i;

	temp = front;
	if(temp == NULL)
	{
		//printf("Queue is empty\n");
		return;
	}

	
	if(temp->nextNode == NULL) // for when the last process is dequeued
	{
		free(front->name);
		free(front);
		front = rear = NULL;
	}
	else
	{
		while(temp!= NULL)
		{
			//printf("the address of temp: %p \n the address of process_done: %p\n",temp,process_done );
			if(temp->nextNode == process_done)
			{
				temp->nextNode = process_done->nextNode;
				//printf("dequeue, process_done found\n");
				process_done->nextNode = NULL;
				free(process_done->name);
				free(process_done);
				return;
			}
		}
	}

}


void runRoundRobin(Process* processArray,int sizeOfProcessArray,int totalRunTime, int quantum)
{
	// Variables
	int time = 0; // counter acts like a clock, counting up until totalRunTime
	int numOfProcessesRemaining = sizeOfProcessArray;
	front = rear = NULL;

	int i;
	int arrival_time[sizeOfProcessArray];
	int finished_time[sizeOfProcessArray];

	// to calculate turnaround time, record the time when a process arrives and finishes
	// turnaround_time = finished_time - arrival_time
	// to calculate wait time, 
	// wait_time = turnaround_time - burst_size

	for(i = 0; i < sizeOfProcessArray;i++)
	{
		arrival_time[i] = -1;
		finished_time[i] = -1;
	}

	// top section of output
	printf("\n%d processes\n",sizeOfProcessArray);
	printf("Using Round-Robin\n");
	printf("Quantum %d\n\n",quantum);


	qsort(processArray, sizeOfProcessArray, sizeof(Process), compare_arrival); // quicksort average O(nlogn)

	for(i=0; i<sizeOfProcessArray; ++i) // loop for testing purposes
	{
		//printf("process %s arrival time: %d\n",processArray[i].name, processArray[i].arrival);
		processArray[i].index = i;
	}

	int currentP = 0; // counter that keeps track of current process in the CPU
	int nextP = 0; // counter that keeps tack of the next process to arrive

	int quantum_counter=0;



	for(time = 0; time < totalRunTime ; time++)
	{

		for(i = 0; i < sizeOfProcessArray;i++)
		{
			if(processArray[i].arrival == time)
			{
				enqueueRoundRobin(processArray+i);
				printf("Time %d: %s arrived\n",time,processArray[i].name);
				arrival_time[i] = time;
				break;
			}
		}

		if(current != NULL)
		{

		if(current->burst == 0)
		{
			
			if(!isEmpty())
			{
				printf("Time %d: %s finished\n",time,current->name);
				finished_time[current->index] = time;
				//printf("current index i %d\n",current->index);
			}	
			if(current == front)
				dequeue();
			else
				dequeueP(current);
			quantum_counter = quantum;
			
		}

	
		if(quantum_counter == quantum)
		{
			// switch to next process
			quantum_counter = 0;

			if(isEmpty() == 0 && current->nextNode != NULL)
				current = current->nextNode;
			else if(isEmpty() == 0 && current->nextNode == NULL)
				current = front;

		}

		if(current->burst > 0)
		{
			quantum_counter++;
			printf("Time %d: %s selected (burst %d)\n",time,current->name,current->burst);
			current->burst--;
		}	

		if(isEmpty() == 1)
			printf("Time %d: IDLE\n",time);	

		}

	}

	if(isEmpty() == 1)
		printf("Finished at time %d\n",totalRunTime);
	else
		while(!isEmpty())
		{
			printf("Process %s did not finish\n",front->name);
			dequeue();
		}

	printf("\n");	

	int turnaround_time;
	int wait_time;

	for(i = 0; i < sizeOfProcessArray;i++)
	{
		//printf("Arrival time of %s: %d  Finish time: %d\n",processArray[i].name,arrival_time[i],finished_time[i]);
		if(arrival_time[i] != -1 && finished_time[i] != -1)
		{
			turnaround_time = finished_time[i] - arrival_time[i];
			wait_time = turnaround_time - processArray[i].burst;

			printf("%s wait %d turnaround %d\n"
	 		,processArray[i].name
	 		,wait_time
	 		,turnaround_time);
		}

	}

}
