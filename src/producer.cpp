#include "../include/task_scheduler.h"

void producer(int producerId, int tasksToProduce) {
    for (int i = 0; i < tasksToProduce; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv_full.wait(lock, [] { return taskQueue.size() < MAX_QUEUE_SIZE; });

        Task t;
        t.id = taskCounter++;
        t.priority = rand() % 100;
        t.type = (rand() % 2 == 0) ? TaskType::CPU_BOUND : TaskType::IO_BOUND;
        t.description = "Task " + std::to_string(t.id) + " from Producer " + std::to_string(producerId);
        t.created_time = std::chrono::high_resolution_clock::now();

        taskQueue.push(t);
        logFile << "[Producer " << producerId << "] Produced task " << t.id 
                << " Type: " << ((t.type==TaskType::CPU_BOUND)?"CPU":"IO")
                << " Priority: " << t.priority << std::endl;

        lock.unlock();
        cv_empty.notify_all();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}
