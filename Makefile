CC=clang
CFLAGS=-c -Wall -g
LDFLAGS=-lm -lsndfile
SOURCES=main.c cbuffer.c
TESTS=tests/tests.c
TEST_SOURCES= $(filter-out main.c, $(SOURCES))
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=rtFFT

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	make clean

.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o

test:
	$(CC) $(LDFLAGS) $(TEST_SOURCES) $(TESTS) -o testexec

