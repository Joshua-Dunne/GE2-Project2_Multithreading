#include <ThreadPool.h>

using namespace std::chrono_literals;

std::queue<std::function<void()>> ThreadPool::m_tasks;
std::mutex ThreadPool::mtx;

static bool s_running = true;

ThreadPool::ThreadPool() {}

ThreadPool::~ThreadPool() {}

void ThreadPool::initializeThreads()
{
	int cores = std::thread::hardware_concurrency() - 1;

	for (int i = 0; i < cores; i++)
	{
		m_threads.push_back(std::thread(checkTasks));
	}
}

void ThreadPool::addTask(std::function<void()> task)
{
	m_tasks.push(task);
}

void ThreadPool::checkTasks()
{
	while (s_running)
	{

		while (m_tasks.size() == 0) { std::this_thread::sleep_for(0.5s);  continue; };

		mtx.lock(); // lock down to allow only one thread to potentially be assigned a task

		if (m_tasks.size() == 0)
		{
			mtx.unlock();
			continue; // if no tasks are found, go back up to the spin and wait for more
		}

		std::cout << "Thread taking task..." << std::endl;

		auto task = m_tasks.front();

		m_tasks.pop();

		mtx.unlock(); // now that a single thread has been assigned a task, allow other threads to acquire a task

		task();

		std::cout << "Thread completed task." << std::endl;
	}
	
}
