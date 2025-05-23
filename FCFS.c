#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int PID;
  int arrivalTime;
  int burstTime;
  int IO_requestTime;
  int IO_burst;
  int priority
}PROCESS;

typedef struct node{
  PROCESS *process;
  struct node *next;
}NODE;

typedef struct{
  NODE *out;
  NODE *in;
}QUEUE;

PROCESS* createProcess(int PID, int arrivalTime, int IO_requestTime, int IO_burst, int priority);
QUEUE* createQueue();
void insertQueue(QUEUE* queue, PROCESS* ptr);
int compareArrivalTime(const void * a , const void * b);
void FCFS(QUEUE* queue);

int main(){
  int processCount = 10;
  NODE* processes[10];
  PROCESS *ptr;
  QUEUE* queue;
  queue = createQueue();

  for(int i =0 ;i<processCount;i++){
    int PID;
    NODE* newnode = (NODE*)malloc(sizeof(NODE));
    ptr = createProcess(i, rand()%10, rand()%15+1,rand()%3,rand()%10);
    newnode -> process = ptr;
    newnode -> next = NULL;
    processes[i] = newnode;
  }
  qsort(processes,10,sizeof(NODE*),compareArrivalTime);
  for(int i =0; i<processCount;i++){
    insertQueue(queue,processes[i]);
  }
  FCFS(queue);
  
  return 0;
}

PROCESS* createProcess(int PID, int arrivalTime, int IO_requestTime, int IO_burst, int priority){
  PROCESS* newProcess = (NODE*)malloc(sizeof(NODE));
  newProcess -> PID = PID;
  newProcess -> arrivalTime = arrivalTime;
  newProcess -> burstTime = 15- IO_requestTime +1;
  newProcess -> IO_requestTime = IO_requestTime;
  newProcess -> IO_burst = IO_burst;
  newProcess -> priority = priority;
}
QUEUE* createQueue(){
  QUEUE* queue = (QUEUE*)malloc(sizeof(QUEUE));
  queue -> in = NULL;
  queue -> out = NULL;
  return queue;
}
void insertQueue(QUEUE* queue,NODE* node){
  if(queue -> in == NULL){
    queue -> in = node;
    queue ->out = node;
  }else{
    queue -> in -> next = node;
  }
}
int compareArrivalTime(const void *a, const void *b){
  NODE * nodeA = *(NODE**)a;
  NODE * nodeB = *(NODE**)b;
  return nodeA->process->arrivalTime - nodeB -> process -> arrivalTime;
}
void FCFS(QUEUE* queue){
  
  do{
    NODE* ptr = queue -> out;
    if(ptr -> process -> burstTime == ptr -> process -> IO_requestTime){
      do{
        ptr -> process -> IO_burst -= 1;
        printf("idle");
      }while(ptr -> process -> IO_burst != 0);
    }else{
      ptr -> process -> burstTime -= 1;
      printf("P%d processing",ptr -> process->PID);
      if(ptr -> process -> burstTime == 0){
        queue -> out = ptr -> next;
        free(ptr);
      }
    }
    
  }while(queue -> out != NULL);
}
