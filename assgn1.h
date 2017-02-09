typedef struct process
{
	char* name;
	int arrival;
	int burst;
	int index;
	struct process* nextNode;

}Process;
Process* front;
Process* rear;
Process* temp;
Process* current;

void enqueue(Process* test);
void runFcfs(Process* processArray,int sizeOfProcessArray,int totalRunTime);
void test();
void dequeue();
char isEmpty();

void runRoundRobin(Process* processArray,int sizeOfProcessArray,int totalRunTime,int quantum);
