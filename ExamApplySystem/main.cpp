//�����㷨�Ƚ�
#include <iostream>
#include "functions.h"
#include "basics.h"
#include <ctime>
using namespace std;

#define DEBUG 0

//�����ô���
#if DEBUG
void printArray(int arr[],int length) {
	cout << "����Ϊ: ";
	for (size_t i = 0; i < length; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	cout << endl;
}
#endif

int main() {
	enum SortType	//�����㷨������
	{	
		Clear = 0,
		Bubble,
		Selection,
		Direct,
		Shell,
		Quick,
		Heap,
		Merge,
		Radix,
		Exit
	};
	srand(static_cast<unsigned int>(time(0)));//���������
	//�˵�
	printMenu();
	Info information; //�洢�����㷨����Ϣ
	bool running = true;//ѡ���˳�ʱ��Ϊfalse
	int choice;//ѡ�������㷨
	int randomNum = 0;//������ĸ���
	//����������ĸ���
	cout << "����������ĸ���: ";
	cin >> randomNum;
	while (!cin.good() || randomNum <= 0) {
		cout << "�������,����������: ";
		cin.clear();
		cin >> randomNum;
	}
	//�������������
	int* randomArr = new int[static_cast<int>(randomNum)];//���������
	int* copyArr = new int[static_cast<int>(randomNum)];//����������������
	for (size_t i = 0; i < randomNum; i++) {
		randomArr[i] = rand() % (static_cast<int>(1e9));
	}

	//��ѭ��
	while (running) {
		//ѡ�������㷨
		cout << "ѡ�������㷨: ";
		cin >> choice;
		while(!cin.good()&&(choice < 0 || choice > 9)) {
			cout << "�������,����������: ";
			cin.clear();
			cin >> choice;
		}
		//�����������,�ø��Ƶ�������Ϊ����,��ֹ�ı�ԭ����,�Ա��´�����	
		for (size_t i = 0; i < randomNum; i++) {
			copyArr[i] = randomArr[i];
		}
#if DEBUG
		cout << endl;
		cout << "����ǰ";
		printArray(copyArr,randomNum);
#endif
		switch (static_cast<SortType>(choice)) {
		case Clear:
			system("cls");//����
			printMenu();//��ӡ�˵�
			cout << "����������ĸ���: " << randomNum;//��ӡ������ĸ���
			break;
		case Bubble:
			information = BubbleSort(copyArr, randomNum);
			printOutcome("ð������", information);
			break;
		case Selection:
			information = SelectionSort(copyArr, randomNum);
			printOutcome("ѡ������", information);
			break;
		case Direct:
			information = DirectInsertion(copyArr, randomNum);
			printOutcome("ֱ�Ӳ�������", information);
			break;
		case Shell:
			
			break;
		case Quick:
			information = QuickSort(copyArr,randomNum);
			printOutcome("��������",information);
			break;
		case Heap:
			
			break;
		case Merge:
			
			break;
		case Radix:
			
			break;
		case Exit:
			running = false;
			break;
		}
		cout << endl;
#if DEBUG
		cout << "�����";
		printArray(copyArr,randomNum);
#endif
		
	}

	delete[] randomArr;
	delete[] copyArr;
	system("pause");
	return 0;
}