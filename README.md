# Multi-Threaded Task Scheduler (10,000+ Tasks)

## Overview
Simulates a task scheduling system with multiple producers and consumers using C++ threads.
Supports 10,000+ tasks safely with few threads.

## Features
- 2+ producers and 2+ consumers handling 10,000+ tasks
- Thread-safe queue using mutex and condition variables
- Logs task production and consumption events
- Scalable and modular design

## How to Run
```bash
# Linux/Mac
make
./main
```
# Windows (VS Code + MinGW)
g++ -std=c++11 main.cpp -o task_scheduler -pthread
./task_scheduler
