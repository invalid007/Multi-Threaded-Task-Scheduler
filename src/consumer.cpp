#include "../include/task_scheduler.h"

void consumer(int consumerId) {
    while (!stopAll || !taskQueue.empty()) {
        std::unique_lock<std::mutex> lock(mtx);
        cv_empty.wait(lock, [] { return !taskQueue.empty() || stopAll; });

        if (taskQueue.empty() && stopAll) break;

        Task t = taskQueue.top();
        taskQueue.pop();

        auto now = std::chrono::high_resolution_clock::now();
        auto waitTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - t.created_time).count();
        totalWaitTimeMs += waitTime;
        totalTasksProcessed++;

        logFile << "[Consumer " << consumerId << "] Consumed task " << t.id 
                << " Type: " << ((t.type==TaskType::CPU_BOUND)?"CPU":"IO")
                << " Priority: " << t.priority 
                << " WaitTime(ms): " << waitTime << std::endl;

        lock.unlock();
        cv_full.notify_all();

        // Simulate processing time
        std::this_thread::sleep_for(std::chrono::milliseconds((t.type==TaskType::CPU_BOUND)?50:30));
    }
}
