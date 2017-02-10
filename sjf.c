#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assgn1.h"

// priority queue priorityEnqueue
// params: Process
// returns: front Process

void priorityEnqueue(Process* process)
{
	if(process == NULL)
		return;

	Process *processToInsert = malloc(sizeof(Process));
	processToInsert -> name = malloc(sizeof(process -> name));
	strcpy(processToInsert -> name,process -> name);
	processToInsert -> arrival = process -> arrival;
	processToInsert -> burst = process -> burst;
	processToInsert -> index = process -> index;
	processToInsert -> nextNode = NULL;
	process -> nextNode = NULL;

	if(front == NULL) {
		// queue hasn't been initiated, so we start it here
		front = processToInsert;
		return;
	}

	if(front -> burst > processToInsert -> burst) {
		processToInsert -> nextNode = front;
		front = processToInsert;
		return;
	}

	Process* processRunner = front;

	while(processRunner -> nextNode != NULL) {
		if(processRunner -> nextNode -> burst < processToInsert -> burst) {
			processRunner = processRunner -> nextNode;
			continue;
		} else {
			processToInsert -> nextNode = processRunner -> nextNode;
			processRunner -> nextNode = processToInsert;
			return;
		}
	}

	// the only way we'll get here is if we get to the end of the queue.
	processRunner -> nextNode = processToInsert;

	return;
}

// priority queue priorityDequeue
// params: none
// returns: A Process if there is one, else NULL
void priorityDequeue() {
	
	if(front == NULL)
		return;
	if(front -> nextNode == NULL){
		free(front);
		front = NULL;
		return;
	}
	// Process* processToInsert = front;
	temp = front;
	front = front -> nextNode;
	free(temp);

	return;
}

// scans through all the processes we have and sees if one enters this cycle

// sjf main script
// params: Process*, numberOfProcesses, runFor
// returns: nothing, should do all printing of output in this file

Process* findNewProcess(Process* processes, int numberOfProcesses, int cycle) {
	int i;
	for(i = 0; i < numberOfProcesses; i++) {
		if(processes[i].arrival == cycle)
			return &processes[i];
	}
	return NULL;
}

void printqueue() {
	if(front == NULL)
		return;

	Process* runner = front;

	while(runner != NULL){
		printf("%s: %d -> ", runner -> name, runner -> burst);
		runner = runner -> nextNode;
	}
	printf("\n");
}

void sjf(Process* processes, int numberOfProcesses, int runFor) {
	int cycle, wait_time, turnaround_time, i, j;
	int processesEntered = 0;
	int arrival_time[numberOfProcesses], finished_time[numberOfProcesses];
	Process* processToInsert;
	front = processToInsert = NULL; // front = front of line
	char* finished;

	// printf("DEBUG: %d\n", processes[0].burst); // DEBUG

	// runFor = 20;
	printf("%d processes\n", numberOfProcesses);
	printf("Using Shortest Job First (Pre)\n\n");

	for(i = 0; i < numberOfProcesses;i++) {
		arrival_time[i] = -1;
		finished_time[i] = -1;
		// index in process struct will coorespond to arrival time/finish time arrays
		processes[i].index = i;
	}


	for(cycle = 0; cycle < runFor; cycle++) {
		
		// if there is there are no processes left (priorityDequeue should return null), should print idle cycles
		if(processesEntered < numberOfProcesses) {
			// looks for a new process entry
			processToInsert = findNewProcess(processes, numberOfProcesses, cycle);
			if(processToInsert != NULL) {
				// updates queue
				printf("Time %d: %s arrived\n", cycle, processToInsert -> name);
				arrival_time[processToInsert -> index] = cycle;
				priorityEnqueue(processToInsert);
				if(strcmp(front -> name, processToInsert -> name) == 0){
					printf("Time %d: %s selected (burst %d)\n", cycle, front -> name, front -> burst);
				}
				processesEntered++;
			}
		}
		// printqueue(); // DEBUG
		if(front == NULL) {
			printf("Time %d: IDLE\n", cycle);
			continue;
		}
		if(front -> burst == 0){
			printf("Time %d: %s finished\n", cycle, front -> name);
			finished_time[front -> index] = cycle;
			priorityDequeue();
			if(front != NULL)
				printf("Time %d: %s selected (burst %d)\n", cycle, front -> name, front -> burst);
		}
		
		if(front == NULL) {
			printf("Time %d: IDLE\n", cycle);
			continue;
		}
		// printf("blah\n");

		// printf("front -> name = %s, front -> burst = %d\n", front -> name, front -> burst);

		(front -> burst)--;
	}
	finished = front == NULL ? "Finished": "Not finished";
	printf("%s at time %d\n\n", finished, cycle);

	// printing the wait and turnaround times for all processes that finished
	for(i = 0; i < numberOfProcesses; i++) {
		//printf("Arrival time of %s: %d  Finish time: %d\n",processes[i].name,arrival_time[i],finished_time[i]);
		if(arrival_time[i] != -1 && finished_time[i] != -1)
		{
			turnaround_time = finished_time[i] - arrival_time[i];
			wait_time = turnaround_time - processes[i].burst;

			printf("%s wait %d turnaround %d\n"
	 		,processes[i].name
	 		,wait_time
	 		,turnaround_time);
		}
	}
	return;
}