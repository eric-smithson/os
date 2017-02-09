#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assgn1.h"

int main(void)
{
	Process *processes;
	char buffer[255];
	FILE *fp;
	char* token;
	int numberOfProcesses;
	char* typeOfScheduler;
	int totalRunTime;
	fp = fopen("./set4_process.in","r");
	int lineNumber = 0;
	int timeQuantum;
	char** inputStrings;
	int i = 0;
	if(fgets(buffer,sizeof buffer, fp)!= NULL)
	{
		token = strtok(buffer," ");
		numberOfProcesses = atoi(strtok(NULL," "));
	}
	processes = malloc(numberOfProcesses * sizeof *processes);

	if(fgets(buffer,sizeof buffer,fp) !=NULL)
	{
		token = strtok(buffer," ");
		totalRunTime = atoi(strtok(NULL, " "));
	}
	if(fgets(buffer,sizeof buffer,fp) != NULL)
	{

		token = strtok(buffer," ");
		char* temp = strtok(NULL," ");
		typeOfScheduler = malloc(sizeof(temp));
		strcpy(typeOfScheduler,temp);

	}
	if(fgets(buffer,sizeof buffer,fp) != NULL)
	{
		token = strtok(buffer," ");
		timeQuantum = atoi(strtok(NULL," "));
	}
	for(i = 0; i < numberOfProcesses;i++)
	{
		if(fgets(buffer,sizeof buffer,fp) != NULL)
		{
			token = strtok(buffer," ");
			strtok(NULL," ");
			char* temp = strtok(NULL," ");
			(processes[i]).name = malloc(sizeof(temp));
			strcpy((processes[i]).name,temp);
			strtok(NULL," ");
			(processes+i)->arrival = atoi(strtok(NULL," "));
			strtok(NULL," ");
			(processes[i]).burst = atoi(strtok(NULL," "));

		}
	}

	// printf("typeOfScheduler = %s\n", typeOfScheduler); // DEBUG

	if(strcmp(typeOfScheduler,"fcfs") == 0)
	{
		printf("running fcfs\n"); // DEBUG
		runFcfs(processes,numberOfProcesses,totalRunTime);
	}
	else if(strcmp(typeOfScheduler,"sjf") == 0)
	{
		printf("running sjf:\n"); // DEBUG
		sjf(processes,numberOfProcesses,totalRunTime);
	}
	else if(strcmp(typeOfScheduler,"rr") == 0)
	{
		//call round robin here
		printf("running rr:\n"); // DEBUG
	}
	else
	{
		printf("unrecognized task exiting....\n");
		free(typeOfScheduler);
		for(i = 0 ; i < numberOfProcesses;i++)
		{
			free((processes+i)->name);
		}
		free(processes);
		exit(0);
	}
	free(typeOfScheduler);
}
