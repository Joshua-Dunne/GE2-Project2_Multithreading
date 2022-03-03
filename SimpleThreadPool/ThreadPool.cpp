#include <ThreadPool.h>

std::queue<std::function<void()>> ThreadPool::m_tasks;

ThreadPool::ThreadPool() {
	
	int cores = std::thread::hardware_concurrency() - 1;
	
	for (int i = 0; i < cores; i++)
	{
		m_threads.push_back(std::thread(checkTasks));
		// Need to add a function thats listens for 
		// Tasks to be added to the queue

		m_threads[i].detach();
	}

}

ThreadPool::~ThreadPool() {}


void ThreadPool::addTask(std::function<void()> task) 
{
	m_tasks.push(task);
}

void ThreadPool::checkTasks()
{
	while (m_tasks.size() == 0) continue; // spin time

	auto task = m_tasks.front();
	
	m_tasks.pop(); // technically mutex

	task();

	m_tasks.push(task);
}
