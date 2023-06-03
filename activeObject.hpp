#ifndef ACTIVEOBJECT_HPP
#define ACTIVEOBJECT_HPP

#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <functional>
#include "safeQueue.hpp"  // Assuming you have SafeQueue in a separate header file

class activeObject {
private:
    SafeQueue* queue;
    std::function<void(void*)> func;
    std::thread* workerThread;
    bool stopFlag;

    void processQueue();

public:
    activeObject(std::function<void(void*)> func);
    SafeQueue* getQueue();
    void stop();
};

#endif  // ACTIVEOBJECT_HPP
