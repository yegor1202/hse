#ifndef PROCESS_LIST

#include "ListNode.h"

class ProcessList{
    private:
    ListNode* head;

    public:
    ProcessList();
    ~ProcessList();
    
    bool insert(const PCB& newPCB);
    bool remove(int pid);
    void printList();
};

#endif