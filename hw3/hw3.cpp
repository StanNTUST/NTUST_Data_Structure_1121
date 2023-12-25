/***********************************************************************
 * File: main.cpp
 * Author: JiaHong-Wang
 * Create Date: 2023-11-27
 * Editor: JiaHong-Wang
 * Update Date: 2023-11-27
 * Description: find key in the selection sort and insertion sort
 * ***********************************************************************/
#include<iostream>
#include<string>

using namespace std;

struct Pair {
	int number;
	char charactor;

};

void swap(Pair& data, Pair& data2);
int selectionSort(Pair data[]);
int insertionSort(Pair data[]);
bool check(Pair data[]);
string findText;

int number = 0;

int main() {
	int selectKey, insertKey;
	string  text, numberText, tmpText;
	Pair data[100], data2[100];

	getline(cin, findText);

	getline(cin, numberText);

	getline(cin, text);
	size_t start = 0, start2 = 0;
	size_t end = numberText.find(" "), end2 = text.find(" ");
	while (end != string::npos) {
		tmpText = numberText.substr(start, end - start);
		start = end + 1;
		end = numberText.find(" ", start);
		data[number].number = stoi(tmpText);
		data2[number].number = stoi(tmpText);

		tmpText = text.substr(start2, end2 - start2);
		start2 = end2 + 1;
		end2 = text.find(" ", start2);
		data[number].charactor = tmpText[0];
		data2[number].charactor = tmpText[0];

		number++;
	}
	tmpText = numberText.substr(start, end - start);
	data[number].number = stoi(tmpText);
	data2[number].number = stoi(tmpText);

	tmpText = text.substr(start2, end2 - start2);
	data[number].charactor = tmpText[0];
	data2[number].charactor = tmpText[0];

	number++;
	selectKey = selectionSort(data);
	insertKey = insertionSort(data2);

	if (selectKey == -1 && insertKey == -1) cout << "Word not found." << endl;
	else if (selectKey == -1 && insertKey != -1) cout << "Word found in insertion sort step " << insertKey << "." << endl;
	else if (selectKey != -1 && insertKey == -1) cout << "Word found in selection sort step " << selectKey << "." << endl;
	else if (selectKey != -1 && insertKey != -1) cout << "Word found in insertion sort step " << insertKey << " and selection sort step " << selectKey << "." << endl;
	for (int i = 0; i < number; i++) cout << data[i].charactor;
}
void swap(Pair& data, Pair& data2) {
	int tmpNumber = data.number;
	char tmpChar = data.charactor;

	data.number = data2.number;
	data.charactor = data2.charactor;

	data2.number = tmpNumber;
	data2.charactor = tmpChar;
}
bool check(Pair data[]) {
	if (findText.length() > number) return false;

	for (int i = 0; i < number && i < findText.length(); i++) {
		if (data[i].charactor != findText[i]) return false;
	}

	return true;
}
int selectionSort(Pair data[]) {
	int key = -1, small;
	for (int i = 0; i < number; i++) {
		small = i;

		for (int j = i + 1; j < number; j++) {
			if (data[small].number > data[j].number) {
				small = j;
			}
		}

		swap(data[i], data[small]);

		if (check(data) && key == -1) key = i + 1;
	}
	return key;
}
int insertionSort(Pair data[]) {
	int key = -1, i, j, tmpNumber;
	char tmpChar;

	for (i = 1; i < number - 1; i++) {
		tmpNumber = data[i].number;
		tmpChar = data[i].charactor;

		for (j = i - 1; 0 <= j && tmpNumber <= data[j].number; j--) {
			data[j + 1].number = data[j].number;
			data[j + 1].charactor = data[j].charactor;
		}

		data[j + 1].number = tmpNumber;
		data[j + 1].charactor = tmpChar;

		if (check(data) && key == -1) key = i+1;
	}
	return key;
}
