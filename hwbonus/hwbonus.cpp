/***********************************************************************
 * File: test1.cpp
 * Author: JiaHong-Wang
 * Create Date: 2023-12-12
 * Editor: JiaHong-Wang
 * Update Date: 2023-12-15
 * Description:Shortest Path
 * ***********************************************************************/
#include<iostream>
#include<cstring>
#include<cctype>

#define INT_MAX 214748364

using namespace std;



struct Node {
	string name = "";
	int weight = INT_MAX;
	bool isSelect = false;
	Node* lastNode = nullptr;
};

struct Edge {
	Node* startNode = nullptr;
	Node* endNode = nullptr;
	int weight = 0;
	bool isSelect = false;
};
template <typename T>
struct QueueNode {
	T* data;
	QueueNode* next;

	QueueNode(T* data) : data(data), next(nullptr) {}
};

template <typename T>
class Queue {
public:
	QueueNode<T>* front;
	QueueNode<T>* rear;
	Queue() : front(nullptr), rear(nullptr) {}

	void enqueue(T* data) {
		QueueNode<T>* newNode = new QueueNode<T>(data);

		if (rear == nullptr) {
			front = rear = newNode;
			return;
		}

		rear->next = newNode;
		rear = newNode;
	}

	void dequeue() {
		if (front == nullptr) return;

		QueueNode<T>* temp = front;
		front = front->next;

		if (front == nullptr) {
			rear = nullptr;
		}

		delete temp;
	}
	bool find(T* data) {
		QueueNode<T>* tmp = front;
		while (tmp != nullptr) {
			if (tmp->data == data) return true;
			tmp = tmp->next;
		}
		return false;
	}

	bool isEmpty() const {
		return front == nullptr;
	}

	bool deleteNode(T* target) {
		if (front == nullptr) {
			return false;
		}

		QueueNode<T>* temp = front;
		QueueNode<T>* prev = nullptr;

		if (temp != nullptr && temp->data == target) {
			front = temp->next;
			delete temp;
			if (front == nullptr) {
				rear = nullptr;
			}
			return true;
		}

		while (temp != nullptr && temp->data != target) {
			prev = temp;
			temp = temp->next;
		}

		if (temp == nullptr) return false;

		prev->next = temp->next;
		delete temp;

		if (prev->next == nullptr) {
			rear = prev;
		}

		return true;
	}
	~Queue() {
		while (!isEmpty()) {
			dequeue();
		}
	}
};


Edge* edges, tmpEdge;
Node* nodes, * startNode, * tmpNodes, tmpNode;
bool* isSelect;
string startNodeName;
int nodeNumber, edgeNumber;

Node* findNode(string nodeName);
bool BellmanFord();
bool checkNegativeCycle();
bool Dijkstra();

int main() {
	string start, endName, tmp;
	int weight, mininumber;
	bool valid;
	cin >> nodeNumber >> edgeNumber >> startNodeName;

	edges = new Edge[edgeNumber];
	nodes = new Node[nodeNumber];
	isSelect = new bool[nodeNumber];

	for (int i = 0; i < edgeNumber; i++) {
		cin >> start >> endName >> weight;
		edges[i].startNode = findNode(start);
		edges[i].endNode = findNode(endName);
		edges[i].weight = weight;
	}



	startNode = findNode(startNodeName);

	valid = BellmanFord();

	tmpNodes = new Node[nodeNumber];
	for (int i = 0; i < nodeNumber; i++) {
		tmpNodes[i].name = nodes[i].name;
		tmpNodes[i].weight = nodes[i].weight;
	}
	for (int i = 0; i < nodeNumber - 1; i++) {
		for (int j = 0; j < nodeNumber - 1 - i; j++) {
			if (strcmp(tmpNodes[j].name.c_str(), tmpNodes[j + 1].name.c_str()) > 0) {
				tmpNode = tmpNodes[j];
				tmpNodes[j] = tmpNodes[j + 1];
				tmpNodes[j + 1] = tmpNode;
			}
		}
	}

	if (valid) {
		for (int i = 0; i < nodeNumber; i++) {
			if (tmpNodes[i].weight != INT_MAX)cout << tmpNodes[i].weight;
			else cout << "-";
			cout << " ";
		}
		cout << endl;
	}
	else cout << "invalid input" << endl;

	delete[] tmpNodes;

	//reset
	for (int i = 0; i < nodeNumber; i++) nodes[i].weight = INT_MAX;

	valid = Dijkstra();

	for (int i = 0; i < nodeNumber; i++)isSelect[i] = false;

	if (valid) {
		for (int i = 0; i < nodeNumber; i++) {
			for (int j = 0; j < nodeNumber; j++) {
				if (!isSelect[j]) {
					mininumber = j;
					tmpNode = nodes[j];
					break;
				}
			}

			for (int j = 0; j < nodeNumber; j++) {
				if (!isSelect[j] && strcmp(tmpNode.name.c_str(), nodes[j].name.c_str()) > 0) {
					mininumber = j;
					tmpNode = nodes[j];
				}
			}
			isSelect[mininumber] = true;
			if (nodes[mininumber].weight != INT_MAX) {
				Node* currentNode = &nodes[mininumber];
				Queue<Node> nodeQueue;
				while (currentNode != nullptr) {
					nodeQueue.enqueue(currentNode);
					currentNode = currentNode->lastNode;
				}
				while (!nodeQueue.isEmpty()) {
					Node* queueNode = nodeQueue.rear->data;
					nodeQueue.deleteNode(queueNode);
					if (!nodeQueue.isEmpty())cout << queueNode->name << " -> ";
					else cout << queueNode->name << " = " << queueNode->weight;
				}

			}
			else cout << "No path to " << nodes[i].name;

			cout << endl;
		}
	}
	else cout << "invalid input" << endl;
}

