#pragma once
#include <iostream>
#include <chrono>
using namespace std;

//�洢����������ʱ��
class Info
{
public:
	Info() :exchangeTimes(0), time(0) {}
	int exchangeTimes;//��¼��������
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
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);//����
		timePtr->time = static_cast<double>(duration.count());//cast
	}
};