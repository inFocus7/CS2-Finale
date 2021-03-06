#include "binaryST.h"
#include "graph.h"
#include <iostream>
#include <sstream>
#include <string>
//#include <vector>
//#include <queue>
#include <fstream>

bool singular(std::string line)
{
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == ' ')
		{
			return false;
		}
	}
	return true;
}

int main()
{
	digraph network;
	std::string infectedComputer;
	std::ifstream connection;
	connection.open("connections.txt");

	/* KEY IDEA
	first line = |Computers|
	2nd to (last - 1) = network connections
	last = infected computer
	KEY IDEA */

	//First Line
	std::string line;
	std::getline(connection, line);
	std::stringstream ss(line);
	int amtOfComputers{ 0 };
	ss >> amtOfComputers;
	//Next Lines
	for (line; std::getline(connection, line); )
	{
		if (singular(line)) // Last Line
		{
			infectedComputer = line;
			break;
		}

		std::stringstream ss(line);
		std::string computer, main;

		for (int count = 0; ss >> computer; count++)
		{
			if (count == 0)
			{
				main = computer; // first string is connected into
				if (network.findVertex(computer) == nullptr) //if computer hasn't been registered into network add it
				{
					network.addVertex(computer);
				}
			}
			else
			{
				if (network.findVertex(computer) == nullptr)
				{
					network.addVertex(computer);
				}
				network.addEdge(computer, main);
			}
		}
	}

	network.displayInfected(infectedComputer);

    return 0;
}

