CC=gcc -Wall -g
CFLAGS=
OBJ=proj2.o graphs.o
HEAD=proj2.h

All: proj2 outros

proj2: $(OBJ)
	$(CC) $(OBJ) -o $@ $(CFLAGS)

proj2.o: proj2.c proj2.h $(HEAD)
	$(CC) -c proj2.c $(CFLAGS)

graphs.o: graphs.c proj2.h
	$(CC) -c graphs.c $(CFLAGS)

outros:
	rm *.o

clean:
	rm proj2
