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
		Node* temp = new Node(val);//�����½ڵ�
		
		if (temp == nullptr) {//�ڴ��Ƿ����ɹ�
			cerr << "�ڴ����ʧ��" << endl;
			exit(1);
		}
		size++;//���д�С��1
		
		if (front == nullptr) {//��Ϊ�ն���
			front = temp;
			rear = temp;
			return;
		}
		rear->next = temp;//��Ϊ�ն���,����뵽��β
		rear = temp;
	}

	bool pop() {
		//��Ϊ�ն���
		if (front == nullptr)
		{
			return false;
		}
		//��Ϊ�ն���
		Node* temp = front;//ɾ����ͷ�ڵ�
		front = front->next;
		delete temp;
		size--;
		if (front == nullptr) {//��ɾ����Ϊ�ն���
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
	system("pause");
	return 0;
}