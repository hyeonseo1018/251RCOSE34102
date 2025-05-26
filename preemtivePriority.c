#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"

void preemtivePriority(NODE** processesOrigin,int totalBurst){
  int turnAroundTime = 0;
  QUEUE* readyQueue = (QUEUE*)malloc(sizeof(QUEUE));
  QUEUE* waitingQueue = (QUEUE*)malloc(sizeof(QUEUE));
  readyQueue = createQueue();
  waitingQueue = createQueue();
  NODE** processes = copyProcesses(processesOrigin);
  int index = 0;
  int clock = 0;
  preemtivePriorityInsertReadyQueue(readyQueue,processes,clock,&index);
  printClock(clock);
  do{
    NODE* ptr = readyQueue -> out;
    if(ptr != NULL){
      if(ptr -> process -> burstTime == ptr -> process -> IO_requestTime){
      IO_request(readyQueue,waitingQueue,ptr);
      }else{
        ptr -> process -> burstTime -= 1;
        if(waitingQueue->out!=NULL)preemtivePriority_IO_processing(readyQueue,waitingQueue);
        printf("P%d   ",ptr -> process->PID);
        clock += 1;
        preemtivePriorityInsertReadyQueue(readyQueue,processes,clock,&index);
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
      if(waitingQueue->out!=NULL)preemtivePriority_IO_processing(readyQueue,waitingQueue);
      printf("idle ");
      clock +=1;
      preemtivePriorityInsertReadyQueue(readyQueue,processes,clock,&index);
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
void preemtivePriorityInsertReadyQueue(QUEUE* readyQueue,NODE** processes,int clock,int* index){
  NODE* node = NULL;
  while(*index < PROCESSCOUNT){
    node = processes[*index];
    if(node -> process -> arrivalTime == clock){
      preemtivePriorityInsertQueue(readyQueue,node);
      *index+=1;
    }else{
      break;
    }
  }    
  
}

void preemtivePriority_IO_processing(QUEUE* readyQueue,QUEUE* waitingQueue){
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
      preemtivePriorityInsertQueue(readyQueue,loc);
      loc = temp;
    }else{
      pre = loc;
      loc = loc -> next;
    }
  }
}
void preemtivePriorityInsertQueue(QUEUE* queue, NODE* node){
  if(queue -> out == NULL){
    queue -> out = node;
    queue -> in = node;
  }else{
    NODE* ptr = queue->out;
    if(ptr -> process -> priority > node -> process -> priority){
      node -> next = queue -> out -> next;
      if(node -> next == NULL){
        queue -> in = node;
      }
      queue -> out = node;
      preemtivePriorityInsertQueue(queue,ptr);
      
    }else{
      while(ptr -> next != NULL && (ptr -> next -> process -> priority < node -> process -> priority)){
      ptr = ptr -> next;
      }
      if(ptr -> next == NULL){
        queue-> in -> next = node;
        queue ->in = node;
      }else{
        node -> next = ptr -> next;
        ptr -> next = node;
      }
    }
    
  }
}