CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I ../include
DEPS = ../include/fsa.h ../include/vsa.h
FSA_OBJ = ../obj/fsa.o ../obj/fsa_test.o
VSA_OBJ = ../obj/vsa.o ../obj/vsa_test.o


fsa: $(FSA_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	
../obj/fsa_test.o: fsa_test.c $(DEPS)
	$(CC) -c -o ../obj/$@ $< $(CFLAGS)
	
../obj/fsa.o: ../src/fsa.c $(DEPS)
	$(CC) -c -o ../obj/$@ $< $(CFLAGS)
	
vsa: $(VSA_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	
../obj/vsa_test.o: vsa_test.c $(DEPS)
	$(CC) -c -o ../obj/$@ $< $(CFLAGS)
	
../obj/vsa.o: ../src/vsa.c $(DEPS)
	$(CC) -c -o ../obj/$@ $< $(CFLAGS)
	
clean: 
	$(RM) fsa *.o *~ $(RM) vsa *.o *~


