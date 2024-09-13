//�����㷨�Ƚ�
#include <iostream>
#include <ctime>
#include <chrono>
#include <iomanip> 
#include <thread>
using namespace std;

//����atomic��,���ڿ��������̵߳�ȡ��(����ʱ�������)
static std::atomic<bool> stopSorting = false;
static std::atomic<bool> sortingDone = false;

#define DEBUG 0

//�����ô���
#if DEBUG
void printArray(int arr[],int length) {
	std::cout << "����Ϊ: ";
	for (size_t i = 0; i < length; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << endl;
	std::cout << endl;
}
#endif

/*
	basic classes / structs
*/

//�洢����������ʱ��
class Info
{
public:
	Info() :exchangeTimes(0), time(0) {}
	long long exchangeTimes;//��¼��������,��long long��ֹ���
	double time;//��¼ʱ��
};

//��ʱ��
class Timer {
	//���캯������һ��ptrָ��ָ��һ��Info����
	//Timer���ڵ����������ʱ���������������ʱ��,����ʱ�����ptrָ���Info����
private:
	chrono::steady_clock::time_point start;
	Info* timePtr;
public:
	Timer(Info* ptr) {
		start = chrono::high_resolution_clock::now();//start time
		timePtr = ptr;
	}

	~Timer() {
		auto end = chrono::high_resolution_clock::now();//end time
		auto duration = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start);//����,double����
		timePtr->time = duration.count();
	}
};

/*
	functions
*/
//��ӡ���
void printOutcome(const char* ch, const Info& info) {
	if (info.exchangeTimes != -1) //��Ϊ-1,���ʾȡ������
	{
		std::cout << ch << "����ʱ��: \t" << std::fixed << std::setprecision(4) << info.time << "����" << endl; //�������ΪС�����4λ
		std::cout << ch << "��������: \t" << info.exchangeTimes << "��" << endl;
	}
}

//��ӡ�˵�
void printMenu() {
	std::cout << "**\t\t  �����㷨�Ƚ� \t\t\t**" << endl;
	std::cout << "==================================================" << endl;
	std::cout << "**\t\t0 --- ���� \t\t\t**" << endl;
	std::cout << "**\t\t1 --- ð������ \t\t\t**" << endl;
	std::cout << "**\t\t2 --- ѡ������ \t\t\t**" << endl;
	std::cout << "**\t\t3 --- ֱ�Ӳ������� \t\t**" << endl;
	std::cout << "**\t\t4 --- ϣ������ \t\t\t**" << endl;
	std::cout << "**\t\t5 --- �������� \t\t\t**" << endl;
	std::cout << "**\t\t6 --- ������ \t\t\t**" << endl;
	std::cout << "**\t\t7 --- �鲢���� \t\t\t**" << endl;
	std::cout << "**\t\t8 --- �������� \t\t\t**" << endl;
	std::cout << "**\t\t9 --- �˳����� \t\t\t**" << endl;
	std::cout << "==================================================" << endl;
}

//���ڶ��߳�,-1ȡ������
void monitorInput() {
	int input;
	//�ȴ�6��,��6����û���������,����ʾ�û�����-1ȡ������
	for(int i = 0;i < 6;i++){
		if (sortingDone) return;
		this_thread::sleep_for(chrono::seconds(1));//�ȴ�1��
	}
	while (!sortingDone) {
		std::cout << "����-1ȡ������: ";
		cin >> input;
		if (input == -1) {
			stopSorting = true;
			std::cout << "\t ȡ������" << endl;
		}
		else {
			std::cout << "\t ��Ч����" << endl;
		}
		this_thread::sleep_for(chrono::seconds(1));
	}
}

//ð������
Info BubbleSort(int arr[], int length) {
	Info result;
	{
		Timer t(&result);//��ʱ��
		for (int i = 0; i < length && !stopSorting; i++)
		{
			for (int j = 0; j < length - i - 1 && !stopSorting; j++) {
				if (arr[j] > arr[j + 1]) {
					//���arr[j]����arr[j+1]����������
					int temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
					result.exchangeTimes++;
				}
			}
		}
		sortingDone = true;
	}
	if(stopSorting)	result.exchangeTimes = -1;
	return result;
}

