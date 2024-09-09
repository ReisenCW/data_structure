#include <iostream>
#include "functions.h"
#include <ctime>
using namespace std;

int main() {
	enum SortType {
		Bubble = 1,
		Selection,
		Direct,
		Shell,
		Quick,
		Heap,
		Merge,
		Radix,
		Exit
	};
	srand(static_cast<unsigned int>(time(0)));
	int randomArr[static_cast<int>(1e6)];
	cout << "**\t\t\t\t Sort Algorithm Comparison\t\t\t\t**";
	cout << "==============================================";
	cout << "**\t\t\t\t1 --- Bubble Sort ---\t\t\t\t**";
	cout << "**\t\t\t\t2 --- Selection Sort ---\t\t\t\t**";
	cout << "**\t\t\t\t3 --- Direct Insertation sort ---\t\t\t\t**";
	cout << "**\t\t\t\t4 --- Shell Sort ---\t\t\t\t**";
	cout << "**\t\t\t\t5 --- Quick Sort ---\t\t\t\t**";
	cout << "**\t\t\t\t6 --- Heap Sort ---\t\t\t\t**";
	cout << "**\t\t\t\t7 --- Merge Sort ---\t\t\t\t**";
	cout << "**\t\t\t\t8 --- Radix Sort ---\t\t\t\t**";
	cout << "**\t\t\t\t9 --- Exit Program ---\t\t\t\t**";
	Info information; //store the outcome of the functions
	bool running = true;//becomes false when choosing 9.Exit
	int choice = 0;
	int randomNum = 0;
	cout << "please type in the number of random numbers: ";
	cin >> randomNum;
	while (randomNum <= 0) {
		cout << "wrong number, please retype: ";
		cin >> randomNum;
	}
	//make random nums
	for (size_t i = 0; i < randomNum; i++) {
		randomArr[i] = rand() % (static_cast<int>(1e9));
	}
	while (running) {
		cout << "please choose the sort algorithm:\t\t";
		cin >> choice;
		switch (choice) {
		case Bubble:
			information = BubbleSort(randomArr,randomNum);
			printOutcome("Bubble Sort");
		case Selection:

		case Direct:

		case Shell:

		case Quick:

		case Heap:

		case Merge:

		case Radix:

		case Exit:

		default:
			
		}


	}
	

	return 0;
}