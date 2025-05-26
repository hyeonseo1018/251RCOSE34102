#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"

void RR(NODE** processesOrigin,int totalBurst,int timeQuantum){
  int timeQuantumCount = 0;
  int turnAroundTime = 0;
  QUEUE* readyQueue = (QUEUE*)malloc(sizeof(QUEUE));
  QUEUE* waitingQueue = (QUEUE*)malloc(sizeof(QUEUE));
  readyQueue = createQueue();
  waitingQueue = createQueue();
  NODE** processes = copyProcesses(processesOrigin);
  int index = 0;
  int clock = 0;
  InsertReadyQueue(readyQueue,processes,clock,&index);
  printClock(clock);
  do{
    NODE* ptr = readyQueue -> out;
    if(ptr != NULL){
      if(ptr -> process -> burstTime == ptr -> process -> IO_requestTime){
        timeQuantumCount = 0;
        IO_request(readyQueue,waitingQueue,ptr);
      }else{
        ptr -> process -> burstTime -= 1;
        timeQuantumCount += 1;
        if(waitingQueue->out!=NULL)IO_processing(readyQueue,waitingQueue);
        printf("P%d   ",ptr -> process->PID);
        clock += 1;
        if(ptr -> process -> burstTime == 0){
          turnAroundTime += clock - ptr -> process -> arrivalTime;
          readyQueue -> out = ptr -> next;
          timeQuantumCount = 0;
          free(ptr -> process);
          free(ptr);
        }else if(timeQuantumCount == timeQuantum){
          timerEvent(readyQueue,ptr);
          timeQuantumCount = 0;
        }
        
        InsertReadyQueue(readyQueue,processes,clock,&index);
        if(clock%25 == 0){
          printf("\n\n");
          printClock(clock);
        }
      }
    }else{
      if(waitingQueue->out!=NULL)IO_processing(readyQueue,waitingQueue);
      printf("idle ");
      clock +=1;
      InsertReadyQueue(readyQueue,processes,clock,&index);
      if(clock%25 == 0){
        printf("\n\n");
        printClock(clock);
      }
    }
    
    
  }while(index < PROCESSCOUNT || readyQueue -> out != NULL || waitingQueue -> out != NULL);
  free(readyQueue);
  printf("\n");
  printf("turnaround time : %d\n",turnAroundTime);
  printf("waiting time : %d\n",turnAroundTime - totalBurst);
}
void timerEvent(QUEUE* readyQueue,NODE* ptr){
  readyQueue -> out = ptr -> next;
  ptr -> next = NULL;
  InsertQueue(readyQueue,ptr);
}