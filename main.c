#include "scheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
  NODE **processesOrigin = malloc(PROCESSCOUNT*sizeof(NODE*));
  PROCESS *ptr;
  int totalBurst = 0;
  int timeQuantum = 2;
  srand((unsigned int)time(NULL));

  for(int i =0 ;i<PROCESSCOUNT;i++){
    NODE* newnode = (NODE*)malloc(sizeof(NODE));
    ptr = createProcess(i, rand()%10, rand()%15+1,rand()%3+1,rand()%10);
    newnode -> process = ptr;
    newnode -> next = NULL;
    processesOrigin[i] = newnode;
  }
  qsort(processesOrigin,PROCESSCOUNT,sizeof(NODE*),compareArrivalTime);
  for(int i =0; i<PROCESSCOUNT;i++){
    totalBurst += processesOrigin[i] -> process -> burstTime + processesOrigin[i] -> process -> IO_burst;
    printf("P%d\n",processesOrigin[i] -> process -> PID);
    printf("arrivalTime : %d\n",processesOrigin[i] -> process -> arrivalTime);
    printf("burstTime : %d\n",processesOrigin[i] -> process -> burstTime);
    printf("IO_requestTime : %d\n",processesOrigin[i] -> process -> IO_requestTime);
    printf("IO_burst : %d\n",processesOrigin[i] -> process -> IO_burst);
    printf("priority : %d\n",processesOrigin[i] -> process -> priority);
  }
  printf("\n------FCFS-----------------------------------------------------------------------------------------------------------\n");
  FCFS(processesOrigin,totalBurst);
  printf("\n------SJF------------------------------------------------------------------------------------------------------------\n");
  SJF(processesOrigin,totalBurst);
  printf("\n------Priority-------------------------------------------------------------------------------------------------------\n");
  priority(processesOrigin,totalBurst);
  printf("\n------RR-------------------------------------------------------------------------------------------------------------\n");
  RR(processesOrigin,totalBurst,timeQuantum);
  printf("\n------preemptiveSJF--------------------------------------------------------------------------------------------------\n");
  preemptiveSJF(processesOrigin,totalBurst);
  printf("\n------preemptivePriority---------------------------------------------------------------------------------------------\n");
  preemptivePriority(processesOrigin,totalBurst);
  return 0;
}

PROCESS* createProcess(int PID, int arrivalTime, int burstTime, int IO_burst, int priority){
  PROCESS* newProcess = (PROCESS*)malloc(sizeof(PROCESS));
  newProcess -> PID = PID;
  newProcess -> arrivalTime = arrivalTime;
  newProcess -> burstTime = burstTime;
  newProcess -> IO_requestTime = rand()%burstTime + 1;
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
NODE** copyProcesses(NODE** processesOrigin){
  NODE **copy = malloc(PROCESSCOUNT*sizeof(NODE*));
  for (int i=0;i<PROCESSCOUNT;i++) {
      NODE* newnode = (NODE*)malloc(sizeof(NODE));
      newnode -> process = (PROCESS*)malloc(sizeof(PROCESS));
      *(newnode -> process) = *(processesOrigin[i]->process);
      newnode -> next = NULL;
      copy[i] = newnode;
  }
  return copy;
}
void InsertQueue(QUEUE* queue ,NODE* node){
  if(queue -> out == NULL){
    queue -> out = node;
    queue -> in = node;
  }else{
    queue -> in -> next = node;
    queue -> in = node;
  }
}
void InsertReadyQueue(QUEUE* readyQueue,NODE** processes,int clock,int* index){
  NODE* node = NULL;
  while(*index < PROCESSCOUNT){
    node = processes[*index];
    if(node -> process -> arrivalTime == clock){
      InsertQueue(readyQueue,node);
      *index+=1;
    }else{
      break;
    }
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
    }else if(i<1000){
      printf("%d  ",i);
    }else{
      printf("%d ",i);
    }
    
  }
  printf("\n");
  for(int i =0 ; i<25;i++){
    printf("|----");
  }
  printf("|\n");
}
void IO_request(QUEUE* readyQueue,QUEUE* waitingQueue, NODE* ptr){
  if(readyQueue -> out -> next == NULL){
    readyQueue -> out = NULL;
    readyQueue -> in = NULL;
  }else{
    readyQueue -> out = ptr -> next;
  }
  ptr -> next = NULL;
  InsertQueue(waitingQueue,ptr);
  
  
}
void IO_processing(QUEUE* readyQueue,QUEUE* waitingQueue){
  NODE* pre = NULL;
  NODE* loc = waitingQueue -> out;
  while(loc != NULL){
    loc -> process ->IO_burst -= 1;
    if(loc -> process -> IO_burst == 0){
      NODE* temp = loc -> next;
      if(pre == NULL){
        waitingQueue -> out = loc -> next;
        if(waitingQueue -> out == NULL){
          waitingQueue -> in = NULL;
        }
        
      }else{
        pre -> next = loc -> next;
        if(loc->next == NULL){
          waitingQueue -> in = pre;
        }
      }
      loc -> process ->IO_requestTime = -1;
      loc->next = NULL;
      InsertQueue(readyQueue,loc);
      loc = temp;
    }else{
      pre = loc;
      loc = loc -> next;
    }
  }
}