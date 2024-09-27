//���������������еĽ���
#include <iostream>
using namespace std;

class List;
List GetIntersection(const List& S1, const List& S2);


class Node {
	friend class List;
	friend List GetIntersection(const List& S1, const List& S2);
private:
	int data;
	Node* next;
	Node* prev;
	Node(int data): data(data), next(nullptr), prev(nullptr) {}
};

class List {
	friend List GetIntersection(const List& S1, const List& S2);
private:
	Node* head;
	Node* tail;
	int size;
public:
	List(): head(nullptr), tail(nullptr),size(0) {}

	void push_back(int num) {
		if(head == nullptr)//����Ϊ��
		{
			head = new Node(num);
			tail = head;
		}
		else//����Ϊ��
		{
			Node* p = new Node(num);
			tail->next = p;
			p->prev = tail;
			tail = p;
		}
		size++;
	}

	void printList()const {
		if (size == 0) {
			cout << "NULL" << endl;
			return;
		}
		//��������е�Ԫ��,�Կո�ָ�,���һ��Ԫ�غ���û�пո�
		Node* p = head;
		cout << p->data;
		p = p->next;
		while (p) {
			cout << " " << p->data;
			p = p->next;
		}
	}

	List(const List& L) : head(nullptr), tail(nullptr), size(0)
	{
		Node* p = L.head;
		while (p) {
			push_back(p->data);
			p = p->next;
		}
	}

	~List() {
		Node* p = head;
		while (p) {
			Node* q = p;
			p = p->next;
			delete q;
		}
	}
};

List GetIntersection(const List& S1, const List & S2) {
	List S3;
	if(S1.size == 0 || S2.size == 0)//��һ������Ϊ��
	{
		return S3;
	}
	Node* i = S1.head;
	Node* j = S2.head;
	while(i && j)
	{
		if(i->data == j->data)
		{
			S3.push_back(i->data);//����ͬ��Ԫ�ؼ��뵽��������,����i��jͬʱ����
			i = i->next;
			j = j->next;
		}
		else if(i->data < j->data)//i��Ԫ��С��j��Ԫ��,��i����
		{
			i = i->next;
		}
		else
		{
			j = j->next;//j��Ԫ��С��i��Ԫ��,��j����
		}
	}
	return S3;
}

int main() {
	List S1, S2;
	int num;
	//�����һ������
	while (cin >> num && num != -1) {
		S1.push_back(num);
	}
	//����ڶ�������
	while (cin >> num && num != -1) {
		S2.push_back(num);
	}
	//����������Ľ���
	List S3 = GetIntersection(S1, S2);
	//�������
	S3.printList();
	system("pause");
	return 0;
}