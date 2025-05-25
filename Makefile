CC      = gcc
TARGET  = sched                 
SRC     = main.c fcfs.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $^ -o $@               # $^ = SRC 전체, $@ = TARGET

clean:
	rm -f $(TARGET)

.PHONY: all clean	