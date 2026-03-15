#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>

class TaskQueue {
private:
    std::queue<int> tasks;
    std::mutex mtx;
    std::condition_variable cv;

public:
    void push(int task) {
        std::unique_lock<std::mutex> lock(mtx);
        tasks.push(task);
        cv.notify_one();
    };

    int pop() {
        std::unique_lock<std::mutex> lock(mtx);

        cv.wait(lock, [this]() {
            return !tasks.empty();
        });

        int task = tasks.front();
        tasks.pop();
        return task;
    };
};

std::mutex coutMutex;

void worker(TaskQueue& queue, int id) {
    while (true) {
        int task = queue.pop();

        if (task == -1) {
            break;
        };
        std::this_thread::sleep_for(std::chrono::seconds(1));

        {   std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << "[Worker-" << id
                      << "] обработал задачу "
                      << task << std::endl;
        };
    };
};


int main() {
    TaskQueue queue;

    const int N = 4;

    std::vector<std::thread> workers;

    for (int i = 0; i < N; i++) {
        workers.emplace_back(worker, std::ref(queue), i + 1);
    };

    for (int i = 1; i <= 20; i++) {
        queue.push(i);
    };

    for (int i = 0; i < N; i++) {
        queue.push(-1);
    };

    for (auto& t : workers) {
        t.join();
    };

    return 0;
};