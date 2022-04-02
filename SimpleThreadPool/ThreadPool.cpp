#include <ThreadPool.h>

using namespace std::chrono_literals;

std::queue<std::function<void()>> ThreadPool::m_tasks;
std::mutex ThreadPool::mtx;

static bool s_running = true;
static unsigned int s_queued = 0;

ThreadPool::ThreadPool() {}

ThreadPool::~ThreadPool() 
{
	s_running = false;

	for (std::thread& thread : m_threads)
	{
		thread.join();
	}

	m_threads.clear();
}

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
	std::cout << "Thread " << s_queued << " checking in." << std::endl;
	s_queued++;
	// wait for all threads to arrive
	while (s_queued < std::thread::hardware_concurrency() - 1) continue;

	std::cout << "All threads ready" << std::endl;

	while (s_running)
	{
		while (m_tasks.size() == 0 && s_running) { std::this_thread::sleep_for(0.5s);  continue; };

		if (!s_running) break; // if we are finished running, break out here, don't attempt to run any more tasks

		mtx.lock(); // lock down to allow only one thread to potentially be assigned a task

		s_queued--; // since this thread got through the mutex lock, decrement the queued counter.

		if (m_tasks.size() == 0)
		{
			mtx.unlock();
			s_queued++;
			continue; // if no tasks are found, go back up to the spin and wait for more
		}

		std::cout << "Thread taking task..." << std::endl;

		auto task = m_tasks.front();

		m_tasks.pop();

		mtx.unlock(); // now that a single thread has been assigned a task, allow other threads to acquire a task

		task();

		std::cout << "Thread completed task." << std::endl;

		s_queued++;
	}
}

void ThreadPool::clearThreads()
{
	// if all the threads are queued waiting, threads exist, and all tasks are complete, we can clean up our threads
	if (s_queued == std::thread::hardware_concurrency() - 1 && m_threads.size() > 0 && m_tasks.size() == 0)
	{
		s_running = false;
	}
	else
		return;

	for (std::thread& thread : m_threads)
	{
		thread.join();
	}

	s_queued = 0;

	m_threads.clear();
}
