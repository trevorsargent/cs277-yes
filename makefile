CC=gcc
EXEC=yes
OBJS=*.o
SOURCES=*.c

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC)  $(OBJS) -o $(EXEC)

.c.o:
	$(CC) -IHeaders/ -c *.c

clean:
	rm -f $(OBJS) $(EXEC) a.out