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
		typeOfScheduler = (strtok(NULL," "));

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
			processes[i].name = strtok(NULL," ");
			strtok(NULL," ");
			processes[i].arrival = atoi(strtok(NULL," "));
			strtok(NULL," ");
			processes[i].burst = atoi(strtok(NULL," "));

		}
		// printf("process name: %s arrival: %d burst: %d\n", processes[i].name,processes[i].arrival,processes[i].burst);
	}
	enqueue(processes);
	test();
		free(processes);

}
