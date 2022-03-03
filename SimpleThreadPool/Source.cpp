#include <ThreadPool.h>

int main() {

	ThreadPool tp;

	auto path = []() {
		  
		for (int a = 0; a < 50; a++)
		{
			std::cout << "pathing to " << a << std::endl;
		}
	};

	tp.addTask(path);
}