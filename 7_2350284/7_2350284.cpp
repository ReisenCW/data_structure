#include <iostream>
#include <cmath>
using namespace std;

//利用小根堆实现优先队列
class PriorityQueue {
private:
	int size;
	int count;
	int *data;
public:
	PriorityQueue(int N = 20):size(N),count(0),data(new int[N]){}

	~PriorityQueue() {
		if(data != nullptr)
			delete[] data;
	}

	void ShiftUp(int i) {
		while (i > 0 && data[i] < data[(i - 1) >> 1]) {//如果当前节点小于父节点，交换
			swap(data[i], data[(i - 1) >> 1]);
			i = (i - 1) >> 1;//更新当前节点
		}
	}

	void ShiftDown(int i) {
		while ((i << 1) + 1 < count) {//如果有左孩子
			int j = (i << 1) + 1;//j指向左孩子
			if (j + 1 < count && data[j + 1] < data[j]) {//如果有右孩子且右孩子小于左孩子
				j++;//j指向右孩子
			}
			if (data[i] <= data[j]) {//如果当前节点小于等于左右孩子中的最小值
				break;
			}
			swap(data[i], data[j]);//交换当前节点和左右孩子中的最小值
			i = j;//更新当前节点
		}
	}

	void Push(int x) {
		if (size <= count) {
			Resize(size << 1);
		}
		data[count] = x;
		count++;
		ShiftUp(count - 1);
	}

	int Front() const{
		if(count == 0) {
			cerr << "PriorityQueue is empty." << endl;
			exit(1);
		}
		return data[0];
	}

	void Pop() {
		if (count == 0) {
			cerr << "PriorityQueue is empty." << endl;
			exit(1);
		}
		data[0] = data[--count];//将最后一个元素放到堆顶,并删除最后一个元素(逻辑上删除,即--count)
		ShiftDown(0);
	}

	bool Empty() const {
		return count == 0;
	}

	int Count() const {
		return count;
	}

	int Size() const {
		return size;
	}

	void Resize(int newSize) {
		int* newData = new int[newSize];
		if(newData == nullptr) {
			cerr << "Memory allocation failed." << endl;
			exit(1);
		}
		for (int i = 0; i < count && i < newSize; i++) {
			newData[i] = data[i];
		}
		delete[] data;
		data = newData;
	}
};

//求解最小花费
int MiniCost(const int* const length,int N) {
	PriorityQueue q(N);//创建优先队列
	for (int i = 0; i < N; i++) {
		q.Push(length[i]);//将木头长度放入优先队列
	}
	int result = 0;
	while (q.Count() > 1) {//当优先队列中木头数量至少为2时
		int a = q.Front();//取出最短的木头
		q.Pop();//删除最短的木头
		int b = q.Front();//取出次短的木头
		q.Pop();//删除次短的木头
		int sum = a + b;//将两根木头锯成一根木头(题目的逆序操作)
		result += sum;//累加花费
		q.Push(sum);//将新的木头放入优先队列
	}
	return result;//返回最小花费
}

int main() {
	int N = 0;//木头锯成N段
	int* length = nullptr;//木头长度
	cin >> N;
	length = new int[N];
	for (int i = 0; i < N; i++) {
		cin >> length[i];//输入每段木头的长度
	}
	cout << MiniCost(length, N) << endl;//求解最小花费
	delete[] length;//释放内存
	system("pause");
	return 0;
}