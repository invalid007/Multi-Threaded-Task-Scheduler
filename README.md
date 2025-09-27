# Multi-Threaded Task Scheduler (10,000+ Tasks)

## Overview
Simulates a task scheduling system with multiple producers and consumers using C++ threads.
Supports 10,000+ tasks safely with few threads.

## Features

- **Multi-Producer, Multi-Consumer Model**: Utilizes multiple producer and consumer threads to simulate a real-world task scheduling environment.
- **Thread-Safe Queue**: Implements a thread-safe queue using mutexes and condition variables to ensure safe data access across threads.
- **Logging**: Provides detailed logging of task production and consumption events for monitoring and debugging purposes.
- **Scalability**: Designed to handle a large number of tasks efficiently, showcasing the scalability of the system.

## Requirements

- C++11 or higher
- g++ compiler (Linux/Mac) or MinGW (Windows)

## How to Run
```bash
# Linux/Mac
make
./main
```
# Windows (VS Code + MinGW)
g++ -std=c++11 main.cpp -o task_scheduler -pthread
./task_scheduler

