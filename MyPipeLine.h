#ifndef MYPIPELINE_H
#define MYPIPELINE_H

#include <vector>
#include <functional>
#include <string>
#include <stdexcept>
#include <iostream>

template<class T>
class MyPipeline {
private:
    struct Step {
        std::string name;
        std::function<T(T)> func;
    };

    std::vector<Step> steps;

public:
    MyPipeline() = default;

    size_t size() const {
        return steps.size();
    }

    bool empty() const {
        return steps.empty();
    }

    void clear() {
        steps.clear();
    }

    template<class F>
    void addStep(const std::string& name, F func) {
        if (name.empty()) {
            throw std::invalid_argument("Step name cannot be empty");
        }

        steps.push_back({name, func});
    }

    void removeStep(size_t index) {
        if (index >= steps.size()) {
            throw std::out_of_range("Index out of range");
        }

        steps.erase(steps.begin() + index);
    }

    T run(T value) const {
        for (const auto& step : steps) {
            value = step.func(value);
        }
        return value;
    }

    std::vector<T> trace(T value) const {
        std::vector<T> result;

        for (const auto& step : steps) {
            value = step.func(value);
            result.push_back(value);
        }

        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const MyPipeline<T>& p) {
        os << "Pipeline steps: " << p.size() << std::endl;

        for (size_t i = 0; i < p.steps.size(); ++i) {
            os << i << ") " << p.steps[i].name << std::endl;
        }

        return os;
    }
};

#endif