//ѡ������
Info SelectionSort(int arr[], int length) {
	Info result;
	{
		Timer t(&result);//��ʱ��
		for (int i = 0; i < length && !stopSorting; i++) {
			int minIndex = i;
			for (int j = i + 1; j < length && !stopSorting; j++) {
				if (arr[j] < arr[minIndex]) {
					minIndex = j;//�ҳ��±�i֮����С����,��arr[i]����
				}
			}
			//����
			int temp = arr[i];
			arr[i] = arr[minIndex];
			arr[minIndex] = temp;
			result.exchangeTimes++;
		}
		sortingDone = true;
	}
	if (stopSorting)	result.exchangeTimes = -1;
	return result;
}

//ֱ�Ӳ�������
Info DirectInsertion(int arr[], int length) {
	Info result;
	{
		Timer t(&result);//��ʱ��
		for (int i = 1; i < length && !stopSorting; i++) {
			int j = i;
			int temp = arr[j];
			while (j > 0 && temp < arr[j - 1] && !stopSorting) {
				arr[j] = arr[j - 1];
				j--;
			}
			arr[j] = temp;
			result.exchangeTimes++;
		}
		sortingDone = true;
	}
	if (stopSorting)	result.exchangeTimes = -1;
	return result;
}

//ϣ������
Info ShellSort(int arr[], int length) {
	Info result;
	{
		Timer t(&result);//��ʱ��
		int gap = length;
		do{
			gap = gap / 3 + 1;//��Сgap,���һ��ѭ��gapΪ1
			//gap����,ÿ�����ֱ�Ӳ�������
			for (int i = gap; i < length && !stopSorting; i++) {
				int j = i;
				int temp = arr[j];
				while (j >= gap && temp < arr[j - gap] && !stopSorting) {
					arr[j] = arr[j - gap];
					j -= gap;
				}
				arr[j] = temp;
				result.exchangeTimes++;
			}			
		} while (gap > 1 && !stopSorting);
	}
	sortingDone = true;
	if (stopSorting)	result.exchangeTimes = -1;
	return result;
}
//��������
void QuickSortRecursion(int arr[], int left, int right, Info& result) //�ݹ����
{
	if (left >= right || stopSorting) return;
	int i = left, j = right;
	//ѡȡ�м�ֵ��Ϊpivot,ʹ����ߵ���С��pivot,�ұߵ�������pivot
	int pivot = arr[left + ((right - left) >> 1)];//����д����ֹ���
	while (i <= j && !stopSorting) {
		while (arr[i] < pivot && !stopSorting) i++;//Ѱ����ߴ���pivot����
		while (arr[j] > pivot && !stopSorting) j--;//Ѱ���ұ�С��pivot����
		if (i <= j) {
			//����
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
			result.exchangeTimes++;
		}
	}
	//�ݹ���������������
	QuickSortRecursion(arr, left, j, result);
	QuickSortRecursion(arr, i, right, result);
}

Info QuickSort(int arr[], int length) {
	Info result;
	{
		Timer t(&result);//��ʱ��
		QuickSortRecursion(arr, 0, length - 1, result);
	}
	sortingDone = true;
	if (stopSorting)	result.exchangeTimes = -1;
	return result;
}

//������
void BuildHeap(int arr[], int start, int m, Info& result) {
	int i = start;
	int j = 2 * i + 1;
	while (j <= m && !stopSorting) {
		if (j < m && arr[j] < arr[j + 1]) j++;//����ҽڵ��ڷ�Χ��,���ҽڵ������ڵ�,��jָ���ҽڵ�
		//���ӽڵ���ڸ��ڵ�,�򽻻�,���������µ���
		if (arr[i] < arr[j]) {
			swap(arr[i], arr[j]);
			i = j;
			j = 2 * i + 1;
			result.exchangeTimes++;
		}
		else break;
	}
}
Info HeapSort(int arr[], int length) {
	Info result;
	{
		Timer t(&result); //��ʱ��
		int len = length;
		//��������
		for(int i=len/2;i>=0 && !stopSorting;--i)
			BuildHeap(arr,i,len-1,result);
		//�����Ѷ������һ��Ԫ��,Ȼ�������Ϊ�����
		while (len-- && !stopSorting) {
			swap(arr[0], arr[len]);
			BuildHeap(arr, 0, len - 1,result);
		}
	}
	sortingDone = true;
	if (stopSorting)	result.exchangeTimes = -1;
	return result;
}


