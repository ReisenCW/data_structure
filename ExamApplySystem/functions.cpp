#include "functions.h"
#include "basics.h"
#include <iomanip> 

void printOutcome(const char* ch,const Info& info){
	cout << ch << "����ʱ��: \t\t" << std::fixed << std::setprecision(4) << info.time << "����" << endl; //�������ΪС�������λ
	cout << ch << "��������: \t\t" << info.exchangeTimes << "��" << endl;
}

Info BubbleSort(int arr[], int length) {
	Info result;
	{
		Timer t(&result);//��ʱ��
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length-i-1; j++) {
				if (arr[j] > arr[j+1]) {
					//���arr[j]����arr[j+1]����������
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