#include <cstdlib>
#include <ctime>
#include "activeObject.hpp"

bool isPrime(int num) {
    if(num <= 1) return false;
    if(num <= 3) return true;
    if(num % 2 == 0 || num % 3 == 0) return false;

    for(int i = 5; i * i <= num; i += 6) {
        if(num % i == 0 || num % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

void func1(void *item) {
    int num = *(static_cast<int*>(item));
    bool prime = isPrime(num);
    std::cout << num << " " << (prime ? "true" : "false") << std::endl;
}

void func2(void *item) {
    int num = *(static_cast<int*>(item)) + 11;
    bool prime = isPrime(num);
    std::cout << num << " " << (prime ? "true" : "false") << std::endl;
}

void func3(void *item) {
    int num = *(static_cast<int*>(item)) - 13;
    bool prime = isPrime(num);
    std::cout << num << " " << (prime ? "true" : "false") << std::endl;
}

void func4(void *item) {
    int num = *(static_cast<int*>(item)) + 2;
    std::cout << num << std::endl;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int N = atoi(argv[1]);
    activeObject AO1(func1), AO2(func2), AO3(func3), AO4(func4);

    for(int i = 0; i < N; ++i) {
        int num = rand() % 1000000;
        AO1.getQueue()->enqueue(static_cast<void*>(&num));
        usleep(1000);
        AO2.getQueue()->enqueue(static_cast<void*>(&num));
        usleep(1000);
        AO3.getQueue()->enqueue(static_cast<void*>(&num));
        usleep(1000);
        AO4.getQueue()->enqueue(static_cast<void*>(&num));
        usleep(1000);
    }

    AO1.stop();
    AO2.stop();
    AO3.stop();
    AO4.stop();
    return 0;
}
