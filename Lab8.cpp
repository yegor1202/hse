#include <iostream>
#include <string>
#include "group_stats.h"

int main() {
    std::cout << "Array of int:" << std::endl;
    int intArr[] = {12, 23, 45, 56, 67, 78, 89, 90, 11, 22};
    auto intGroups = groupStats(intArr, 10, 
        [](int x) { return x % 10; },  
        [](int x) { return x; }        
    );
    
    for (const auto& g : intGroups) {
        std::cout << g.key << ", " << g.count << ", " 
                  << g.minElem << ", " << g.maxElem << ", " 
                  << g.sum << ", " << g.avg << std::endl;
    }

    std::cout << "\nArray of double:" << std::endl;
    double doubleArr[] = {-5.0, 3.5, 12.3, 0.0, 7.8, 15.2, -1.1, 10.0, 20.5, 5.5};
    auto doubleGroups = groupStats(doubleArr, 10,
        [](double x) { 
            if (x < 0) return 0;
            else if (x <= 10) return 1;
            else return 2;
        },
        [](double x) { return x; }
    );
    
    for (const auto& g : doubleGroups) {
        std::cout << g.key << ", " << g.count << ", " 
                  << g.minElem << ", " << g.maxElem << ", " 
                  << g.sum << ", " << g.avg << std::endl;
    }
    
    std::cout << "\nArray of string:" << std::endl;
    std::string strArr[] = {"apple", "banana", "cat", "cherry", "ball", "dog"};
    auto strGroups = groupStats(strArr, 6,
        [](const std::string& s) { return s[0]; }, 
        [](const std::string& s) { return s.length(); } 
    );
    
    for (const auto& g : strGroups) {
        std::cout << g.key << ", " << g.count << ", " 
                  << g.minElem << ", " << g.maxElem << ", " 
                  << g.sum << ", " << g.avg << std::endl;
    }
    std::cin.get();
    return 0;
}