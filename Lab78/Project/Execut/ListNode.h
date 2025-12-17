#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "PCB.h"

class ListNode{
    private:
    ListNode* next;
    PCB data;

    public:
    ListNode(const PCB& pcb);

    ListNode* getNext();
    int getID();
    PCB getData();
    
    void setNext(ListNode* newNext);
};


#endif
