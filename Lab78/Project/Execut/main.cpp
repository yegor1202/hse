#include <iostream>
#include "ProcessList.h"

using namespace std;

PCB createPCB(int id, const string& name, ProcessStatus status, int counter) {
    PCB pcb;
    pcb.processID = id;
    pcb.processName = name;
    pcb.processStatus = status;
    pcb.commandCounter = counter;
    
    for (int i = 0; i <8; i++) {
        pcb.cpuRegisters[i] = i * 10;
    }
    
    return pcb;
}

int main() {
    cout << "=== Лабораторная работа 7-8:===" << endl;
    cout << "=============================\n" << endl;
    

    cout << "1. Создание списка процессов..." << endl;
    ProcessList processList;
    cout << "Список создан успешно.\n" << endl;
    

    cout << "2. Добавление элементов в список..." << endl;
    
    PCB pcb1 = createPCB(3, "System", RUNNING, 0);
    PCB pcb2 = createPCB(1, "Initialisation", RUNNING, 10);
    PCB pcb3 = createPCB(5, "User", WAITING, 25);
    PCB pcb4 = createPCB(2, "Driver", STOPPED, 5);
    PCB pcb5 = createPCB(4, "Service", WAITING, 15);
    
 
    cout << "\nДобавим процессы:" << endl;
    processList.insert(pcb1); 
    processList.insert(pcb2); 
    processList.insert(pcb3); 
    processList.insert(pcb4); 
    processList.insert(pcb5); 
    
    cout << "\n3. Вывод списка после добавления всех процессов:" << endl;
    processList.printList();
    
    cout << "\n4. Удаление элементов из списка..." << endl;
    
    cout << "\nПопытка удалить процесс с ID 2 (существует):" << endl;
    processList.remove(2);
    
    cout << "\nПопытка удалить процесс с ID 99 (не существует):" << endl;
    processList.remove(99);

    cout << "\n5. Вывод списка после удаления:" << endl;
    processList.printList();
    
    cout << "\n6. Демонстрация неудачных операций:" << endl;
    
    cout << "\nПопытка добавить процесс с ID 3 (дубликат):" << endl;
    PCB duplicatePCB = createPCB(3, "Duplicate", STOPPED, 0);
    processList.insert(duplicatePCB);
    
    cout << "\nПопытка удалить процесс с ID 100 (не существует):" << endl;
    processList.remove(100);
    
    cout << "\n7. Финальное состояние списка:" << endl;
    processList.printList();
    
    cout << "Конец" << endl;
    
    return 0;
}