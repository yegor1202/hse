#ifndef GROUPSTATS_H
#define GROUPSTATS_H

#include <vector>
#include <map>
#include <cstddef>

template<typename KeyType, typename T, typename ValueType>
struct GroupInfo {
    KeyType key;
    size_t count;
    T minElem;
    T maxElem;
    ValueType sum;
    double avg;
};
template<typename T, typename KeyFunc, typename ValueFunc>
auto groupStats(T* arr, size_t n, KeyFunc keyFunc, ValueFunc valueFunc) 
    -> std::vector<GroupInfo<decltype(keyFunc(arr[0])), T, decltype(valueFunc(arr[0]))>> {
    
    using KeyType = decltype(keyFunc(arr[0]));
    using ValueType = decltype(valueFunc(arr[0]));
    
    std::map<KeyType, GroupInfo<KeyType, T, ValueType>> groups;
    
    for (size_t i = 0; i < n; ++i) {
        KeyType key = keyFunc(arr[i]);
        ValueType val = valueFunc(arr[i]);
        
        if (groups.find(key) == groups.end()) {
            GroupInfo<KeyType, T, ValueType> info;
            info.key = key;
            info.count = 1;
            info.minElem = arr[i];
            info.maxElem = arr[i];
            info.sum = val;
            info.avg = 0.0;
            groups[key] = info;
        } 
        else {
            auto& info = groups[key];
            info.count++;
            if (arr[i] < info.minElem) info.minElem = arr[i];
            if (info.maxElem < arr[i]) info.maxElem = arr[i];
            info.sum += val;
        }
    }
    
    std::vector<GroupInfo<KeyType, T, ValueType>> result;
    for (auto& pair : groups) {
        auto& info = pair.second;
        info.avg = static_cast<double>(info.sum) / info.count;
        result.push_back(info);
    }
    
    return result;
}

#endif // GROUPSTATS_H