//����ҵ��
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
		//�����½ڵ�
		Node* temp = new Node(val);
		//�ڴ��Ƿ����ɹ�
		if (temp == nullptr) {
			cerr << "�ڴ����ʧ��" << endl;
			exit(1);
		}
		//���д�С��1
		size++;
		//��Ϊ�ն���
		if (front == nullptr) {
			front = temp;
			rear = temp;
			return;
		}
		//��Ϊ�ն���,����뵽��β
		rear->next = temp;
		rear = temp;
	}

	bool pop() {
		//��Ϊ�ն���
		if (front == nullptr)
		{
			return false;
		}
		//��Ϊ�ն���
		//ɾ����ͷ�ڵ�
		Node* temp = front;
		front = front->next;
		delete temp;
		size--;
		//��ɾ����Ϊ�ն���
		if (front == nullptr) {
			rear = nullptr;
		}
	}

	int getFront() {
		if (front == nullptr) {
			cerr << "����Ϊ��" << endl;
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

private:
	int size;
	Node* front;
	Node* rear;
};

int main() {
	int N;//�˿�����
	cin >> N;
	if (N <= 0) {
		cout << "�������" << endl;
		return 0;
	}
	ListQueue qA;
	ListQueue qB;
	for (int i = 0; i < N; i++) {
		int id = 0;
		cin >> id;
		//�������뵽A����,ż�����뵽B����
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
	return 0;
}