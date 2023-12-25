/***********************************************************************
 * File: hw1-2.cpp
 * Author: JiaHong-Wang
 * Create Date: 2023-10-02
 * Editor: JiaHong-Wang
 * Update Date: 2023-10-04
 * Description: build binary tree by inoder and preorder or postorder
 * ***********************************************************************/
#include<iostream>
#include<string>
#include<cctype>
using namespace std;

struct binaryTreeNode {
	char data;
	struct binaryTreeNode* leftNode = NULL;
	struct binaryTreeNode* rightNode = NULL;

};
struct Node {
	binaryTreeNode* node;
	struct Node* next;
};
class Queue {
public:
	Node* front;
	Node* rear;

	Queue() : front(nullptr), rear(nullptr) {}

	void enqueue(binaryTreeNode* node) {
		Node* newNode = new Node();
		newNode->node = node;

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
};



binaryTreeNode* toNewOrder(string inorder, string preorder, string type);
void postorderTraversal(binaryTreeNode* node);
void preorderTraversal(binaryTreeNode* node);
void levelorderTraversal(binaryTreeNode* node);

int main() {
	string inorder, type, order, outputType, newOrder;
	binaryTreeNode* root;
	cin >> inorder >> type >> order >> outputType;
	root = toNewOrder(inorder, order, type);
	if (outputType == "postfix")postorderTraversal(root);
	else if (outputType == "prefix") preorderTraversal(root);
	cout << endl;
	levelorderTraversal(root);

}

binaryTreeNode* toNewOrder(string inorder, string order, string type) {
	if (inorder.empty() || order.empty()) return nullptr;

	binaryTreeNode* newNode = new binaryTreeNode();
	if (type == "prefix") {
		char letter = order[0];

		newNode->data = letter;

		int index = inorder.find(letter);

		string leftInorder = inorder.substr(0, index);
		string rightInorder = inorder.substr(index + 1);

		int cutLength = leftInorder.length();

		string leftPreorder = order.substr(1, cutLength);
		string rightPreorder = order.substr(1 + cutLength);

		newNode->leftNode = toNewOrder(leftInorder, leftPreorder, type);
		newNode->rightNode = toNewOrder(rightInorder, rightPreorder, type);
	}

	else if (type == "postfix") {
		char letter = order[order.length() - 1];

		newNode->data = letter;

		int index = inorder.find(letter);

		string leftInorder = inorder.substr(0, index);
		string rightInorder = inorder.substr(index + 1);


		int cutLength = leftInorder.length();

		string leftPostorder = order.substr(0, cutLength);
		string rightPostorder = order.substr(cutLength, order.length() - 1 - cutLength);

		newNode->leftNode = toNewOrder(leftInorder, leftPostorder, type);
		newNode->rightNode = toNewOrder(rightInorder, rightPostorder, type);
	}

	return newNode;
}
void postorderTraversal(binaryTreeNode* node) {
	if (node == nullptr) {
		return;
	}

	postorderTraversal(node->leftNode);
	postorderTraversal(node->rightNode);
	cout << node->data;
}

void preorderTraversal(binaryTreeNode* node) {
	if (node == nullptr) {
		return;
	}

	cout << node->data;
	preorderTraversal(node->leftNode);
	preorderTraversal(node->rightNode);
}
void levelorderTraversal(binaryTreeNode* node) {
	Queue levelOrder;
	levelOrder.enqueue(node);
	while (levelOrder.front != nullptr) {
		cout << levelOrder.front->node->data;
		if (levelOrder.front->node->leftNode != nullptr) levelOrder.enqueue(levelOrder.front->node->leftNode);
		if (levelOrder.front->node->rightNode != nullptr) levelOrder.enqueue(levelOrder.front->node->rightNode);

		levelOrder.dequeue();
	}
}
