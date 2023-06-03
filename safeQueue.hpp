#include <queue>
#include <mutex>
#include <condition_variable>

class SafeQueue {
private:
    std::queue<void*> q;
    std::mutex m;
    std::condition_variable cv;

public:
    void enqueue(void* item) {
        std::lock_guard<std::mutex> lock(m);
        q.push(item);
        cv.notify_one();
    }

    void* dequeue() {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [this]{ return !q.empty(); });
        void* val = q.front();
        q.pop();
        return val;
    }
};
