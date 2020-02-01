#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <sstream>
#include <tchar.h>

#include "Input.h";
#include "Physics.h";
#include "Player.h";
#include "Render.h"

const int t = 4;

std::atomic_int ticketNumber;
std::atomic_int nextTicket;
std::atomic_int ticketTurn[t];
int numThreads;
std::mutex coutMutex;

int playerPosX = 0;
int playerPosY = 0;

Input input;
Physics physics;
Player player;
Render render;

void Ticket()
{
	int i = numThreads++;

	//Use Mutex for outputs so the threads dont overlap each other on console
	coutMutex.lock();
	std::cout << "Thread number " << i << "." << std::endl;
    coutMutex.unlock();

	while (true)
	{
		//take ticket
		ticketTurn[i] = ticketNumber.fetch_add(1);

		//slow program to read console
		std::this_thread::sleep_for(std::chrono::seconds(1));

		//if its not your turn wait
		while (ticketTurn[i] != nextTicket)
		{
			continue;
		}

		coutMutex.lock();
		std::cout << "Thread Number " << i << ". \t Ticket number : " << ticketTurn[i] << std::endl;
		std::cout << std::endl;
		coutMutex.unlock();

		//Calls the updates of the systems
		switch (i)
		{
		case 0:
			input.update(playerPosX);
			break;
		case 1:
			physics.update(playerPosY);
			break;
		case 2:
			player.update(playerPosX);
			break;
		case 3:
			render.update(playerPosY);
			break;
		default:
			break;
		}

		//log the players position
		coutMutex.lock();
		std::cout << "Player x :" << playerPosX << "\tPlayer y : " << playerPosY << std::endl;
		coutMutex.unlock();

		nextTicket++;

		//log the next ticket number and create a line break for easier visibility
		coutMutex.lock();
		std::cout << "Next ticket number is = " << nextTicket << std::endl;
		std::cout << "---------------------------------------------------------------------- " << std::endl;
		coutMutex.unlock();
	}
}

int _tmain(int argc, TCHAR* argv[])
{
	srand(time(NULL));
	
	numThreads = 0;
	ticketNumber = 1;
	nextTicket = 1;

	/*for (int i = 0; i < t; i++)
	{
		ticketTurn[i] = 0;
	}*/

	std::thread t1 = std::thread(Ticket);
	std::thread t2 = std::thread(Ticket);
	std::thread t3 = std::thread(Ticket);
	std::thread t4 = std::thread(Ticket);

	t1.join();
	t2.join();
	t3.join();
	t4.join();


	return 0;
}