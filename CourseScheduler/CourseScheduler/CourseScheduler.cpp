#include "graph.h"
#include "binaryST.h"
#include <iostream>
#include <string>
//#include <vector>
//#include <queue>
#include <fstream>
#include <sstream>

int main()
{
	/* STEPS TO TAKE
	1) Read in file.
	2) Create directed graph
	3) Per line...
	-> 3.1) Tokenize word
	-> 3.2) First word: Create a vertex (iff not inside graph already)
	-> 3.3) 2+ word: Create vertex
	-> 3.4) Add diredges from 2+ to first
	STEPS TO TAKE */

	digraph scheduler;
	std::ifstream schedule;
	schedule.open("schedule.txt");
	
	// Scheduler
	for (std::string line; std::getline(schedule, line); ) //line by line
	{
		//unsigned int count{ 0 };
		std::stringstream ss(line);
		std::string course, main;
		
		for (int count = 0; ss >> course; count++)
		{
			//Input course
			if (count == 0)
			{
				main = course;
				if (scheduler.findVertex(course) == nullptr)
				{
					scheduler.addVertex(course); //Add first, main
				}
			}
			else
			{
				if (scheduler.findVertex(course) == nullptr)
				{
					scheduler.addVertex(course); //Add first, main
				}
				scheduler.addDirectedEdge(course, main);
			}
		}

	}

		// Display
	scheduler.displaySchedule();

    return 0;
}

