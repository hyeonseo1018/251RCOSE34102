#define PROCESSCOUNT 10
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
NODE** copyProcesses(NODE**processesOrigin);
int compareArrivalTime(const void * a , const void * b);
void IO_request(QUEUE* readyQueue,QUEUE* waitingQueue, NODE* ptr);
void IO_processing(QUEUE* readyQueue,QUEUE* waitingQueue);
void printClock(int clock);
void FCFS(NODE**processesOrigin,int totalBurst);
void SJF(NODE**processesOrigin,int totalBurst);
void priority(NODE**processesOrigin,int totalBurst);
void RR(NODE**processesOrigin,int totalBurst,int timeQuantum);
void preemptiveSJF(NODE**processesOrigin,int totalBurst);
void preemptivePriority(NODE**processesOrigin,int totalBurst);

void InsertQueue(QUEUE* queue ,NODE* node);
void InsertReadyQueue(QUEUE* readyQueue, NODE** processes,int clock,int* index);

void SJFInsertReadyQueue(QUEUE* readyQueue, NODE** processes, int clock,int*index);
void SJF_IO_processing(QUEUE* readyQueue,QUEUE* waitingQueue);
void SJFInsertQueue(QUEUE* queue, NODE*node);

void preemptiveSJFInsertReadyQueue(QUEUE* readyQueue, NODE** processes, int clock,int*index);
void preemptiveSJF_IO_processing(QUEUE* readyQueue,QUEUE* waitingQueue);
void preemptiveSJFInsertQueue(QUEUE* queue, NODE* node);

void priorityInsertReadyQueue(QUEUE* readyQueue, NODE** processes, int clock,int*index);
void priority_IO_processing(QUEUE* readyQueue,QUEUE* waitingQueue);
void priorityInsertQueue(QUEUE* queue, NODE*node);

void preemptivePriorityInsertReadyQueue(QUEUE* readyQueue, NODE** processes, int clock,int*index);
void preemptivePriority_IO_processing(QUEUE* readyQueue,QUEUE* waitingQueue);
void preemptivePriorityInsertQueue(QUEUE* queue, NODE*node);

void timerEvent(QUEUE* queue, NODE*node);