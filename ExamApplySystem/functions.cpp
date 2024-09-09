#include "functions.h"

struct Info
{
	int exchangeTimes;
	double time;
};

class Timer {
	//pass in a ptr that point to a struct Info,
	//after the scope ends,this class will pass the time value to the time member of Info
private:
	chrono::steady_clock::time_point start;
	Info* timePtr;
public:
	Timer(Info* ptr) {
		auto start = chrono::high_resolution_clock::now();//start time
		timePtr = ptr;
	}

	~Timer() {
		auto end = chrono::high_resolution_clock::now();//end time
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		timePtr->time = static_cast<double>(duration.count());//cast
	}
};

void printOutcome(const char* ch,const Info& info){
	cout << ch << "takes time: \t\t" << info.time << endl;
	cout << ch << "makes exhanges: \t\t" << info.exchangeTimes << endl;
}

Info BubbleSort(int arr[], int length) {
	Info result = { 0,0 };
	{
		Timer t(&result);
		for (int i = 0; i < length; i++)
		{
			for (int j = i + 1; j < length; j++) {
				if (arr[i] > arr[j]) {
					//if the former one is smaller ,switch arr[i] and arr[j]
					int temp = arr[i];
					arr[i] = arr[j];
					arr[i] = temp;
					result.exchangeTimes++;
				}
			}
		}
	}
	return result;
}