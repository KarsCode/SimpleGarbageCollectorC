CC = gcc
CFLAGS = -Wall -Iinclude
SRC = src/gc.c src/memory.c src/root_scan.c
TEST = tests/test_gc.c
OUT = test_gc

all: $(OUT)

$(OUT): $(SRC) $(TEST)
	$(CC) $(CFLAGS) $(SRC) $(TEST) -o $(OUT)

clean:
	rm -f $(OUT)
