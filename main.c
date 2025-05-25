#include "scheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
  const int processCount = 10;
  NODE* processesOrigin[10];
  PROCESS *ptr;
  srand((unsigned int)time(NULL));

  for(int i =0 ;i<processCount;i++){
    int PID;
    NODE* newnode = (NODE*)malloc(sizeof(NODE));
    ptr = createProcess(i, rand()%10, rand()%15+1,rand()%3+1,rand()%10);
    newnode -> process = ptr;
    newnode -> next = NULL;
    processesOrigin[i] = newnode;
  }
  qsort(processesOrigin,10,sizeof(NODE*),compareArrivalTime);
  for(int i =0; i<processCount;i++){
    printf("P%d\n",processesOrigin[i] -> process -> PID);
    printf("arrivalTime : %d\n",processesOrigin[i] -> process -> arrivalTime);
    printf("burstTime : %d\n",processesOrigin[i] -> process -> burstTime);
    printf("IO_requestTime : %d\n",processesOrigin[i] -> process -> IO_requestTime);
    printf("IO_burst : %d\n",processesOrigin[i] -> process -> IO_burst);
    printf("priority : %d\n",processesOrigin[i] -> process -> priority);
  }
  FCFS(processesOrigin,processCount);
  
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
NODE** copyProcesses(NODE** processesOrigin, const processCount){
  NODE **copy = malloc(processCount*sizeof(NODE*));
  for (int i=0;i<processCount;i++) {
      NODE* newnode = (NODE*)malloc(sizeof(NODE));
      newnode -> process = (PROCESS*)malloc(sizeof(PROCESS));
      *(newnode -> process) = *(processesOrigin[i]->process);
      newnode -> next = NULL;
      copy[i] = newnode;
  }
  return copy;
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