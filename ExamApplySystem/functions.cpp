#include "functions.h"
#include "basics.h"
#include <iomanip> 
//��ӡ���
void printOutcome(const char* ch,const Info& info){
	cout << ch << "����ʱ��: \t" << std::fixed << std::setprecision(4) << info.time << "����" << endl; //�������ΪС�����4λ
	cout << ch << "��������: \t" << info.exchangeTimes << "��" << endl;
}

void printMenu() {
	cout << "**\t\t  �����㷨�Ƚ� \t\t\t**" << endl;
	cout << "==================================================" << endl;
	cout << "**\t\t0 --- ���� \t\t\t**" << endl;
	cout << "**\t\t1 --- ð������ \t\t\t**" << endl;
	cout << "**\t\t2 --- ѡ������ \t\t\t**" << endl;
	cout << "**\t\t3 --- ֱ�Ӳ������� \t\t**" << endl;
	cout << "**\t\t4 --- ϣ������ \t\t\t**" << endl;
	cout << "**\t\t5 --- �������� \t\t\t**" << endl;
	cout << "**\t\t6 --- ������ \t\t\t**" << endl;
	cout << "**\t\t7 --- �鲢���� \t\t\t**" << endl;
	cout << "**\t\t8 --- �������� \t\t\t**" << endl;
	cout << "**\t\t9 --- �˳����� \t\t\t**" << endl;
	cout << "==================================================" << endl;
}

//ð������
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

//ѡ������
Info SelectionSort(int arr[], int length) {
	Info result;
	{
		Timer t(&result);//��ʱ��
		for (int i = 0; i < length; i++) {
			int minIndex = i;
			for (int j = i+1; j < length; j++) {
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
	}
	return result;
}

//ֱ�Ӳ�������
Info DirectInsertion(int arr[], int length) {
	Info result;
	{
		Timer t(&result);//��ʱ��
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

//ϣ������


//��������
void QuickSortRecursion(int arr[], int left ,int right,Info& result) //�ݹ����
{
	if (left >= right) return;
	int i = left, j = right;
	//ѡȡ�м�ֵ��Ϊpivot,ʹ����ߵ���С��pivot,�ұߵ�������pivot
	int pivot = arr[left + ((right - left) >> 1)];//����д����ֹ���
	while (i <= j) {
		while (arr[i] < pivot) i++;//Ѱ����ߴ���pivot����
		while (arr[j] > pivot) j--;//Ѱ���ұ�С��pivot����
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
	QuickSortRecursion(arr, left, j,result);
	QuickSortRecursion(arr, i, right,result);
}

Info QuickSort(int arr[], int length) {
	Info result;
	{
		Timer t(&result);//��ʱ��
		QuickSortRecursion(arr,0,length-1,result);
	}
	return result;
}

//������


//�鲢����


//��������