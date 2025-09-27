#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <cstdlib>

// Max tasks in queue
const int MAX_QUEUE_SIZE = 1000;

// Task types
enum class TaskType { CPU_BOUND, IO_BOUND };

// Task structure
struct Task {
    int id;
    int priority;
    TaskType type;
    std::string description;
    std::chrono::time_point<std::chrono::high_resolution_clock> created_time;

    bool operator<(const Task& other) const {
        return priority < other.priority; // max-heap
    }
};

// Shared resources
extern std::priority_queue<Task> taskQueue;
extern std::mutex mtx;
extern std::condition_variable cv_full, cv_empty;
extern int taskCounter;
extern bool stopAll;

// Logging
extern std::ofstream logFile;

// Statistics
extern int totalTasksProcessed;
extern long long totalWaitTimeMs;

#endif
