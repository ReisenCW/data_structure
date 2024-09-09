#include "functions.h"
#include "basics.h"
#include <iomanip> 
//打印结果
void printOutcome(const char* ch,const Info& info){
	cout << ch << "所用时间: \t" << std::fixed << std::setprecision(4) << info.time << "毫秒" << endl; //输出精度为小数点后4位
	cout << ch << "交换次数: \t" << info.exchangeTimes << "次" << endl;
}

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
			for (int j = 0; j < length-i-1; j++) {
				if (arr[j] > arr[j+1]) {
					//如果arr[j]大于arr[j+1]，交换两者
					int temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
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
			for (int j = i+1; j < length; j++) {
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
void QuickSortRecursion(int arr[], int left ,int right,Info& result) //递归快排
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
	QuickSortRecursion(arr, left, j,result);
	QuickSortRecursion(arr, i, right,result);
}

Info QuickSort(int arr[], int length) {
	Info result;
	{
		Timer t(&result);//计时器
		QuickSortRecursion(arr,0,length-1,result);
	}
	return result;
}

//堆排序


//归并排序


//基数排序