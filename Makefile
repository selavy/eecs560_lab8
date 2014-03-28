CC = g++
CFLAGS = -std=c++11 -Wall -Werror -g

OBJS = main.o

lab8: $(OBJS)
	$(CC) $(CFLAGS) -o lab8 $(OBJS)
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
.PHONY: clean
clean:
	rm -rf *.o lab8