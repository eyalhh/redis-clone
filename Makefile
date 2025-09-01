CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = redis-clone

SRC = main.c hashmap/hashmap.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)
