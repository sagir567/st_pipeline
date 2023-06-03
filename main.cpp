#include <cstdlib>
#include <ctime>
#include <iostream>
#include "activeObject.hpp"
#include <unistd.h>
static int counter;
bool isPrime(unsigned int num) {
    if(num <3) return true;
    else{
        for(int i =3 ;i*i<num ;i+=2){
            if(num%i ==0)return false;
        }
        return true;
    }
}

void func1(void* item, SafeQueue* nextQueue) {
    int num = *(static_cast<int*>(item));
    bool prime = isPrime(num);

    nextQueue->enqueue(static_cast<void*>(&num));
}

void func2(void* item, SafeQueue* nextQueue) {
    std::cout << *(static_cast<int*>(item)) << std::endl;

    bool prime = isPrime(*(static_cast<int*>(item)));
    std::cout << (prime ? "true" : "false") << std::endl;
    int num = *(static_cast<int*>(item)) + 11;


    nextQueue->enqueue(static_cast<void*>(&num));
}

void func3(void* item, SafeQueue* nextQueue) {
    std::cout << *(static_cast<int*>(item)) << std::endl;
    bool prime = isPrime(*(static_cast<int*>(item)));

    std::cout << (prime ? "true" : "false") << std::endl;
    int num = *(static_cast<int*>(item)) - 13;

    nextQueue->enqueue(static_cast<void*>(&num));
}

void func4(void* item) {
    std::cout << *(static_cast<int*>(item)) << std::endl;
    int num = *(static_cast<int*>(item)) + 2;
    bool prime = isPrime(num);
    std::cout << (prime ? "true" : "false") << std::endl;
    std::cout << num << std::endl;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int N;
    int seed;
    if (argc == 2) {
        N = atoi(argv[1]);
        seed = time(NULL);
    } else if (argc == 3) {
        N = atoi(argv[1]);
        seed = atoi(argv[2]);
    } else {
        std::cout << "Invalid input format. Usage: ./st_pipeline N [S]" << std::endl;
        return 1;
    }

    srand(seed);
    counter = N;
    activeObject AO4(func4);
    activeObject AO3(std::bind(func3, std::placeholders::_1, AO4.getQueue()));
    activeObject AO2(std::bind(func2, std::placeholders::_1, AO3.getQueue()));
    activeObject AO1(std::bind(func1, std::placeholders::_1, AO2.getQueue()));

    // Set up the pipeline manually
    AO1.getQueue()->setNextQueue(AO2.getQueue());
    AO2.getQueue()->setNextQueue(AO3.getQueue());
    AO3.getQueue()->setNextQueue(AO4.getQueue());

    for (int i = 0; i < N; ++i) {
        int num = rand() % 1000000;
        AO1.getQueue()->enqueue(static_cast<void *>(&num));
        usleep(1000);
        counter--;
    }
    if (counter == 0)
        exit(0);

    AO1.stop();
    AO2.stop();
    AO3.stop();
    AO4.stop();
    return 0;
}