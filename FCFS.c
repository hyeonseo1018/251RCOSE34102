#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"

void FCFS(NODE** processesOrigin,const int processCount){
  QUEUE* queue = (QUEUE*)malloc(sizeof(QUEUE));
  queue = createQueue();
  NODE** processes = copyProcesses(processesOrigin,processCount);
  for(int i =0; i<processCount;i++){
    insertQueue(queue,processes[i]);
  }
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
