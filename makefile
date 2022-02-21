TARGET=ctm
LIBS=
CC=gcc
CFLAGS= -std=c99 -g -Wall -Werror -Wno-unused-variable

.PHONY: default all

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(LIBS) -o $@

clean: 
	-rm -f *.o *.tmp *.orig $(TARGET)

format:
	astyle --style=gnu --indent=spaces=4 *.c *.h
