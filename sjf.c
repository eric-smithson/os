#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// priority queue enqueue
// params: Process
// returns: fol Process

Process enqueue(Process* processToInsert, Process* fol)
{
	if(process == NULL)
		return;

	if(fol == NULL) {
		// queue hasn't been initiated, so we start it here
		fol = processToInsert;
		return fol;
	}

	if(fol.burst > processToInsert.burst) {
		processToInsert.next = fol;
		return processToInsert;
	}

	currentProcess = fol;
	while(currentProcess.next != NULL) {
		if(currentProcess.next.burst < processToInsert.burst) {
			currentProcess = currentProcess.next;
			continue;
		} else {
			// at this point currentProcess.next.burst > processToInsert.burst
			processToInsert.next = currentProcess.next;
			currentProcess.next = processToInsert;
			return fol;
		}
	}
	return NULL;
}

// priority queue dequeue
// params: none
// returns: A Process if there is one, else NULL
Process dequeue(Process* fol) {
	
	if(fol == NULL)
		return NULL;
	if(fol.next == NULL)
		return fol;
	
	Process* temp = fol;
	fol = fol.next;

	return temp;
}

// scans through all the processes we have and sees if one enters this cycle

// sjf main script
// params: Process*, numberOfProcesses, runFor
// returns: nothing, should do all printing of output in this file

void sjf(Process* processes, int numberOfProcesses, int runFor) {

	int i, j, cycle;

	Process current = NULL;
	int processesEntered = 0;
	Process* fol = NULL; // fol = front of line

	for(cycle = 0; cycle < runFor; cycle++) {
		// every cycle it needs to:
			// check if there are new processes which need to be put in the queue
				// if there are new processes, make a check to see if the newest process has a shorter burst time
				// allow the process with the shortest burst left to take a turn
			// When dequeing, you take out the Process, and enqueue it when you need to switch out (with burst time adjusted)

		// if there is there are no processes left (dequeue should return null), should print idle cycles

		// looks for a new process entry
		if(processesEntered < numberOfProcesses) {
			fol = enqueue(findNewProcess(processes, numberOfProcesses, cycle), fol)
			processesEntered++;
		}

		if(current == NULL) {
			current = dequeue(fol);
			if(current == NULL) {
				printf("idle cycle\n");
				continue;
			}
		}
	}

	// for(i = 0; i < numberOfProcesses; i++) {
	// 	process = processes[i]
	// 	enqueue(process)
	// }
	return;
}