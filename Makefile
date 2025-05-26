all: sched

sched: main.o FCFS.o SJF.o priority.o RR.o preemptiveSJF.o preemptivePriority.o
	gcc main.o FCFS.o SJF.o priority.o RR.o preemptiveSJF.o preemptivePriority.o -o sched

main.o: main.c
	gcc -Wall -Wextra -MMD -MP -c main.c -o main.o

FCFS.o: FCFS.c
	gcc -Wall -Wextra -MMD -MP -c FCFS.c -o FCFS.o
SJF.o: SJF.c
	gcc -Wall -Wextra -MMD -MP -c SJF.c -o SJF.o
preemptiveSJF.o: preemptiveSJF.c
	gcc -Wall -Wextra -MMD -MP -c preemptiveSJF.c -o preemptiveSJF.o
priority.o: priority.c
	gcc -Wall -Wextra -MMD -MP -c priority.c -o priority.o
preemptivePriority.o: preemptivePriority.c
	gcc -Wall -Wextra -MMD -MP -c preemptivePriority.c -o preemptivePriority.o
RR.o: RR.c
	gcc -Wall -Wextra -MMD -MP -c RR.c -o RR.o
clean:
	rm -f sched main.o FCFS.o SJF.o priority.o RR.o preemptiveSJF.o preemptivePriority.o main.d FCFS.d SJF.d priority.d RR.d preemptiveSJF.d preemptivePriority.d

.PHONY: all clean

-include main.d FCFS.d
