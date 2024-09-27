//两个有序链表序列的交集
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
		if(head == nullptr)//链表为空
		{
			head = new Node(num);
			tail = head;
		}
		else//链表不为空
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
		//输出链表中的元素,以空格分隔,最后一个元素后面没有空格
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
	if(S1.size == 0 || S2.size == 0)//有一个链表为空
	{
		return S3;
	}
	Node* i = S1.head;
	Node* j = S2.head;
	while(i && j)
	{
		if(i->data == j->data)
		{
			S3.push_back(i->data);//将相同的元素加入到新链表中,并且i和j同时后移
			i = i->next;
			j = j->next;
		}
		else if(i->data < j->data)//i的元素小于j的元素,则i后移
		{
			i = i->next;
		}
		else
		{
			j = j->next;//j的元素小于i的元素,则j后移
		}
	}
	return S3;
}

int main() {
	List S1, S2;
	int num;
	//输入第一个链表
	while (cin >> num && num != -1) {
		S1.push_back(num);
	}
	//输入第二个链表
	while (cin >> num && num != -1) {
		S2.push_back(num);
	}
	//求两个链表的交集
	List S3 = GetIntersection(S1, S2);
	//输出交集
	S3.printList();
	system("pause");
	return 0;
}