/***********************************************************************
 * File: hw1-1.cpp
 * Author: ¤ý®a§»
 * Create Date: 2023-10-30
 * Editor: ¤ý®a§»
 * Update Date: 2023-11-04
 * Description: build red-black tree and set the
 * ***********************************************************************/
#include<iostream>
#include<string>

struct Node {
	struct Node* leftNode;
	struct Node* rightNode;
	struct Node* parentNode;
	bool isRed = true;
	int data;
};

void insert(Node* newNode);
void changeColor(Node* node);
void rotate(Node* node);
void postBlack(Node* node);
void preRed(Node* node);

Node* root = nullptr;
int rotateCount = 0;

using namespace std;

int main() {
	string text, tmpText;
	Node* newNode;
	bool isInteger;
	int j = 1;
	getline(cin, text);
	while (text != "\0") {
		tmpText = text.substr(0, text.find(" "));
		isInteger = true;
		for (int i = 0; i < tmpText.size(); i++)
			if (!isdigit(tmpText[i])) {
				isInteger = false;
				break;
			}

		if (root != nullptr) {
			newNode = new Node();
			if (isInteger)newNode->data = stoi(tmpText);
			else newNode->data = tmpText[0];
			insert(newNode);

			if (root->isRed) root->isRed = false;
		}
		else {
			root = new Node();
			root->isRed = false;
			if (isInteger)root->data = stoi(tmpText);
			else root->data = tmpText[0];
		}
		if (text.find(" ") >= text.length()) break;
		text = text.substr(text.find(" ") + 1, text.length());
	}
	postBlack(root);
	cout << "_";
	preRed(root);
	cout << "_" << rotateCount;
}

void insert(Node* newNode) {

	Node* currentNode = root, * lastNode = nullptr;
	while (currentNode != nullptr) {
		changeColor(currentNode);
		if (newNode->data >= currentNode->data) {
			lastNode = currentNode;
			currentNode = currentNode->rightNode;
		}
		else {
			lastNode = currentNode;
			currentNode = currentNode->leftNode;
		}
	}

	if (newNode->data >= lastNode->data) {
		lastNode->rightNode = newNode;
		newNode->parentNode = lastNode;
	}
	else {
		lastNode->leftNode = newNode;
		newNode->parentNode = lastNode;
	}

	if (lastNode->isRed) rotate(newNode);


}
void changeColor(Node* node) {
	if (node->leftNode != nullptr && node->rightNode != nullptr) {
		if (node->leftNode->isRed && node->rightNode->isRed) {
			node->isRed = true;
			node->leftNode->isRed = false;
			node->rightNode->isRed = false;
			if (node->parentNode != nullptr && node->parentNode->isRed == true && node->parentNode != root) {
				rotate(node);
			}
		}
	}
}
void rotate(Node* childNode) {
	Node* parentNode = childNode->parentNode;
	Node* grandparentNode = parentNode->parentNode;
	Node* tmpNode, * tmpNode2;

	//L
	if (grandparentNode->leftNode != nullptr && grandparentNode->leftNode == parentNode) {
		//LL
		if (parentNode->leftNode != nullptr && parentNode->leftNode == childNode) {
			tmpNode = parentNode->rightNode;
			parentNode->parentNode = grandparentNode->parentNode;
			parentNode->rightNode = grandparentNode;
			parentNode->isRed = false;
			grandparentNode->leftNode = tmpNode;
			grandparentNode->parentNode = parentNode;
			grandparentNode->isRed = true;

			if (tmpNode != nullptr)tmpNode->parentNode = grandparentNode;

			if (parentNode->parentNode == nullptr) root = parentNode;
			else if (parentNode->parentNode->leftNode == grandparentNode)parentNode->parentNode->leftNode = parentNode;
			else parentNode->parentNode->rightNode = parentNode;
			rotateCount++;
		}
		//LR
		else if (parentNode->rightNode != nullptr && parentNode->rightNode == childNode) {
			tmpNode = childNode->leftNode;
			tmpNode2 = childNode->rightNode;
			childNode->parentNode = grandparentNode->parentNode;
			childNode->leftNode = parentNode;
			childNode->rightNode = grandparentNode;
			childNode->isRed = false;
			parentNode->parentNode = childNode;
			parentNode->rightNode = tmpNode;
			grandparentNode->parentNode = childNode;
			grandparentNode->leftNode = tmpNode2;
			grandparentNode->isRed = true;

			if (tmpNode != nullptr)tmpNode->parentNode = parentNode;
			if (tmpNode2 != nullptr)tmpNode2->parentNode = grandparentNode;

			if (childNode->parentNode == nullptr) root = childNode;
			else if (childNode->parentNode->leftNode == grandparentNode)childNode->parentNode->leftNode = childNode;
			else childNode->parentNode->rightNode = childNode;
			rotateCount++;


		}
	}
	//R
	else if (grandparentNode->rightNode != nullptr && grandparentNode->rightNode == parentNode) {
		//RL
		if (parentNode->leftNode != nullptr && parentNode->leftNode == childNode) {
			tmpNode = childNode->leftNode;
			tmpNode2 = childNode->rightNode;
			childNode->parentNode = grandparentNode->parentNode;
			childNode->leftNode = grandparentNode;
			childNode->rightNode = parentNode;
			childNode->isRed = false;
			parentNode->parentNode = childNode;
			parentNode->leftNode = tmpNode2;
			grandparentNode->parentNode = childNode;
			grandparentNode->rightNode = tmpNode;
			grandparentNode->isRed = true;

			if (tmpNode != nullptr)tmpNode->parentNode = grandparentNode;
			if(tmpNode2!=nullptr)tmpNode2->parentNode = parentNode;

			if (childNode->parentNode == nullptr) root = childNode;
			else if (childNode->parentNode->leftNode == grandparentNode)childNode->parentNode->leftNode = childNode;
			else childNode->parentNode->rightNode = childNode;
			rotateCount++;

		}
		//RR
		else if (parentNode->rightNode != nullptr && parentNode->rightNode == childNode) {
			tmpNode = parentNode->leftNode;
			parentNode->parentNode = grandparentNode->parentNode;
			parentNode->leftNode = grandparentNode;
			parentNode->isRed = false;

			grandparentNode->rightNode = tmpNode;
			grandparentNode->parentNode = parentNode;
			grandparentNode->isRed = true;

			if (tmpNode != nullptr)tmpNode->parentNode = grandparentNode;

			if (parentNode->parentNode == nullptr) root = parentNode;
			else if (parentNode->parentNode->leftNode == grandparentNode)parentNode->parentNode->leftNode = parentNode;
			else parentNode->parentNode->rightNode = parentNode;
			rotateCount++;
		}
	}
}

void postBlack(Node* node) {
	if (node != nullptr) {
		postBlack(node->leftNode);
		postBlack(node->rightNode);
		if (!node->isRed) cout << node->data;
	}
}

void preRed(Node* node) {
	if (node != nullptr) {
		if (node->isRed) cout << node->data;
		preRed(node->leftNode);
		preRed(node->rightNode);
	}
}
