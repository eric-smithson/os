#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assgn1.h"

int main(void)
{
	Process* processes;
	char buffer[255];
	FILE *fp;
	char* token;
	int numberOfProcesses;
	char* typeOfScheduler;
	int timeUnit;
	fp = fopen("./set1_process.in","r");
	int lineNumber = 0;
	int timeQuantum;
	char** inputStrings;
	int i = 0;
	if(fgets(buffer,sizeof buffer, fp)!= NULL)
	{
		token = strtok(buffer," ");
		numberOfProcesses = atoi(strtok(NULL," "));
	}
	processes = malloc(sizeof(Process) * numberOfProcesses);
	if(fgets(buffer,sizeof buffer,fp) !=NULL)
	{
		token = strtok(buffer," ");
		timeUnit = atoi(strtok(NULL, " "));
	}
	printf("time unit = %d\n",timeUnit);
	if(fgets(buffer,sizeof buffer,fp) != NULL)
	{

		token = strtok(buffer," ");
		char* temp = strtok(NULL," ");
		typeOfScheduler = malloc(sizeof(temp));
		strcpy(typeOfScheduler,temp);
		printf("address of temp: %p adress of typeOfScheduler = %p\n",temp,typeOfScheduler);

	}
	printf("type of scheduler: %s\n",typeOfScheduler);
	if(fgets(buffer,sizeof buffer,fp) != NULL)
	{
		token = strtok(buffer," ");
		timeQuantum = atoi(strtok(NULL," "));
	}
	printf("time quantum = %d\n", timeQuantum);
	for(i = 0; i < numberOfProcesses;i++)
	{
		if(fgets(buffer,sizeof buffer,fp) != NULL)
		{
			token = strtok(buffer," ");
			strtok(NULL," ");
			char* temp = strtok(NULL," ");
			(processes+i)->name = malloc(sizeof(temp));
			strcpy((processes+i)->name,temp);
			strtok(NULL," ");
			(processes+i)->arrival = atoi(strtok(NULL," "));
			strtok(NULL," ");
			(processes+i)->burst = atoi(strtok(NULL," "));

		}
	}

	int val = strcmp(typeOfScheduler,"fcfs");

	if(strcmp(typeOfScheduler,"fcfs") == 0)
	{
		for( i = 0 ; i < numberOfProcesses; i ++)
		{
			printf("process name: %s arrival: %d burst: %d\n", processes[i].name,processes[i].arrival,processes[i].burst);

		}
		printf("size of process array in main: %d\n",sizeof(processes));
		runFcfs(processes,numberOfProcesses);
	}
	else if(strcmp(typeOfScheduler,"sjf"))
	{
		//call shortest job first here
	}
	else if(strcmp(typeOfScheduler,"rr"))
	{
		//call round robin here
	}
	else
	{
		printf("unrecognized task exiting....");
		free(typeOfScheduler);
		free(processes);
		exit(0);
	}
	free(typeOfScheduler);
	for( i = 0; i < numberOfProcesses;i ++)
	{
		free((processes+i)->name);
	}
	free(processes);


}
