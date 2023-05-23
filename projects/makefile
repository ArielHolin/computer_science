CC = gcc
INCLUDE = -I ./include/
GUARDFILES1 = commun_guard.c scheduler.c uid.c task.c
GUARDFILES2 = pqueue.c heap.c sorted_list.c dlist.c vector.c
APPFILES = app.c wdt.c
LIB_FLAGS = -shared -fPIC -pedantic-errors -Wall -Wextra 
COMPILE_FLAGS = -pedantic-errors -Wall -Wextra -g -pthread
SHAREDLIB = -L/home/ariel/infinitylabs/git/projects
SHAREDFILE = -lguard
WDTFILES = main_wdt.c
RM = rm -f

all: app main_wdt lib

app: $(APPFILES) | lib
	$(CC) $(SHAREDLIB) $(INCLUDE) $(COMPILE_FLAGS) -o $@ $^ $(SHAREDFILE) 

main_wdt: $(WDTFILES) | lib
	$(CC) $(SHAREDLIB) $(INCLUDE) $(COMPILE_FLAGS) -o $@ $^ $(SHAREDFILE) 

lib :  $(GUARDFILES1) $(GUARDFILES2)
	$(CC) $(INCLUDE) $(LIB_FLAGS) -o libguard.so $^



.PHONE:clean
clean:
	$(RM) libguard.so app main_wdt
