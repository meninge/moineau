CC = gcc
CFLAGS = -Wall -g -Wno-missing-braces
LDFLAGS =
EXEC = moineau
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

ifeq (, $(NEURONS))
	NEURONS = 100
endif
CFLAGS += -DNEURONS_FIRST_LAYER=$(NEURONS)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm src/*.o

parse:
	cd extra; python parser.py $(NEURONS)
