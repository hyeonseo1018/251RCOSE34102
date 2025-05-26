#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"

void FCFS(NODE** processesOrigin,int totalBurst){
  int turnAroundTime = 0;
  QUEUE* readyQueue = createQueue();
  QUEUE* waitingQueue = createQueue();
  NODE** processes = copyProcesses(processesOrigin);
  int index = 0;
  int clock = 0;
  InsertReadyQueue(readyQueue,processes,clock,&index);
  printClock(clock);
  do{
    NODE* ptr = readyQueue -> out;
    if(ptr != NULL){
      if(ptr -> process -> burstTime == ptr -> process -> IO_requestTime){
      IO_request(readyQueue,waitingQueue,ptr);
      }else{
        ptr -> process -> burstTime -= 1;
        if(waitingQueue->out!=NULL)IO_processing(readyQueue,waitingQueue);
        printf("P%d   ",ptr -> process->PID);
        clock += 1;
        InsertReadyQueue(readyQueue,processes,clock,&index);
        if(clock%25 == 0){
          printf("\n\n");
          printClock(clock);
        }
        
        if(ptr -> process -> burstTime == 0){
          turnAroundTime += clock - ptr -> process -> arrivalTime;
          readyQueue -> out = ptr -> next;
          free(ptr -> process);
          free(ptr);
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
  free(waitingQueue);
  free(processes);
  printf("\n");
  printf("turnaround time : %d\n",turnAroundTime);
  printf("waiting time : %d\n",turnAroundTime - totalBurst);
}
