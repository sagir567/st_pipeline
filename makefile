# makefile

CC = g++
CFLAGS = -Wall -std=c++11 -pthread
OBJS = main.o activeObject.o
TARGET = st_pipeline

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp activeObject.hpp
	$(CC) $(CFLAGS) -c main.cpp

activeObject.o: activeObject.cpp activeObject.hpp
	$(CC) $(CFLAGS) -c activeObject.cpp

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)
