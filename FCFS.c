#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
void insertQueue(QUEUE* queue, NODE* ptr);
int compareArrivalTime(const void * a , const void * b);
void FCFS(QUEUE* queue);
void IO_request(QUEUE* queue, NODE* ptr ,int* clock);
void printClock(int clock);

int main(){
  int processCount = 10;
  NODE* processes[10];
  PROCESS *ptr;
  QUEUE* queue;
  srand((unsigned int)time(NULL));
  queue = createQueue();

  for(int i =0 ;i<processCount;i++){
    int PID;
    NODE* newnode = (NODE*)malloc(sizeof(NODE));
    ptr = createProcess(i, rand()%10, rand()%15+1,rand()%3+1,rand()%10);
    newnode -> process = ptr;
    newnode -> next = NULL;
    processes[i] = newnode;
  }
  qsort(processes,10,sizeof(NODE*),compareArrivalTime);
  for(int i =0; i<processCount;i++){
    insertQueue(queue,processes[i]);
    printf("P%d\n",processes[i] -> process -> PID);
    printf("arrivalTime : %d\n",processes[i] -> process -> arrivalTime);
    printf("burstTime : %d\n",processes[i] -> process -> burstTime);
    printf("IO_requestTime : %d\n",processes[i] -> process -> IO_requestTime);
    printf("IO_burst : %d\n",processes[i] -> process -> IO_burst);
    printf("priority : %d\n",processes[i] -> process -> priority);
  }
  FCFS(queue);
  
  return 0;
}

PROCESS* createProcess(int PID, int arrivalTime, int burstTime, int IO_burst, int priority){
  PROCESS* newProcess = (PROCESS*)malloc(sizeof(PROCESS));
  newProcess -> PID = PID;
  newProcess -> arrivalTime = arrivalTime;
  newProcess -> burstTime = burstTime;
  newProcess -> IO_requestTime = burstTime - rand()%burstTime;
  newProcess -> IO_burst = IO_burst;
  newProcess -> priority = priority;
  return newProcess;
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
    queue -> in = node;
  }
}
int compareArrivalTime(const void *a, const void *b){
  NODE * nodeA = *(NODE**)a;
  NODE * nodeB = *(NODE**)b;
  return nodeA->process->arrivalTime - nodeB -> process -> arrivalTime;
}
void printClock(int clock){
  for(int i =clock ; i<clock+25;i++){
    if(i<10){
      printf("%d    ",i);
    }else if(i<100){
      printf("%d   ",i);
    }else{
      printf("%d  ",i);
    }
    
  }
  printf("\n");
  for(int i =0 ; i<25;i++){
    printf("|----");
  }
  printf("|\n");
}
void IO_request(QUEUE* queue, NODE* ptr,int* clock){
  do{
      ptr -> process -> IO_burst -= 1;
      printf("idle ");
      *clock += 1;
      if(*clock%25 == 0){
        printf("\n\n");
        printClock(*clock);
      }
    }while(ptr -> process -> IO_burst != 0);
    ptr -> process -> IO_requestTime = -1;
    if(ptr -> next != NULL){
      queue -> out = ptr -> next;
      queue -> in -> next = ptr;
      queue -> in = ptr;
      ptr -> next = NULL;
    }
    
}
void FCFS(QUEUE* queue){
  int clock = 0;
  printClock(clock);
  do{
    NODE* ptr = queue -> out;
    if(ptr -> process -> arrivalTime <= clock){
      if(ptr -> process -> burstTime == ptr -> process -> IO_requestTime){
      IO_request(queue,ptr,&clock);
    }else{
      ptr -> process -> burstTime -= 1;
      printf("P%d   ",ptr -> process->PID);
      clock += 1;
      if(clock%25 == 0){
        printf("\n\n");
        printClock(clock);
      }
      
      if(ptr -> process -> burstTime == 0){
        queue -> out = ptr -> next;
        free(ptr -> process);
        free(ptr);
      }
    }
    }else{
      printf("idle ");
      clock +=1;
      if(clock%25 == 0){
        printf("\n\n");
        printClock(clock);
      }
    }
    
    
  }while(queue -> out != NULL);
  free(queue);
  printf("\n");
}
