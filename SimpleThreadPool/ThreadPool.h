#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <iostream>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>

class ThreadPool {
public:
	ThreadPool();
	~ThreadPool();
	void addTask(std::function<void()>);
	static void checkTasks();
private:
	std::vector<std::thread> m_threads;
	static std::queue<std::function<void()>> m_tasks;
	static std::mutex mtx;
};
#endif // !THREAD_POOL_H