//�鲢����
void MergeRecursion(int arr[], int left, int mid, int right, Info& result) {
	int i = left, j = mid+1,k = 0;
	int* newArr = new int[right - left + 1];
	for (i = left, j = mid + 1; i <= mid && j <= right && !stopSorting; k++) {
		if (arr[i] < arr[j]) {
			newArr[k] = arr[i];
			i++;
		}
		else {
			newArr[k] = arr[j];
			j++;
		}
	}
	while(i <= mid && !stopSorting) {
		newArr[k] = arr[i];
		k++;
		i++;
	}
	while (j <= right && !stopSorting) {
		newArr[k] = arr[j];
		k++;
		j++;
	}

	for (int index = left; index <= right && !stopSorting; index++) {
		arr[index] = newArr[index-left];
		result.exchangeTimes++;
	}
	delete[] newArr;
}


void DividRecursion(int arr[], int left, int right, Info& result) {
	if (left >= right) return;
	int mid = left + ((right - left) >> 1);
	DividRecursion(arr, left, mid, result);
	DividRecursion(arr, mid + 1, right, result);
	MergeRecursion(arr, left, mid, right, result);
}

Info MergeSort(int arr[], int length) {
	Info result;
	{
		Timer t(&result);//��ʱ��
		DividRecursion(arr, 0, length - 1, result);
	}
	sortingDone = true;
	if (stopSorting)	result.exchangeTimes = -1;
	return result;
}

class Node {
public:
	int data;
	int next;
};

class StaticList {
public:
	int head;
	int tail;
	int size;
	int length;
	Node* vector;
	StaticList(int l) :head(1),tail(1),length(0),size(l+1)
	{	
		//�ճ�vector[0]
		vector = new Node[l+1];
		for (int i = 1; i < l; i++) {
			vector[i].next = i+1;
		}
		vector[l].next = 1;
		vector[0].next = 1;
	}

	void push(int val) {
		if (length >= size) {
			cerr << "StaticList is full" << endl;
			return;
		}
		vector[tail].data = val;
		tail = vector[tail].next;
		length++;
	}

	~StaticList() {
		delete[] vector;
	}
};

int GetDegree(int num, int digit) //��ȡλ,��λΪ1,�����ŵ��� 
{
	for (int i = 0; i < digit-1; i++) {
		num /= 10;
	}
	return num % 10;
}

