typedef struct process
{
	char* name;
	int arrival;
	int burst;
	struct process* nextNode;

}Process;
Process* front;
Process* rear;
Process* temp;
void enqueue(Process* test);
void runFcfs(Process* processArray,int sizeOfProcessArray,int totalRunTime);
void sjf(Process* processes, int numberOfProcesses, int runFor);
void test();
void dequeue();
char isEmpty();
