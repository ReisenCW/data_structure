#include <iostream>
using namespace std;

struct Link;
class ListQueue;
class Node;

//Link:�ڽӱ��еĽڵ�
struct Link{
	int cost = 0;//����������ʱ��
	int to = -1;//��ɸýڵ�����ǰ������һ���ڵ�
};

//Vector:��̬����ģ����
template <typename T>
class Vector {
private:
	T* data;
public:
	int size;//��ǰԪ�ظ���
	int capacity;//����
public:
	Vector(int N = 20) :size(0), capacity(N), data(new T[N]) {
		if (data == nullptr) {
			cerr << "�ڴ����ʧ��" << endl;
			exit(1);
		}
	}

	~Vector() {
		if (data != nullptr)
			delete[] data;
	}

	void Resize(int newSize) {
		T* temp = new T[newSize];
		if(size > newSize){
			size = newSize;
		}
		for (int i = 0; i < size; i++) {
			temp[i] = data[i];
		}
		delete[] data;
		data = temp;
		capacity = newSize;
	}

	void push_back(T x) {
		if (size >= capacity) {
			Resize(capacity << 1);
		}
		data[size++] = x;
	}

	T& operator[](int index) {
		if (index < 0 || index >= capacity) {
			cerr << "�±�Խ��" << endl;
			exit(1);
		}
		if(index >= size){
			size = index+1;
		}
		return data[index];
	}
};

//Stack:ջ��ģ����
template <typename T>
class Stack {
public:
	Stack(int size = 100) : data(nullptr), size(size), top(-1) {
		data = new T[size];
		isValid();
	}
	~Stack() {
		delete[] data;
	}
	void push(const T& x) {
		//���ջ����,�����·���ռ�
		if (top >= size - 1) {
			T* temp = new T[size * 2];
			isValid();
			for (int i = 0; i < size; i++) {
				temp[i] = data[i];
			}
			delete[] data;
			data = temp;
			size *= 2;
		}
		//��ջ
		data[++top] = x;
	}
	T pop() {
		if (top == -1)
		{
			cerr << "ջΪ��" << endl;
			exit(1);
		}
		return data[top--];
	}
	T getTop() {
		if (top == -1)
		{
			cerr << "ջΪ��" << endl;
			exit(1);
		}
		return data[top];
	}
	bool empty() {
		return top == -1;
	}
private:
	T* data;
	int size;
	int top;

	void isValid() {
		if (data == nullptr)
		{
			cerr << "�ڴ����ʧ��" << endl;
			exit(1);
		}
	}
};

//ListQueue:����ʵ�ֵ�int�Ͷ�����
class Node {
	friend class ListQueue;
public:
	Node(int val) :data(val), next(nullptr) {}
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
	ListQueue() :size(), front(nullptr), rear(nullptr) {}

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
};


static int N, M;//N�����ӵ�,M��������
Vector<int> earliest;//�ڵ�i������¼�������ʱ��
Vector<int> latest;//�ڵ�i������¼�������ʱ��

//DAG�����޻�ͼ,������������(�������л�,��ֱ�����0��return)
//��������
void TopologicalSort(Vector<Vector<Link>>& graph,int* const ind) {
	ListQueue q;//������Ϊ0�Ľڵ�,������������,���������ʱ��
	Stack<int> s;//�����������Ľڵ�,����������������,���������ʱ��
	int nodeNum = 0;//��¼��������Ľڵ���,��������N���л�
	int minimumTime = 0;	
	for (int i = 1; i <= N; i++) {//�����Ϊ0�Ľڵ����
		if (ind[i] == 0) {
			q.push(i);
			earliest[i] = 0;
		}
	}
	while (!q.empty()) {
		int u = q.getFront();
		q.pop();
		s.push(u);//�����Ϊ0�Ľڵ����,����ջ
		nodeNum++;
		for (int i = 0; i < graph[u].size; i++) {
			int v = graph[u][i].to;
			if (v == -1)	continue;
			ind[v]--;
			if (ind[v] == 0) {
				q.push(v);
			}
			int now_cost = earliest[u] + graph[u][i].cost;
			//����v��ʱ��ȡ����ǰ�ù������ʱ��(���ؼ��)
			if(earliest[v] <= now_cost){
				earliest[v] = now_cost;
			}
		}
	}
	if(nodeNum != N){//�л�,�޷����
		cout << "0" << endl;
		return;
	}
	for(int i = 1; i <= N; i++) {
		minimumTime = max(minimumTime, earliest[i]);//�ҵ���������ʱ��(���·����ʱ��)
	}
	cout << minimumTime << endl;
	//������������,���������ʱ��
	s.pop();//ջ��Ԫ�س�ջ
	for(int i = 1; i <= N; i++) {
		latest[i] = minimumTime;//��ʼ��
	}
	while (!s.empty()) {
		int u = s.pop();//ȡջ��Ԫ�ز���ջ
		for (int i = 0; i < graph[u].size; i++) {
			int v = graph[u][i].to;
			if (v == -1)	continue;
			int now_cost = latest[v] - graph[u][i].cost;
			latest[u] = min(latest[u], now_cost);
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = graph[i].size - 1; j >= 0; j--) {//���������ͬʱ��Ҫ������˳�������,���ԴӺ���ǰ����
			int v = graph[i][j].to;
			if (v == -1)	continue;
			int e = earliest[i];
			int l = latest[v] - graph[i][j].cost;
			if (e == l) {//���������ʱ������������ʱ��,˵�������Ƴ����,˵���ǹؼ��
				cout << i << "->" << v << endl;
			}
		}
	}
}

int main() {
	cin >> N >> M;
	Vector<Vector<Link>> graph(N+1);//�ڽӱ�
	earliest.Resize(N + 1);//����ڵ�i������ʱ��
	latest.Resize(N + 1);//����ڵ�i������ʱ��
	int* inDegree = new int[N+1];//���
	for(int i = 0; i <= N; i++) {//��ȳ�ʼ��Ϊ0
		inDegree[i] = 0;
	}
	for (int i = 1; i <= M; i++)	{
		int id1, id2,cst;
		cin >> id1 >> id2 >> cst;
		graph[id1].push_back({ cst,id2 });//id1->id2
		inDegree[id2]++;//id2����ȼ�1
	}
	TopologicalSort(graph,inDegree);
	delete[] inDegree;
	system("pause");
	return 0;
}