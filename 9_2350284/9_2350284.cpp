#include <iostream>
using namespace std;

struct Link;
class ListQueue;
class Node;

//Link:邻接表中的节点
struct Link{
	int cost = 0;//子任务所需时间
	int to = -1;//完成该节点后可以前往的下一个节点
};

//Vector:动态数组模板类
template <typename T>
class Vector {
private:
	T* data;
public:
	int size;//当前元素个数
	int capacity;//容量
public:
	Vector(int N = 20) :size(0), capacity(N), data(new T[N]) {
		if (data == nullptr) {
			cerr << "内存分配失败" << endl;
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
			cerr << "下标越界" << endl;
			exit(1);
		}
		if(index >= size){
			size = index+1;
		}
		return data[index];
	}
};

//Stack:栈的模板类
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
		//如果栈满了,则重新分配空间
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
		//入栈
		data[++top] = x;
	}
	T pop() {
		if (top == -1)
		{
			cerr << "栈为空" << endl;
			exit(1);
		}
		return data[top--];
	}
	T getTop() {
		if (top == -1)
		{
			cerr << "栈为空" << endl;
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
			cerr << "内存分配失败" << endl;
			exit(1);
		}
	}
};

//ListQueue:链表实现的int型队列类
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
};


static int N, M;//N个交接点,M个子任务
Vector<int> earliest;//节点i代表的事件的最早时间
Vector<int> latest;//节点i代表的事件的最晚时间

//DAG有向无环图,利用拓扑排序(若发现有环,则直接输出0并return)
//拓扑排序
void TopologicalSort(Vector<Vector<Link>>& graph,int* const ind) {
	ListQueue q;//存放入度为0的节点,用于拓扑排序,求最早完成时间
	Stack<int> s;//存放拓扑排序的节点,用于逆向拓扑排序,求最晚完成时间
	int nodeNum = 0;//记录拓扑排序的节点数,若不等于N则有环
	int minimumTime = 0;	
	for (int i = 1; i <= N; i++) {//将入度为0的节点入队
		if (ind[i] == 0) {
			q.push(i);
			earliest[i] = 0;
		}
	}
	while (!q.empty()) {
		int u = q.getFront();
		q.pop();
		s.push(u);//将入度为0的节点出队,并入栈
		nodeNum++;
		for (int i = 0; i < graph[u].size; i++) {
			int v = graph[u][i].to;
			if (v == -1)	continue;
			ind[v]--;
			if (ind[v] == 0) {
				q.push(v);
			}
			int now_cost = earliest[u] + graph[u][i].cost;
			//到达v的时间取决于前置工作的最长时间(即关键活动)
			if(earliest[v] <= now_cost){
				earliest[v] = now_cost;
			}
		}
	}
	if(nodeNum != N){//有环,无法完成
		cout << "0" << endl;
		return;
	}
	for(int i = 1; i <= N; i++) {
		minimumTime = max(minimumTime, earliest[i]);//找到最短总完成时间(即最长路径的时间)
	}
	cout << minimumTime << endl;
	//逆向拓扑排序,求最晚完成时间
	s.pop();//栈顶元素出栈
	for(int i = 1; i <= N; i++) {
		latest[i] = minimumTime;//初始化
	}
	while (!s.empty()) {
		int u = s.pop();//取栈顶元素并出栈
		for (int i = 0; i < graph[u].size; i++) {
			int v = graph[u][i].to;
			if (v == -1)	continue;
			int now_cost = latest[v] - graph[u][i].cost;
			latest[u] = min(latest[u], now_cost);
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = graph[i].size - 1; j >= 0; j--) {//由于起点相同时需要按输入顺序反向输出,所以从后往前遍历
			int v = graph[i][j].to;
			if (v == -1)	continue;
			int e = earliest[i];
			int l = latest[v] - graph[i][j].cost;
			if (e == l) {//若最早完成时间等于最晚完成时间,说明不能推迟完成,说明是关键活动
				cout << i << "->" << v << endl;
			}
		}
	}
}

int main() {
	cin >> N >> M;
	Vector<Vector<Link>> graph(N+1);//邻接表
	earliest.Resize(N + 1);//到达节点i的最早时间
	latest.Resize(N + 1);//到达节点i的最晚时间
	int* inDegree = new int[N+1];//入度
	for(int i = 0; i <= N; i++) {//入度初始化为0
		inDegree[i] = 0;
	}
	for (int i = 1; i <= M; i++)	{
		int id1, id2,cst;
		cin >> id1 >> id2 >> cst;
		graph[id1].push_back({ cst,id2 });//id1->id2
		inDegree[id2]++;//id2的入度加1
	}
	TopologicalSort(graph,inDegree);
	delete[] inDegree;
	system("pause");
	return 0;
}