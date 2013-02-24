CC=gcc

LIBS=-lssl -lcrypto
CFLAGS=-I.
DEPS = nma.h
OBJ = nma.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $(LIBS) $<

nma: $(OBJ)
	$(CC) -o $@ $(LIBS) $^

clean:
	rm -f *.o nma
