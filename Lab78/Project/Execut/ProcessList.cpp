#include"ProcessList.h"
#include<iostream>
#include<string>

using namespace std;

ProcessList::ProcessList():head(nullptr){
};
ProcessList::~ProcessList(){
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->getNext();
        delete temp;
    }
};



void ProcessList::printList(){
    if (head == nullptr){
        cout << "Список пуст" << endl;
        return;
    };

    ListNode* current = head;
    int counter = 1;

    while (current != nullptr) {
        const PCB& pcb = current->getData();
        
        string statusStr;
        switch (pcb.processStatus) {
            case RUNNING: statusStr = "Running"; break;
            case WAITING: statusStr = "Waiting"; break;
            case STOPPED: statusStr = "Stopped"; break;
            default: statusStr = "Unknown"; break;
        }
        
        cout << "Процесс #" << counter << ":" << endl;
        cout << "  ID: " << pcb.processID << endl;
        cout << "  Имя: " << pcb.processName << endl;
        cout << "  Статус: " << statusStr << endl;
        cout << "  Счетчик команд: " << pcb.commandCounter << endl;
        
        cout << "  Регистры CPU: [";
        for (const int cpu : pcb.cpuRegisters) {
            cout << cpu << "";   
        };
        cout << endl;
        
        current = current->getNext();
        counter++;
    }
    
    cout << "========================" << endl;
};



bool ProcessList::remove(int pid){
    //ПОиск с начала списка заданного id

    ListNode* current = head;

    while (current->getID() != pid || current == nullptr){
        if (current == nullptr ){
            cout << "Найти процесс по заданному ID не удалось" << endl;
            return false;
            break;
        }else if(current->getID() == pid){
            delete current;
            cout << "Процесс " << pid << "Успешно удален";
            return true;
            break;
        };
        current = current->getNext();
    };

};

bool ProcessList::insert(const PCB& newPCB){

    //Проверка на повторение ID
    ListNode* current = head;

    while (current -> getNext() != nullptr){
        if (current->getID() == newPCB.processID){
            return false;
            break;
        };
        current = current->getNext();
    };

    //Случай, если список пуст:
    ListNode* position = new ListNode(newPCB);
    if (head == nullptr){
        position = head;
        position->setNext(nullptr);
        return true;
    }
    else { 
         //Ищем место,куда необходимо вставить новый элемент
        while (current != nullptr){
            if (current-> getNext()->getID() < newPCB.processID){
                current = current->getNext();
            }else {
                position->setNext(current->getNext());
                current->setNext(position);
                return true;
                break;
            };
        };
};

