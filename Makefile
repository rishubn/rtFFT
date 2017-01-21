CC=clang
CFLAGS=-c -Wall
LDFLAGS=-lm
SOURCES=main.c fft.c
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

