#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

/*#include <ThreadingSingleton.h>
#include <string>

using namespace std::literals::chrono_literals;

ThreadingSingleton* ThreadingSingleton::instance = 0;

std::function<void()> generateTask(std::string t_output)
{
	auto temp = [=]() {
		for (int i = 0; i < 10; i++)
		{
			std::cout << t_output << std::endl;

			std::this_thread::sleep_for(0.5s);
		}
	};

	return temp;
}

int main() {

	ThreadingSingleton* s = s->getInstance();

	// for demonstration, add multiple of the same function

	for (int i = 0; i < 100; i++)
	{
		s->pool().addTask(generateTask("path task " + std::to_string(i)));
	}
	
	system("pause");

}*/



#include <ThreadingSingleton.h>
#include <iostream>
#include "Game.h"

ThreadingSingleton* ThreadingSingleton::instance = 0;

int main()
{
	try
	{
		Game game;
		game.run();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (std::string& e)
	{
		std::cout << e << std::endl;
	}
	catch (...)
	{
		std::cout << "An uncaught error occured!" << std::endl;
	}

	return 0;
}//*/