Info RadixSort(int arr[], int length) {
	Info result;
	//Bucket* radixArr = new Bucket[10];//�����洢��λ�������
	//������arr�е����ݴ��뾲̬������
	StaticList* staticList = new StaticList(length);
	for (int i = 1; i <= length; i++) {
		staticList->push(arr[i-1]);
	}
	int max = arr[0];
	for (int i = 1; i < length; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	int maxDegree = 1;
	while (max / 10 != 0) {
		maxDegree++;
		max /= 10;
	}

	{
		Timer t(&result);//��ʱ��
		for (int degree = 1; degree <= maxDegree; degree++) {
			int front[10] = { 0 };//ÿ�����е�ͷָ��
			int rear[10] = { 0 };//ÿ�����е�βָ��
			int currentListIndex = staticList->head;//��ǰ��̬���������
			for (int i = 0; i < length && !stopSorting; i++) {
				//�����ĸ�Ͱ��
				int index = GetDegree(staticList->vector[currentListIndex].data, degree);				result.exchangeTimes++;
				//�����ͰΪ��,���ʼ��
				if (front[index] == 0) {
					front[index] = currentListIndex;
					rear[index] = currentListIndex;
				}
				//�����Ϊ��,��ѵ�ǰԪ�ط���Ͱ��β��
				else {
					staticList->vector[rear[index]].next = currentListIndex;
					rear[index] = currentListIndex;
				}
				//����ָ�����,ָ����һ��Ԫ��
				currentListIndex = staticList->vector[currentListIndex].next;
			}
			//��Ͱ�е����ݴ�����
			int first = 0;
			int last = 9;
			//�ҵ���һ����Ϊ�յ�Ͱ
			while(front[first] == 0 && !stopSorting) {
				first++;
			}
			//�ҵ����һ����Ϊ�յ�Ͱ
			while(front[last] == 0 && !stopSorting) {
				last--;
			}
			//ͷָ��ָ���һ����Ϊ�յ�Ͱ�еĵ�һ���ڵ�
			staticList->head = front[first];

			//�ѷǿ�Ͱ��β���
			for (int i = first; i <= last && !stopSorting; i++) {
				int j = i + 1;
				//��Ϊ��Ͱ,������
				if (front[i] == 0) continue;
				else {
					//�ҵ���һ����Ϊ�յ�Ͱ
					while(j <= last && front[j] == 0 && !stopSorting) {
						j++;
					}
					//��ǰһ��Ͱ��β��ָ���һ��Ͱ��ͷ��
					staticList->vector[rear[i]].next = front[j];
					i = j-1;
				}
			}
			//���һ����Ϊ�յ�Ͱ�е����һ���ڵ�ָ���һ��Ϊ�յ�Ͱ�еĵ�һ���ڵ�
			staticList->vector[rear[last]].next = front[first];
		}
		//�������,�����ݸ�ֵ��arr
		int currentIndex = staticList->head;
		for (int i = 0; i < length && !stopSorting; i++) {
			arr[i] = staticList->vector[currentIndex].data;
			currentIndex = staticList->vector[currentIndex].next;
		}	
	}
	delete staticList;
	sortingDone = true;
	if (stopSorting)	result.exchangeTimes = -1;
	return result;
}


/*
	main function
*/
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
	std::cout << "����������ĸ���: ";
	cin >> randomNum;
	while (!cin.good() || randomNum <= 0) {
		std::cout << "�������,����������: ";
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
		//��ʼ����Ϣ
		information.exchangeTimes = -1;
		stopSorting = false;
		sortingDone = false;
		//ѡ�������㷨
		std::cout << "ѡ�������㷨: ";
		cin >> choice;
		while(!cin.good()&&(choice < 0 || choice > 9)) {
			std::cout << "�������,����������: ";
			cin.clear();
			cin >> choice;
		}
		//�����������,�ø��Ƶ�������Ϊ����,��ֹ�ı�ԭ����,�Ա��´�����	
		for (size_t i = 0; i < randomNum; i++) {
			copyArr[i] = randomArr[i];
		}
#if DEBUG
		std::cout << endl;
		std::cout << "����ǰ";
		printArray(copyArr,randomNum);
#endif
		//���̴߳����˳������㷨
		thread inputThread(monitorInput);
		switch (static_cast<SortType>(choice)) {
		case Clear:
			sortingDone = true;
			system("cls");//����
			printMenu();//��ӡ�˵�
			inputThread.join();
			std::cout << "����������ĸ���: " << randomNum;//��ӡ������ĸ���
			break;
		case Bubble:
			information = BubbleSort(copyArr, randomNum);
			inputThread.join();
			printOutcome("ð������", information);
			break;
		case Selection:
			information = SelectionSort(copyArr, randomNum);
			inputThread.join();
			printOutcome("ѡ������", information);
			break;
		case Direct:
			information = DirectInsertion(copyArr, randomNum);
			inputThread.join();
			printOutcome("ֱ�Ӳ�������", information);
			break;
		case Shell:
			information = ShellSort(copyArr,randomNum);
			inputThread.join();
			printOutcome("ϣ������", information);
			break;
		case Quick:
			information = QuickSort(copyArr,randomNum);
			inputThread.join();
			printOutcome("��������",information);
			break;
		case Heap:
			information = HeapSort(copyArr,randomNum);
			inputThread.join();
			printOutcome("������", information);
			break;
		case Merge:
			information = MergeSort(copyArr, randomNum);
			inputThread.join();
			printOutcome("�鲢����", information);
			break;
		case Radix:
			information = RadixSort(copyArr,randomNum);
			inputThread.join();
			printOutcome("��������", information);
			break;
		case Exit:
			running = false;
			sortingDone = true;
			inputThread.join();
			break;
		}
		std::cout << endl;
#if DEBUG
		std::cout << "�����";
		printArray(copyArr,randomNum);
#endif
		
	}

	delete[] randomArr;
	delete[] copyArr;
	system("pause");
	return 0;
}