Node* findNode(string nodeName) {
	static int count = 0;
	for (int i = 0; i < count; i++) {
		if (nodes[i].name == nodeName) return &nodes[i];
	}
	nodes[count].name = nodeName;
	nodes[count].weight = INT_MAX;
	count++;
	return &nodes[count - 1];
}

bool BellmanFord() {
	if (!checkNegativeCycle()) return false;


	bool isChange = true;
	startNode->weight = 0;
	startNode->isSelect = true;
	while (isChange) {
		isChange = false;
		for (int i = 0; i < edgeNumber; i++) {
			if (edges[i].startNode->isSelect) {
				if (edges[i].startNode->weight + edges[i].weight < edges[i].endNode->weight) {
					isChange = true;
					edges[i].endNode->weight = edges[i].startNode->weight + edges[i].weight;
					edges[i].endNode->isSelect = true;
					cout << edges[i].endNode->name << " " << edges[i].endNode->weight << endl;
				}
			}
		}


	}
	return true;
}

bool checkNegativeCycle() {
	for (int i = 0; i < nodeNumber; i++) nodes[i].weight = 0;

	for (int i = 0; i < edgeNumber - 1; i++) {
		for (int j = 0; j < edgeNumber; j++) {
			if (edges[j].startNode->weight + edges[j].weight < edges[j].endNode->weight) {
				edges[j].endNode->weight = edges[j].startNode->weight + edges[j].weight;
			}
		}
	}

	for (int j = 0; j < edgeNumber; j++) {
		if (edges[j].startNode->weight + edges[j].weight < edges[j].endNode->weight) {
			return false;
		}
	}
	for (int i = 0; i < nodeNumber; i++) nodes[i].weight = INT_MAX;
	return true;
}

bool Dijkstra() {
	for (int i = 0; i < edgeNumber; i++) {
		if (edges[i].weight < 0)
			return false;
	}

	bool isChange = true;
	Queue<Node> nodeQueue;
	Node* minNode = nullptr;

	for (int i = 0; i < nodeNumber; i++) edges[i].isSelect = false;

	nodeQueue.enqueue(startNode);
	startNode->weight = 0;
	startNode->isSelect = true;
	while (1) {

		Queue<Edge> edgeQueue;
		QueueNode<Node>* tmp = nodeQueue.front;

		while (tmp != nullptr) {
			for (int i = 0; i < edgeNumber; i++) {
				if (tmp->data == edges[i].startNode) edgeQueue.enqueue(&edges[i]);
			}
			tmp = tmp->next;
		}
		while (!edgeQueue.isEmpty()) {
			QueueNode<Edge>* tmp = edgeQueue.front;
			Edge* currentEdge = tmp->data;
			edgeQueue.dequeue();
			if (currentEdge->startNode->weight + currentEdge->weight < currentEdge->endNode->weight) {
				currentEdge->endNode->weight = currentEdge->startNode->weight + currentEdge->weight;
				currentEdge->endNode->lastNode = currentEdge->startNode;
				currentEdge->endNode->isSelect = true;
			}
		}
		for (int i = 0; i < nodeNumber; i++)
			if (!nodeQueue.find(&nodes[i]) && nodes[i].isSelect) {
				minNode = &nodes[i];
				break;
			}

		if (minNode == nullptr) break;

		for (int i = 0; i < nodeNumber - 1; i++) {
			if (!nodeQueue.find(&nodes[i]) && nodes[i].weight < minNode->weight && nodes[i].isSelect) {
				minNode = &nodes[i];
			}
		}

		nodeQueue.enqueue(minNode);

		minNode = nullptr;
	}
	return true;
}
