#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct process
{
	char* name;
	int arrival;
	int burst;

}process;
int main(void)
{
	char buffer[255];
	FILE *fp;
	char* token;
	fp = fopen("./set1_process.in","r");
	int i = 0;
	while(fgets(buffer,sizeof buffer, fp) != NULL)
	{
		char* newString;
		newString = (char*) malloc(strlen(buffer));

		strtok(buffer,"#");

		strcpy(newString,buffer);



		if(strcmp(buffer,"end\n") == 0)
		{
			printf("finished\n");
			return 0;
		}
		if(i >3)
		{
			token = strtok(newString," ");
			while(token != NULL)
			{
				printf("%s \n",token);
				token = strtok(NULL," ");
			}
		}
		free(newString);
		i++;
	}
}
