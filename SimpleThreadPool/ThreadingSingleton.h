#ifndef THREAD_SINGLETON_H
#define THREAD_SINGLETON_H

#include <iostream>
#include "ThreadPool.h"

class ThreadingSingleton
{
    static ThreadingSingleton* instance;
    ThreadPool tp;

    ThreadingSingleton() {}

public:
    static ThreadingSingleton* getInstance() {
        if (!instance)
            instance = new ThreadingSingleton();
        return instance;
    }

    ThreadPool& pool() { return this->tp; };
};

#endif