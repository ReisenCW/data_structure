#include "functions.h"
#include "basics.h"
#include <iomanip> 

void printOutcome(const char* ch,const Info& info){
	cout << ch << "所用时间: \t\t" << std::fixed << std::setprecision(4) << info.time << "毫秒" << endl; //输出精度为小数点后四位
	cout << ch << "交换次数: \t\t" << info.exchangeTimes << "次" << endl;
}

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