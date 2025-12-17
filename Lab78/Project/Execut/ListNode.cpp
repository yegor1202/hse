#include"ListNode.h"

ListNode::ListNode(const PCB& pcb) : data(pcb), next(nullptr) {
};

ListNode* ListNode::getNext() { 
    return next;
};

int ListNode::getID(){ 
    return data.processID;
};

void ListNode::setNext(ListNode* newNext){ 
    next = newNext;
};

PCB ListNode::getData(){
    return data;
};