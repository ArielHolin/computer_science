CC=gcc
OBJ=scheduler_test.o scheduler.o task.o pqueue.o uid.o sorted_list.o dlist.o
DEPS=../src/scheduler.c ../src/task.c ../src/uid.c ../src/pqueue.c ../src/sorted_list.c ../src/dlist.c ../include/scheduler.h ../include/task.h ../include/uid.h ../include/pqueue.h ../include/sorted_list.h ../include/dlist.h
CFLAGS=-ansi -pedantic -errors -Wall -Wextra -g -I ../include/

scheduler: $(OBJ)
	$(CC) -o $@ $(OBJ)
	
dlist.o: ../src/dlist.c ../include/dlist.h
	$(CC) $(CFLAGS) -c $^
	
sorted_list.o: ../src/sorted_list.c ../src/dlist.c ../include/sorted_list.h ../include/dlist.h
	$(CC) $(CFLAGS) -c $^
	
uid.o: ../src/uid.c ../include/uid.h
	$(CC) $(CFLAGS) -c $^
	
pqueue.o: ../src/pqueue.c ../src/sorted_list.c ../src/dlist.c ../include/pqueue.h ../include/sorted_list.h ../include/dlist.h
	$(CC) $(CFLAGS) -c $^
          
task.o: ../src/task.c ../src/uid.c ../include/task.h ../include/uid.h
	$(CC) $(CFLAGS) -c $^
     
scheduler.o: $(DEPS)
	$(CC) $(CFLAGS) -c $^
     
scheduler_test.o: scheduler_test.c $(DEPS)
	$(CC) $(CFLAGS) -c $^
     
.PHONY: clean
clean:
	rm scheduler $(OBJ)
