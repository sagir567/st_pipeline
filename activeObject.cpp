#include "activeObject.hpp"

void activeObject::processQueue() {

    while(!stopFlag) {
        void* task = this->queue->dequeue();
        this->func(task);
    }
}

activeObject::activeObject(std::function<void(void*)> func) : stopFlag(false) {
    this->queue = new SafeQueue();
    this->func = func;
    this->workerThread = new std::thread(&activeObject::processQueue, this);
}

SafeQueue* activeObject::getQueue() {
    return this->queue;
}

void activeObject::stop() {
    this->stopFlag = true;
    this->workerThread->join();
    delete this->workerThread;
    delete this->queue;
}
