#include <ThreadPool.h>

using namespace std::literals::chrono_literals;

int main() {

	ThreadPool tp;

	auto path = []() {
		for(int i = 0; i < 10; i++)
		{
			std::cout << "pathing 1 :)" << std::endl;

			std::this_thread::sleep_for(1s);
		}
	};

	auto pathtwo = []() {
		for (int i = 0; i < 10; i++)
		{
			std::cout << "pathing 2 :)" << std::endl;

			std::this_thread::sleep_for(1s);
		}
	};

	auto paththree = []() {
		for (int i = 0; i < 10; i++)
		{
			std::cout << "pathing 3 :)" << std::endl;

			std::this_thread::sleep_for(1s);
		}
	};

	// for demonstration, add the same function 3 times
	tp.addTask(path);
	tp.addTask(pathtwo);
	tp.addTask(paththree);

	system("pause");
}