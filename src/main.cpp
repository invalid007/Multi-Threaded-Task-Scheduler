#include "../include/task_scheduler.h"

// Shared resources
std::priority_queue<Task> taskQueue;
std::mutex mtx;
std::condition_variable cv_full, cv_empty;
int taskCounter = 0;
bool stopAll = false;
std::ofstream logFile("logs/task_log.txt");
int totalTasksProcessed = 0;
long long totalWaitTimeMs = 0;

// Function declarations
void producer(int producerId, int tasksToProduce);
void consumer(int consumerId);

int main(int argc, char* argv[]) {
    int NUM_PRODUCERS = 2;
    int NUM_CONSUMERS = 2;
    int TASKS_PER_PRODUCER = 500;

    if(argc == 4) {
        NUM_PRODUCERS = std::stoi(argv[1]);
        NUM_CONSUMERS = std::stoi(argv[2]);
        TASKS_PER_PRODUCER = std::stoi(argv[3]);
    }

    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    // Start consumers
    for(int i=0;i<NUM_CONSUMERS;i++)
        consumers.emplace_back(consumer,i+1);

    // Start producers
    for(int i=0;i<NUM_PRODUCERS;i++)
        producers.emplace_back(producer,i+1,TASKS_PER_PRODUCER);

    // Join producers
    for(auto &t : producers) t.join();

    stopAll = true;
    cv_empty.notify_all();

    // Join consumers
    for(auto &t : consumers) t.join();

    logFile << "All tasks processed: " << totalTasksProcessed 
            << " Average WaitTime(ms): " << (totalTasksProcessed>0 ? totalWaitTimeMs/totalTasksProcessed : 0) 
            << std::endl;

    std::cout << "All tasks processed. Check logs/task_log.txt for details." << std::endl;
    logFile.close();
    return 0;
}
