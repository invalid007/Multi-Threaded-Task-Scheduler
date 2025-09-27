CXX = g++
CXXFLAGS = -std=c++11 -Wall -pthread
INCLUDE = -Iinclude

SRC = src/main.cpp src/producer.cpp src/consumer.cpp

all: task_scheduler

task_scheduler:
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(SRC) -o task_scheduler

clean:
	rm -f task_scheduler logs/task_log.txt
