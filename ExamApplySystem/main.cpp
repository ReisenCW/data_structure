//排序算法比较
#include <iostream>
#include "functions.h"
#include "basics.h"
#include <ctime>
using namespace std;

#define DEBUG 0

//调试用代码
#if DEBUG
void printArray(int arr[],int length) {
	cout << "数组为: ";
	for (size_t i = 0; i < length; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	cout << endl;
}
#endif

int main() {
	enum SortType	//排序算法的类型
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
	srand(static_cast<unsigned int>(time(0)));//随机数种子
	//菜单
	printMenu();
	Info information; //存储排序算法的信息
	bool running = true;//选择退出时变为false
	int choice;//选择排序算法
	int randomNum = 0;//随机数的个数
	//输入随机数的个数
	cout << "输入随机数的个数: ";
	cin >> randomNum;
	while (!cin.good() || randomNum <= 0) {
		cout << "输入错误,请重新输入: ";
		cin.clear();
		cin >> randomNum;
	}
	//生成随机数数组
	int* randomArr = new int[static_cast<int>(randomNum)];//随机数数组
	int* copyArr = new int[static_cast<int>(randomNum)];//复制随机数组的数组
	for (size_t i = 0; i < randomNum; i++) {
		randomArr[i] = rand() % (static_cast<int>(1e9));
	}

	//主循环
	while (running) {
		//选择排序算法
		cout << "选择排序算法: ";
		cin >> choice;
		while(!cin.good()&&(choice < 0 || choice > 9)) {
			cout << "输入错误,请重新输入: ";
			cin.clear();
			cin >> choice;
		}
		//复制随机数组,用复制的数组作为参数,防止改变原数组,以便下次排序	
		for (size_t i = 0; i < randomNum; i++) {
			copyArr[i] = randomArr[i];
		}
#if DEBUG
		cout << endl;
		cout << "排序前";
		printArray(copyArr,randomNum);
#endif
		switch (static_cast<SortType>(choice)) {
		case Clear:
			system("cls");//清屏
			printMenu();//打印菜单
			cout << "输入随机数的个数: " << randomNum;//打印随机数的个数
			break;
		case Bubble:
			information = BubbleSort(copyArr, randomNum);
			printOutcome("冒泡排序", information);
			break;
		case Selection:
			information = SelectionSort(copyArr, randomNum);
			printOutcome("选择排序", information);
			break;
		case Direct:
			information = DirectInsertion(copyArr, randomNum);
			printOutcome("直接插入排序", information);
			break;
		case Shell:
			
			break;
		case Quick:
			information = QuickSort(copyArr,randomNum);
			printOutcome("快速排序",information);
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
		cout << "排序后";
		printArray(copyArr,randomNum);
#endif
		
	}

	delete[] randomArr;
	delete[] copyArr;
	system("pause");
	return 0;
}