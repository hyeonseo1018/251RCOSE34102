typedef struct{
  int PID;
  int arrivalTime;
  int burstTime;
  int IO_requestTime;
  int IO_burst;
  int priority;
}PROCESS;

typedef struct node{
  PROCESS *process;
  struct node *next;
}NODE;

typedef struct{
  NODE *out;
  NODE *in;
}QUEUE;

PROCESS* createProcess(int PID, int arrivalTime, int burstTime, int IO_burst, int priority);
QUEUE* createQueue();
void insertQueue(QUEUE* queue, NODE* node);
int compareArrivalTime(const void * a , const void * b);
void IO_request(QUEUE* queue, NODE* ptr ,int* clock);
void printClock(int clock);
void FCFS(NODE**processesOrigin,const int processCount);
NODE** copyProcesses(NODE**processesOrigin, const int processCount);