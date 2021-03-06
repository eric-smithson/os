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
void runFcfs(Process* processArray,int sizeOfProcessArray,int totalRunTime,FILE* fpr);
void sjf(Process* processes, int numberOfProcesses, int runFor,FILE* fpr);
void test();
void dequeue();
char isEmpty();
int compare_arrival(const void *a, const void *b);
void runRoundRobin(Process* processArray,int sizeOfProcessArray,int totalRunTime,int quantum,FILE* fpr);
