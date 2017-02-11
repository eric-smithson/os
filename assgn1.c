#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assgn1.h"


int main(void)
{
	FILE *fpr;
	Process *processes;
	char buffer[255];
	FILE *fp;
	char* token;
	int numberOfProcesses;
	char* typeOfScheduler;
	int totalRunTime;
	fp = fopen("./processes.in","r");
	int lineNumber = 0;
	int timeQuantum;
	char** inputStrings;
	int i = 0;
	fpr = fopen("./processes.out","w");
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


	qsort(processes, numberOfProcesses, sizeof(Process), compare_arrival);
	if(strcmp(typeOfScheduler,"fcfs") == 0)
	{

		runFcfs(processes,numberOfProcesses,totalRunTime,fpr);
	}
	else if(strcmp(typeOfScheduler,"sjf") == 0)
	{
		// printf("running sjf:\n"); // DEBUG
		sjf(processes,numberOfProcesses,totalRunTime,fpr);
	}
	else if(strcmp(typeOfScheduler,"rr") == 0)
	{
		//printf("in assgn1 main else if statments\n");
		runRoundRobin(processes,numberOfProcesses,totalRunTime,timeQuantum,fpr);
	}
	else
	{
		fprintf(fpr,"unrecognized task, exiting....");
		free(typeOfScheduler);
		for(i = 0 ; i < numberOfProcesses;i++)
		{
			free((processes+i)->name);
		}
		free(processes);
		exit(0);
	}
	free(typeOfScheduler);
	fclose(fp);
	fclose(fpr);
}


