LIBS = -lssl -lcrypto
DEPS = nma.h
OBJ = nma.o main.o

ifndef $(CC)
CC = gcc
else
CC = $(CC)
LIBS = $(LIBS) -I/home/spksrc/toolchains/syno-qoriq/work/powerpc-none-linux-gnuspe/include/
endif

ifndef $(LD)
LD = ld
else
LD = $(LD)
endif

ifndef $(DESTDIR)
DESTDIR = /usr
else
DESTDIR = $(DESTDIR)
endif

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $(LIBS) $<

nma: $(OBJ)
	$(CC) -o $@ $(LIBS) $^

install: nma
	install -Dm 0755 nma $(DESTDIR)/bin/nma

clean:
	rm -f *.o nma
