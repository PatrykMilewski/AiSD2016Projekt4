#pragma once

class Node {
public:
	class NodesList {
	private:

		class Link {
		public:
			Link(Node *thisNode, int length) {
				this->thisNode = thisNode;
				this->nextLink = nextLink;
				list[0] = length;
				list[1] = -1;
			}

			~Link() {};

			void addToList(int length) {
				if (list[0] > length) {
					list[1] = list[0];
					list[0] = length;
				}
				else if (list[1] == -1 || list[1] > length)
					list[1] = length;
			}

			Node *thisNode;
			Link *nextLink;
			int list[2];
		};
	public:

		NodesList() {
			head = nullptr;
			tail = nullptr;
			indexAndLength = new int[2];
			amount = 0;
		}

		~NodesList() {
			if (amount > 0)
				tempLink = head->nextLink;
			for (int i = 0; i < amount; i++) {
				secondTempLink = tempLink->nextLink;
				delete tempLink;
				tempLink = secondTempLink;
			}
		}

		bool addToList(Node *inputNode, int length) {
			if (amount == 0) {
				head = new Link(inputNode, length);
				tail = head;
			}
			else {
				if (findAndAdd(inputNode->index, length))
					return false;

				tail->nextLink = new Link(inputNode, length);
				tail = tail->nextLink;
			}

			amount++;
			return true;
		}

		bool findAndAdd(int index, int length) {
			tempLink = head;
			for (int i = 0; i < amount; i++) {
				if (tempLink->thisNode->index == index) {
					tempLink->addToList(length);
					return true;
				}
				tempLink = tempLink->nextLink;
			}

			return false;
		}

		int findAndReturnLength(int index) {
			tempLink = head;
			for (int i = 0; i < amount; i++) {
				if (tempLink->thisNode->index == index)
					return tempLink->list[0];

				tempLink = tempLink->nextLink;
			}

			return -1;
		}

		int findAndReturnSecondLength(int index) {
			tempLink = head;
			for (int i = 0; i < amount; i++) {
				if (tempLink->thisNode->index == index)
					return tempLink->list[1];

				tempLink = tempLink->nextLink;
			}

			return -1;
		}

		Node * findAndReturnNode(int index) {
			if (index == (amount - 1))
				return tail->thisNode;

			tempLink = head;
			for (int i = 0; i < amount; i++) {
				if (i == index)
					return tempLink->thisNode;

				tempLink = tempLink->nextLink;
			}

			return nullptr;
		}

		int findAndReturnIndex(int index) {
			if (index == (amount - 1))
				return tail->thisNode->index;

			tempLink = head;
			for (int i = 0; i < amount; i++) {
				if (i == index)
					return tempLink->thisNode->index;

				tempLink = tempLink->nextLink;
			}

			return -1;
		}

		int * findAndReturnIndexAndLength(int index) {

			if (index == (amount - 1)) {
				indexAndLength[0] = tail->thisNode->index;
				indexAndLength[1] = tail->list[0];
				return indexAndLength;
			}

			tempLink = head;
			for (int i = 0; i < amount; i++) {
				if (i == index) {
					indexAndLength[0] = tempLink->thisNode->index;
					indexAndLength[1] = tempLink->list[0];
					return indexAndLength;
				}

				tempLink = tempLink->nextLink;
			}

			return nullptr;
		}

		Link *head, *tail, *tempLink, *secondTempLink;
		int amount, *indexAndLength;
	};

	Node() {
		index = nodesCounter;
		nodesCounter++;
		connectedNodes = 0;
		wasVisited = false;
		listOfNodes = new NodesList();
	}

	~Node() {
		delete listOfNodes;
	}

	void addNodeAndPath(Node *inputNode, int inputPath) {
		if (listOfNodes->addToList(inputNode, inputPath))
			connectedNodes++;
	}

	NodesList *listOfNodes;
	static int nodesCounter;
	int connectedNodes;
	bool wasVisited;
	unsigned int index;
};

int Node::nodesCounter = 0;