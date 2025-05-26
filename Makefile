all: sched

sched: main.o FCFS.o SJF.o priority.o RR.o preemtiveSJF.o preemtivePriority.o
	gcc main.o FCFS.o SJF.o priority.o RR.o preemtiveSJF.o preemtivePriority.o -o sched

main.o: main.c
	gcc -Wall -Wextra -MMD -MP -c main.c -o main.o

FCFS.o: FCFS.c
	gcc -Wall -Wextra -MMD -MP -c FCFS.c -o FCFS.o
SJF.o: SJF.c
	gcc -Wall -Wextra -MMD -MP -c SJF.c -o SJF.o
preemtiveSJF.o: preemtiveSJF.c
	gcc -Wall -Wextra -MMD -MP -c preemtiveSJF.c -o preemtiveSJF.o
priority.o: priority.c
	gcc -Wall -Wextra -MMD -MP -c priority.c -o priority.o
preemtivePriority.o: preemtivePriority.c
	gcc -Wall -Wextra -MMD -MP -c preemtivePriority.c -o preemtivePriority.o
RR.o: RR.c
	gcc -Wall -Wextra -MMD -MP -c RR.c -o RR.o
clean:
	rm -f sched main.o FCFS.o SJF.o priority.o RR.o preemtiveSJF.o preemtivePriority.o main.d FCFS.d SJF.d priority.d RR.d preemtiveSJF.d preemtivePriority.d

.PHONY: all clean

-include main.d FCFS.d
