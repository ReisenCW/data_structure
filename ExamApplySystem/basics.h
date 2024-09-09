#pragma once
#include <iostream>
#include <chrono>
using namespace std;

//存储交换次数和时间
class Info
{
public:
	Info() :exchangeTimes(0), time(0) {}
	int exchangeTimes;//记录交换次数
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
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);//毫秒
		timePtr->time = static_cast<double>(duration.count());//cast
	}
};