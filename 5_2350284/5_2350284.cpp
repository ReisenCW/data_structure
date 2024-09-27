//银行业务
#include <iostream>
using namespace std;
#define DEBUG 0


class ListQueue;
class Node;

class Node {
	friend class ListQueue;
public:
	Node(int val):data(val), next(nullptr) {}
private:
	int data;
	Node* next;
};

class ListQueue 
{
private:
	int size;
	Node* front;
	Node* rear;
public:
	ListQueue():size(),front(nullptr), rear(nullptr) {}

	~ListQueue() {
		while (front != nullptr) {
			Node* temp = front;
			front = front->next;
			delete temp;
		}
	}

	void push(int val) {
		Node* temp = new Node(val);//创建新节点
		
		if (temp == nullptr) {//内存是否分配成功
			cerr << "内存分配失败" << endl;
			exit(1);
		}
		size++;//队列大小加1
		
		if (front == nullptr) {//若为空队列
			front = temp;
			rear = temp;
			return;
		}
		rear->next = temp;//不为空队列,则插入到队尾
		rear = temp;
	}

	bool pop() {
		//若为空队列
		if (front == nullptr)
		{
			return false;
		}
		//不为空队列
		Node* temp = front;//删除队头节点
		front = front->next;
		delete temp;
		size--;
		if (front == nullptr) {//若删除后为空队列
			rear = nullptr;
		}
	}

	int getFront() {
		if (front == nullptr) {
			cerr << "队列为空" << endl;
			exit(1);
		}
		return front->data;
	}

	bool empty() {
		return front == nullptr;
	}
#if DEBUG
	void print() {
		Node* temp = front;
		while (temp != nullptr) {
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}
#endif
};

int main() {
	int N;//顾客总数
	cin >> N;
	if (N <= 0) {
		cout << "输入错误" << endl;
		return 0;
	}
	ListQueue qA;
	ListQueue qB;
	for (int i = 0; i < N; i++) {
		int id = 0;
		cin >> id;
		//奇数插入到A队列,偶数插入到B队列
		if(id % 2 == 1)
			qA.push(id);
		else 
			qB.push(id);
	}
	int Timer = 0;
	int answer[2000] = { 0 };
	int index = 0;
#if DEBUG
	qA.print();
	qB.print();
#endif
	while(!qA.empty() || !qB.empty()) {
		Timer++;
		Timer %= 2;
		if(!qA.empty()) {
			answer[index++] = qA.getFront();
			qA.pop();
			if (Timer == 1) {
				continue;
			}
		}
		if (!qB.empty()) {
			answer[index++] = qB.getFront();
			qB.pop();
		}
	}
	cout << answer[0];
	for (int i = 1; i < index; i++) {
		cout << " " << answer[i];
	}
	system("pause");
	return 0;
}