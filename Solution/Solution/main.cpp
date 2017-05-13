#include <stdio.h>
#include "Node.h"
#include "Dijkstra.h"

#define MAXVALUE 2147483646

using namespace std;

int main() {
	int nodesAmount, pathsAmount;
	scanf_s("%d%d", &nodesAmount, &pathsAmount);
	Node **nodesTable = new Node*[nodesAmount];
	Dijkstra dijkstra(nodesAmount, pathsAmount, nodesTable);

	for (int i = 0; i < nodesAmount; i++)
		nodesTable[i] = new Node();

	int firstNode, secondNode, length;
	for (int i = 0; i < pathsAmount; i++) {                                         //reading graph from input
		scanf_s("%d%d%d", &firstNode, &secondNode, &length);
		nodesTable[firstNode]->addNodeAndPath(nodesTable[secondNode], length);
		nodesTable[secondNode]->addNodeAndPath(nodesTable[firstNode], length);
	}
	int *tab = dijkstra.dijkstra();

	if (tab[0] == MAXVALUE || tab[1] == MAXVALUE)
		printf("#");
	else
		printf("%d %d", tab[0], tab[1]);

	delete[] tab;
	delete[] nodesTable;

	return 0;
}