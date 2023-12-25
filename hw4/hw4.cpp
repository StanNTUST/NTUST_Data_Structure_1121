/***********************************************************************
 * File: test1.cpp
 * Author: JiaHong-Wang
 * Create Date: 2023-12-12
 * Editor: JiaHong-Wang
 * Update Date: 2023-12-12
 * Description: find minimum spanning tree
 * ***********************************************************************/
#include<iostream>
#include<string>
#include<cctype>

using namespace std;

struct Node {
	int data;
	struct Node* next = nullptr;
};
class Queue {
public:
	Node* front;
	Node* rear;

	Queue() : front(nullptr), rear(nullptr) {}

	void enqueue(int data) {
		Node* newNode = new Node();
		newNode->data = data;

		if (front == nullptr) {
			front = rear = newNode;
		}
		else {
			rear->next = newNode;
			rear = newNode;
		}
	}
	void dequeue() {
		if (front == nullptr) return;

		Node* temp = front;
		front = front->next;
		delete temp;
	}
	bool isEmpty() {
		return(front == nullptr);
	}
};

int findHeight(int root);

bool* isSelect;
int number, ** table;
int* heights;

int main() {
	int i = 0, number1, number2, minimum;
	string text;
	getline(cin, text);
	number = stoi(text.substr(0, text.find(" ")));
	text = text.substr(text.find(" ") + 1, text.length());
	isSelect = new bool[number];
	table = new int* [number];
	heights = new int[number];
	for (int i = 0; i < number; i++) {
		isSelect[i] = false;
		table[i] = new int[number];
		for (int j = 0; j < number; j++) {
			table[i][j] = 0;
		}
	}

	for (int i = 0; i < number - 1; i++) {
		number1 = stoi(text.substr(0, text.find(" ")));
		text = text.substr(text.find(" ") + 1, text.length());
		number2 = stoi(text.substr(0, text.find(" ")));
		text = text.substr(text.find(" ") + 1, text.length());
		table[number1][number2] = 1;
		table[number2][number1] = 1;
	}

	for (int i = 0; i < number; i++) {
		heights[i] = findHeight(i);

		for (int j = 0; j < number; j++) {
			isSelect[j] = false;
		}
	}

	minimum = number;
	for (int i = 0; i < number; i++) {
		minimum = min(minimum, heights[i]);
	}
	for (int i = 0; i < number; i++) {
		if (heights[i] == minimum) {
			cout << i<<" ";
		}
	}
	return 0;
}

int findHeight(int root) {
	int height, count = 1, currentData, bigNumber = 0;
	isSelect[root] = true;
	Queue queue;
	Node* nodes = new Node[number];
	for (int i = 0; i < number; i++) {
		nodes[i].data = i;
	}

	queue.enqueue(root);

	while (count != number && !queue.isEmpty()) {
		currentData = queue.front->data;
		queue.dequeue();
		for (int i = 0; i < number; i++) {
			if (!isSelect[i] && table[currentData][i] == 1) {
				queue.enqueue(i);
				isSelect[i] = true;
				count++;
				nodes[i].next = &nodes[currentData];
			}
		}
	}
	for (int i = 0; i < number; i++) {
		Node* currentNode = &nodes[i];
		height = 0;
		while (currentNode->next != nullptr) {
			height++;
			currentNode = currentNode->next;
		}

		bigNumber = max(bigNumber, height);
	}

	delete[] nodes;
	return bigNumber;
}
