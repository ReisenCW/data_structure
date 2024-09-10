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


//�鲢����


//��������



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
			
			break;
		case Quick:
			information = QuickSort(copyArr,randomNum);
			inputThread.join();
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