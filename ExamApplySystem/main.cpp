//排序算法比较
#include <iostream>
#include <ctime>
#include <chrono>
#include <iomanip> 
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

/*
	basic classes / structs
*/

//存储交换次数和时间
class Info
{
public:
	Info() :exchangeTimes(0), time(0) {}
	long long exchangeTimes;//记录交换次数,用long long防止溢出
	double time;//记录时间
};

//计时器
class Timer {
	//构造函数传入一个ptr指针指向一个Info对象
	//Timer所在的作用域结束时，析构函数会计算时间,并将时间存入ptr指向的Info对象
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
		auto duration = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start);//毫秒,double类型
		timePtr->time = duration.count();
	}
};

/*
	functions
*/
//打印结果
void printOutcome(const char* ch, const Info& info) {
	cout << ch << "所用时间: \t" << std::fixed << std::setprecision(4) << info.time << "毫秒" << endl; //输出精度为小数点后4位
	cout << ch << "交换次数: \t" << info.exchangeTimes << "次" << endl;
}

//打印菜单
void printMenu() {
	cout << "**\t\t  排序算法比较 \t\t\t**" << endl;
	cout << "==================================================" << endl;
	cout << "**\t\t0 --- 清屏 \t\t\t**" << endl;
	cout << "**\t\t1 --- 冒泡排序 \t\t\t**" << endl;
	cout << "**\t\t2 --- 选择排序 \t\t\t**" << endl;
	cout << "**\t\t3 --- 直接插入排序 \t\t**" << endl;
	cout << "**\t\t4 --- 希尔排序 \t\t\t**" << endl;
	cout << "**\t\t5 --- 快速排序 \t\t\t**" << endl;
	cout << "**\t\t6 --- 堆排序 \t\t\t**" << endl;
	cout << "**\t\t7 --- 归并排序 \t\t\t**" << endl;
	cout << "**\t\t8 --- 基数排序 \t\t\t**" << endl;
	cout << "**\t\t9 --- 退出程序 \t\t\t**" << endl;
	cout << "==================================================" << endl;
}

//冒泡排序
Info BubbleSort(int arr[], int length) {
	Info result;
	{
		Timer t(&result);//计时器
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length - i - 1; j++) {
				if (arr[j] > arr[j + 1]) {
					//如果arr[j]大于arr[j+1]，交换两者
					int temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
					result.exchangeTimes++;
				}
			}
		}
	}
	return result;
}

//选择排序
Info SelectionSort(int arr[], int length) {
	Info result;
	{
		Timer t(&result);//计时器
		for (int i = 0; i < length; i++) {
			int minIndex = i;
			for (int j = i + 1; j < length; j++) {
				if (arr[j] < arr[minIndex]) {
					minIndex = j;//找出下标i之后最小的数,和arr[i]交换
				}
			}
			//交换
			int temp = arr[i];
			arr[i] = arr[minIndex];
			arr[minIndex] = temp;
			result.exchangeTimes++;
		}
	}
	return result;
}

//直接插入排序
Info DirectInsertion(int arr[], int length) {
	Info result;
	{
		Timer t(&result);//计时器
		for (int i = 1; i < length; i++) {
			int j = i;
			int temp = arr[j];
			while (j > 0 && temp < arr[j - 1]) {
				arr[j] = arr[j - 1];
				j--;
			}
			arr[j] = temp;
			result.exchangeTimes++;
		}
	}
	return result;
}

//希尔排序


//快速排序
void QuickSortRecursion(int arr[], int left, int right, Info& result) //递归快排
{
	if (left >= right) return;
	int i = left, j = right;
	//选取中间值作为pivot,使得左边的数小于pivot,右边的数大于pivot
	int pivot = arr[left + ((right - left) >> 1)];//这种写法防止溢出
	while (i <= j) {
		while (arr[i] < pivot) i++;//寻找左边大于pivot的数
		while (arr[j] > pivot) j--;//寻找右边小于pivot的数
		if (i <= j) {
			//交换
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
			result.exchangeTimes++;
		}
	}
	//递归左右两个子区间
	QuickSortRecursion(arr, left, j, result);
	QuickSortRecursion(arr, i, right, result);
}

Info QuickSort(int arr[], int length) {
	Info result;
	{
		Timer t(&result);//计时器
		QuickSortRecursion(arr, 0, length - 1, result);
	}
	return result;
}

//堆排序


//归并排序


//基数排序



/*
	main function
*/
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