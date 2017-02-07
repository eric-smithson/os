typedef struct process
{
	char* name;
	int arrival;
	int burst;

}Process;

void enqueue(Process* test);