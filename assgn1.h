typedef struct process
{
	char* name;
	int arrival;
	int burst;
	struct process* nextNode;

}Process;
Process* front;
Process* rear;
void enqueue(Process* test);
void runFcfs(Process* processArray,int sizeOfProcessArray);
void test();
void deque();
char isEmpty();
