#include "mazeGraph.h"
#include "binaryST.h"
#include "priorityQueue.h"
//#include <iostream>
#include <fstream>
//#include <queue>
//#include <vector>

// Globals
int maxRowIndex, maxColumnIndex;

// Start
int main()
{
	mazeGraph maze;
	std::ifstream mazeOne;
	mazeOne.open("maze4.txt");
	std::string line;
	int startX{ 0 }, startY{ 0 }, endX{ 0 }, endY{ 0 }; // Uninitialize if there's problems. New addition.

	std::cout << "ORIGINAL: \n";
	// Maze2Vertex
	for (int rowCount = 0; std::getline(mazeOne, line); rowCount++)
	{
		for (int colCount = 0; colCount < line.size(); colCount++)
		{
			//Make vertex per char and make "position" based on x and y
			//if vertex/edge not made

			maze.addVertex(line[colCount], rowCount, colCount);

			if (line[colCount] == 's')
			{
				startX = rowCount;
				startY = colCount;
			}
			else if (line[colCount] == 'e') //made this an elseif since it could speed it up by a small constant when linecount == 's'...
			{
				endX = rowCount;
				endY = colCount;
			}
			
			std::cout << line[colCount];
			maxColumnIndex = colCount;
		}
		std::cout << '\n';
		maxRowIndex = rowCount;
	}

	std::cout << '\n';

	//Edge Connectors
	for (int i = 0; i <= maxRowIndex; i++) //Need to find more efficient solution if there is one, but so far speeds are good
	{
		for (int j = 0; j <= maxColumnIndex; j++)
		{
			//connect with right if not @ end.
			if (j != maxColumnIndex)
			{
				maze.addEdge(i, j, i, j+1);
			}
			//connect with bottom if not @ bottom.
			if (i != maxRowIndex)
			{
				maze.addEdge(i, j, i + 1, j);
			}
		}
	}

	std::cout << "SOLVED: \n";
	maze.shortestPath(startX, startY, endX, endY);

    return 0;
}

