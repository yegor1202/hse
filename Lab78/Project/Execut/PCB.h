#ifndef PCB_H
#define PCB_h

#include<iostream>
#include<string>

enum ProcessStatus{
    RUNNING,
    WAITING,
    STOPPED
};

struct PCB{
    int processID;
    std::string processName;
    ProcessStatus processStatus;
    int commandCounter;
    int cpuRegisters[8];
};

#endif