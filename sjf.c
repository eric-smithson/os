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

	Process* currentProcess = front;

	while(currentProcess -> nextNode != NULL) {
		if(currentProcess -> nextNode -> burst < processToInsert -> burst) {
			currentProcess = currentProcess -> nextNode;
			continue;
		} else {
			processToInsert -> nextNode = currentProcess -> nextNode;
			currentProcess -> nextNode = processToInsert;
			return;
		}
	}

	// the only way we'll get here is if we get to the end of the queue.
	currentProcess -> nextNode = processToInsert;

	return;
}

// priority queue priorityDequeue
// params: none
// returns: A Process if there is one, else NULL
void priorityDequeue(Process* front) {
	
	if(front == NULL)
		return;
	if(front -> nextNode == NULL)
		return;
	
	Process* processToInsert = front;
	front = front -> nextNode;

	return;
}

// scans through all the processes we have and sees if one enters this cycle

// sjf main script
// params: Process*, numberOfProcesses, runFor
// returns: nothing, should do all printing of output in this file

Process* findNewProcess(Process* processes, int numberOfProcesses, int cycle){
	int i;
	for(i = 0; i < numberOfProcesses; i++) {
		if(processes[i].arrival == cycle)
			return &processes[i];
	}
	return NULL;
}

void sjf(Process* processes, int numberOfProcesses, int runFor) {
	int i, j, cycle;
	int processesEntered = 0;
	Process* processToInsert;
	front = processToInsert = NULL; // front = front of line

	printf("%s\n",processes[0].name);

	for(cycle = 0; cycle < runFor; cycle++) {
		// every cycle it needs to:
			// check if there are new processes which need to be put in the queue
				// if there are new processes, make a check to see if the newest process has a shorter burst time
				// allow the process with the shortest burst left to take a turn
			// When dequeing, you take out the Process, and priorityEnqueue it when you need to switch out (with burst time adjusted)

		// if there is there are no processes left (priorityDequeue should return null), should print idle cycles

		if(processesEntered < numberOfProcesses) {
			// looks for a new process entry
			processToInsert = findNewProcess(processes, numberOfProcesses, cycle);
			if(processToInsert != NULL) {
				// updates front
				priorityEnqueue(processToInsert);
				processesEntered++;
			}
		}
		if(front == NULL) {
			printf("idle cycle\n");
			continue;
		}

		(front -> burst)--;
	}
	return;
}