#include "Node.h"

#define MAXVALUE 2147483646

#pragma once

class Dijkstra {
public:
	Dijkstra(int nodesAmount, int pathsAmount, Node **nodesTable) {
		this->nodesAmount = nodesAmount;
		this->pathsAmount = pathsAmount;
		this->nodesTable = nodesTable;

		shortestWay = new int[nodesAmount];
		perseviousTab = new int[nodesAmount];
		stance = new int[nodesAmount];
	}

	~Dijkstra() {
		delete[] shortestWay;
		delete[] perseviousTab;
		delete[] stance;
	};

	int * dijkstra() {
		for (int i = 0; i < nodesAmount; i++) {
			shortestWay[i] = MAXVALUE;
			perseviousTab[i] = -1;
			stance[i] = 0;
		}
		shortestWay[0] = 0;

		int min = MAXVALUE, i = 0, j = 0;

		Node *firstNode, *neighbour;
		int firstIndex;
		int *indexAndLength;

		int iterator;
		for (int i = 0; i < nodesAmount; i++) {
			for (iterator = 0; stance[iterator] == 1; iterator++);
			for (firstIndex = iterator++; iterator < nodesAmount; iterator++) {
				if (stance[iterator] == 0 && (shortestWay[iterator] < shortestWay[firstIndex]))
					firstIndex = iterator;
			}

			stance[firstIndex] = 1;
			firstNode = nodesTable[firstIndex];
			for (int i = 0; i < firstNode->connectedNodes; i++) {
				indexAndLength = firstNode->listOfNodes->findAndReturnIndexAndLength(i);
				if (stance[indexAndLength[0]] == 0) {
					if (shortestWay[indexAndLength[0]] >(shortestWay[firstIndex] + indexAndLength[1])) {
						shortestWay[indexAndLength[0]] = shortestWay[firstIndex] + indexAndLength[1];
						perseviousTab[indexAndLength[0]] = firstIndex;
					}
				}
			}
		}

		int *results = new int[2];
		results[0] = shortestWay[nodesAmount - 1];

		min = MAXVALUE;
		int distanceToTheEnd = 0, newLength;
		firstNode = nodesTable[nodesAmount - 1];

		while (firstNode != nodesTable[0]) {
			for (int i = 0; i < firstNode->connectedNodes; i++) {
				indexAndLength = firstNode->listOfNodes->findAndReturnIndexAndLength(i);
				firstIndex = firstNode->index;
				if (indexAndLength[0] != perseviousTab[firstIndex]) {
					newLength = shortestWay[indexAndLength[0]] + indexAndLength[1] + distanceToTheEnd;
					if (newLength < min && goesThroughThisNode(firstIndex, indexAndLength[0]) == false)
						min = newLength;
				}
				else {
					newLength = firstNode->listOfNodes->findAndReturnSecondLength(perseviousTab[firstIndex]);
					if (newLength != -1) {
						newLength += shortestWay[perseviousTab[firstIndex]] + distanceToTheEnd;
						if (newLength < min)
							min = newLength;
					}
				}
			}

			distanceToTheEnd += shortestWay[firstIndex] - shortestWay[perseviousTab[firstIndex]];
			firstNode = nodesTable[perseviousTab[firstIndex]];
		}

		results[1] = min;

		return results;

	}

	bool goesThroughThisNode(int throughThis, int fromThis) {
		int temp = fromThis;
		do {
			temp = perseviousTab[temp];
			if (temp == throughThis)
				return true;
		} while (temp != 0);

		return false;
	}

	int nodesAmount, pathsAmount;
	int *shortestWay, *perseviousTab, *stance;
	Node **nodesTable, **visitedNodes;
};