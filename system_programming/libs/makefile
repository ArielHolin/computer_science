CC=gcc
_PATH = -L.
CFLAGS=-ansi -Wall -Wextra -g
SOFLAGS = -shared
ARFLAGS = rcs
DEPS = libar.h
STAT_OBJ = a.o a1.o a2.o


#linking with libso1.so shared object implicitly at program start up
#linking with libso2.so shared object explicitly at run time with -ldl flag
main: main.o libar.a libso1.so libso2.so $(DEPS)
	$(CC) $(CFLAGS) $(_PATH) -Wl,-rpath=. main.c -ldl -lso1 -lso2 libar.a -o main
	
#create new static lib
libar.a: $(STAT_OBJ)
	ar $(ARFLAGS) -o $@ $^

#create new dynamic lib1
libso1.so: so1.o
	$(CC) $(SOFLAGS) -o $@ $^
	
#create new dynamic lib2
libso2.so: so2.o libar.a $(DEPS)
	$(CC) $(SOFLAGS) -o $@ $^

a.o: a.c
	$(CC) -c -o $@ $^ $(CFLAGS)
	
a1.o: a1.c
	$(CC) -c -o $@ $^ $(CFLAGS)
	
a2.o: a2.c
	$(CC) -c -o $@ $^ $(CFLAGS)
	
so1.o: so1.c 
	$(CC) -c -fPIC -o $@ $<
	
so2.o: so2.c $(DEPS)
	$(CC) -c -fPIC -o $@ $<
	
clean:
	$(RM) *.o *.so libar.a main

