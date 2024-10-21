#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cmath>
#include <limits>
using namespace std;
#define DEBUG 0

//定义String类
class String {
public:
	char* str;
	size_t length;
	//三个构造函数
	String() :length(0), str(nullptr) {}
	String(const char* s):length(0), str(nullptr)
	{
		if (s) {
			length = strlen(s);
			str = new char[length + 1];
			strcpy(str, s);
		}
	}
	String(const String& s) {
		length = s.length;
		str = new char[length + 1];
		for (int i = 0; i < length; i++) {
			str[i] = s.str[i];
		}
		str[length] = '\0';
	}
	//重载=运算符
	String& operator=(const String& s) {
		if (this == &s) {
			return *this;
		}
		if (str != nullptr) {
			delete[] str;
		}
		length = s.length;
		str = new char[length + 1];
		for (int i = 0; i < length; i++) {
			str[i] = s.str[i];
		}
		str[length] = '\0';
		return *this;
	}

	//析构函数
	~String() {
		if (str != nullptr)
			delete[] str;
	}
};

//重载==,<<,>>运算符
bool operator==(const String& s, const char* string) {
	if (s.length < 1) return false;
	int i = 0;
	for (i = 0; i < s.length; i++) {
		if (string[i] == '\0' || s.str[i] != string[i])
			return false;
	}
	if (string[i] != '\0')
		return false;
	return true;
}

bool operator==(const String& s, const String& string) {
	if (s.length < 1 || (s.length != string.length))
		return false;
	for (int i = 0; i < s.length; i++) {
		if (s.str[i] != string.str[i])
			return false;
	}
	return true;
}

ostream& operator<<(ostream& os, const String& s) {
	os << s.str;
	return os;
}

istream& operator>>(istream& is, String& s) {
	char temp[100];
	is >> temp;
	if (is.good()) {
		delete[] s.str;
		s.length = strlen(temp);
		s.str = new char[s.length + 1];
		strcpy(s.str, temp);
	}
	return is;
}

//Vector:动态数组模板类
template <typename T>
class Vector {
private:
	T* data;
public:
	size_t size;//当前元素个数
	size_t capacity;//容量
public:
	Vector(size_t N = 20) :size(0), capacity(N), data(new T[N]) {
		if (data == nullptr) {
			cerr << "内存分配失败" << endl;
			exit(1);
		}
	}

	Vector(size_t N, const T& fill) :size(N), capacity(N), data(new T[N]) {
		if (data == nullptr) {
			cerr << "内存分配失败" << endl;
			exit(1);
		}
		for (size_t i = 0; i < N; i++) {
			data[i] = fill;
		}
	}

	~Vector() {
		if (data != nullptr)
			delete[] data;
	}

	void Resize(size_t newSize) {
		T* temp = new T[newSize];
		if (size > newSize) {
			size = newSize;
		}
		for (size_t i = 0; i < size; i++) {
			temp[i] = data[i];
		}
		delete[] data;
		data = temp;
		capacity = newSize;
	}

	void push_back(const T& x) {
		if (size >= capacity) {
			Resize(capacity << 1);
		}
		data[size++] = x;
	}

	void pop_back() {
		if (size > 0) {
			size--;
		}
	}

	T& operator[](size_t index) {
		if (index < 0 || index >= capacity) {
			throw std::out_of_range("下标越界");
		}
		return data[index];
	}

	size_t GetSize(){
		return size;
	}

	int Erase(size_t index) {
		if (index < 0 || index >= size) {
			return -1;
		}
		for (size_t i = index; i < size - 1; i++) {
			data[i] = data[i + 1];
		}
		size--;
		return 0;
	}

	bool IsEmpty() {
		return size == 0;
	}
};

//使用邻接表的方式存储图
class Node;
class SourceVertex;
class NetWork;


class Node {
	friend class SourceVertex;
	friend class NetWork;
private:
	Node* next;//指向下一个相邻节点
public:
	const String src_name;//起点
	const String dest_name;//当前点
	const int weight;//边的权值
	Node(const String& s, const String& d, int w) :src_name(s), dest_name(d), weight(w), next(nullptr) {}
};

class SourceVertex {
	friend class NetWork;
private:
	Node* head;//指向第一条以该顶点为起点的边
	int m_size;
public:
	String vertex_name;//顶点编号
	SourceVertex() :vertex_name(""), head(nullptr), m_size(0) {};
	SourceVertex(const String& name) : vertex_name(name), head(nullptr), m_size(0) {};
	SourceVertex(const SourceVertex& other);
	//重载=运算符
	SourceVertex& operator=(const SourceVertex& other) 
	{
		if (this == &other) {
			return *this;
		}
		vertex_name = other.vertex_name;
		m_size = other.m_size;
		Node* p = head;
		while (p) {
			Node* q = p->next;
			delete p;
			p = q;
		}
		p = other.head;
		if (p == nullptr) {
			head = nullptr;
			return *this;
		}
		head = new Node(p->src_name, p->dest_name, p->weight);
		Node* q = head;
		p = p->next;
		while (p) {
			q->next = new Node(p->src_name, p->dest_name, p->weight);
			q = q->next;
			p = p->next;
		}
		return *this;
	}
	
	~SourceVertex() {
		Node* p = head;
		while (p) {
			Node* q = p->next;
			delete p;
			p = q;
		}
	}
private:
	//增加一条从该顶点到dest的边
	void AddEdge(const String& dest, int weight);
	//删除该顶点到dest的边
	bool DeleteEdge(const String& dest);
	//判断是否存在从该顶点到dest的边
	bool HasEdge(const String& dest);
};

//拷贝构造函数
SourceVertex::SourceVertex(const SourceVertex& other)
	:vertex_name(other.vertex_name), m_size(other.m_size), head(nullptr)
{
	Node* p = other.head;
	if (p == nullptr) {
		head = nullptr;
		return;
	}
	head = new Node(p->src_name, p->dest_name, p->weight);
	Node* q = head;
	p = p->next;
	while (p) {
		q->next = new Node(p->src_name, p->dest_name, p->weight);
		q = q->next;
		p = p->next;
	}
}

void SourceVertex::AddEdge(const String& dest_name, int weight) {
	m_size++;
	Node* p = head;
	if (p == nullptr) {
		head = new Node(vertex_name, dest_name, weight);
		return;
	}
	while (p->next) {
		p = p->next;
	}
	p->next = new Node(vertex_name, dest_name, weight);
}

//若边不存在则返回false,否则删除并返回true
bool SourceVertex::DeleteEdge(const String& dest_name) {
	Node* p = head;
	if (p == nullptr) {
		return false;
	}
	if (p->dest_name == dest_name) {
		m_size++;
		head = p->next;
		delete p;
		return true;
	}
	while (p->next) {
		if (p->next->dest_name == dest_name) {
			m_size++;
			Node* temp = p->next;
			p->next = p->next->next;
			delete temp;
			return true;
		}
		p = p->next;
	}
	return false;
}

bool SourceVertex::HasEdge(const String& dest_name) {
	Node* p = head;
	while (p) {
		if (p->dest_name == dest_name) {
			return true;
		}
		p = p->next;
	}
	return false;
}

class NetWork {
private:
	int m_vertex;//顶点数
	int m_edge;//边数
	Vector<SourceVertex> vertices;
public:
	void StartSystem();
	NetWork() : m_vertex(0), m_edge(0) {}
private:
	bool IsVertexExist(const String& vertex);
	size_t VertexPos(const String& vertex);
	void AddVertex();
	void AddEdge();
	void DeleteVertex();
	void DeleteEdge();
	void ShowMST();
	void PrintMenu() {
		printf("**          电网造价模拟系统        **\n");
		printf("======================================\n");
		printf("**          A. 创建电网顶点         **\n");
		printf("**          B. 添加电网的边         **\n");
		printf("**          C. 删除电网顶点         **\n");
		printf("**          D. 删除电网的边         **\n");
		printf("**          E. 显示最小生成树       **\n");
		printf("**          F. 退出程序             **\n");
		printf("======================================\n");
	}
	void PrintVertices() {
		for (size_t i = 0; i < vertices.GetSize(); ++i) {
			cout << i + 1 << ". " << vertices[i].vertex_name << endl;
		}
	}
};

//判断顶点是否存在
bool NetWork::IsVertexExist(const String& vertex) {
	for (size_t i = 0; i < vertices.GetSize(); ++i) {
		if (vertices[i].vertex_name == vertex) {
			return true;
		}
	}
	return false;
}

//返回顶点在数组中的位置
size_t NetWork::VertexPos(const String& vertex) {
	for (size_t i = 0; i < vertices.GetSize(); ++i) {
		if (vertices[i].vertex_name == vertex) {
			return i;
		}
	}
	return -1;
}

//添加顶点
void NetWork::AddVertex() {
	cout << "请输入顶点的个数 : ";
	double input = 0;
	cin >> input;
	if (!cin.good() || input <= 0 || floor(input) != input) {
		cout << "输入错误";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
	}
	int num = static_cast<int>(input);
	m_vertex += num;
	cout << "请依次输入各个顶点的名字: " << endl;
	while (num--) {
		String vName;
		cin >> vName;
		if (IsVertexExist(vName)) {
			cout << "该顶点已存在，请重新输入: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			num++;
			continue;
		}
		vertices.push_back(SourceVertex(vName));
	}
#if DEBUG
	PrintVertices();
#endif
}

void NetWork::AddEdge(){
	cout << "请输入要添加的边的个数: ";
	double input = 0;
	cin >> input;
	if (!cin.good() || input <= 0 || floor(input) != input) {
		cout << "输入错误";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
	}
	int num = static_cast<int>(input);
	while (num--) {
		cout << "请输入两个顶点及边的权值: ";
		String vertex_1, vertex_2;
		int weight = 0;
		cin >> vertex_1 >> vertex_2 >> weight;
		//得到顶点在数组中的位置
		size_t v1_position = VertexPos(vertex_1);
		size_t v2_position = VertexPos(vertex_2);
		//判断顶点是否存在
		if (v1_position == -1) {
			cout << "顶点" << vertex_1 << "不存在" << endl;
			num++;
			continue;
		}
		if (v2_position == -1) {
			cout << "顶点" << vertex_2 << "不存在" << endl;
			num++;
			continue;
		}
		//判断边是否已经存在
		if (vertices[v1_position].HasEdge(vertex_2)) {
			cout << "边已存在" << endl;
			num++;
			continue;
		}

		//添加边(因为是无向图所以要互相添加)
		vertices[v1_position].AddEdge(vertex_2, weight);
		vertices[v2_position].AddEdge(vertex_1, weight);
		m_edge++;
	}
}

//删除边
void NetWork::DeleteEdge() {
	cout << "请输入要删除的边的两个顶点: ";
	String vertex_1, vertex_2;
	cin >> vertex_1 >> vertex_2;
	size_t v1_position = VertexPos(vertex_1);
	size_t v2_position = VertexPos(vertex_2);
	if (v1_position == -1 || v2_position == -1) {
		cout << "顶点不存在" << endl;
		return;
	}
	if(vertices[v1_position].DeleteEdge(vertex_2) && vertices[v2_position].DeleteEdge(vertex_1))
		m_edge--;
	cout << "删除成功" << endl;
}

//删除顶点
void NetWork::DeleteVertex() {
	cout << "请输入要删除的顶点的名字: ";
	String vertex;
	cin >> vertex;
	size_t pos = VertexPos(vertex);
	if (pos == -1) {
		cout << "该顶点不存在" << endl;
		return;
	}
	vertices.Erase(pos);
	m_vertex--;
	//删除所有以该顶点为终点的边
	for (size_t i = 0; i < vertices.GetSize(); ++i) {
		if(vertices[i].DeleteEdge(vertex))
			m_edge--;
	}
	cout << "删除成功" << endl;
}
//生成Prim最小生成树
void NetWork::ShowMST() {
	String start;
	cout << "输入最小生成树的起点名称: ";
	cin >> start;
	size_t pos = VertexPos(start);
	if (pos == -1) {
		cout << "该顶点不存在" << endl;
		return;
	}
	cout << "最小生成树为: " << endl;
	//inMST[i]为true表示顶点i已经在最小生成树中
	Vector<bool> inMST(vertices.GetSize(), false);
	//key[i]表示顶点i到最小生成树的最小权值
	Vector<int> key(vertices.GetSize(), INT_MAX);
	//parent[i]表示顶点i的父节点
	Vector<size_t> parent(vertices.GetSize(), -1);
	//存储顺序
	Vector<int> route;
	//起点到自己的权值为0
	key[pos] = 0;

	for (size_t count = 0; count < vertices.GetSize(); ++count) {
		int min = INT_MAX;
		int u = -1;
		//找到key值最小的顶点
		for (int v = 0; v < vertices.GetSize(); ++v) {
			if (vertices[v].head != nullptr && !inMST[v] && key[v] < min) {
				min = key[v];
				u = v;
			}
		}
		// 如果没有找到合适的顶点，跳出循环
		if (u == -1) {
			break;
		}
		//将找到的顶点加入最小生成树
		inMST[u] = true;
		//存储顺序
		route.push_back(u);
		//更新key值
		for (Node* p = vertices[u].head; p; p = p->next) {
			size_t v = VertexPos(p->dest_name);
			if (!inMST[v] && p->weight < key[v]) {
				key[v] = p->weight;
				parent[v] = u;
			}
		}
	}

	for (size_t i = 0; i < route.GetSize(); ++i) {
		int index = route[i];
		if (parent[index] != -1) {
			cout << vertices[parent[index]].vertex_name << " -<" << key[index] << ">- " << vertices[index].vertex_name << endl;
		}
	}
}


void NetWork::StartSystem() {
	PrintMenu();
	while (1) {
		char choice = ' ';
		cout << endl << "请选择操作: ";
		cin >> choice;
		while (choice > 'F' || choice < 'A') {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "输入错误，请重新输入: ";
			cin >> choice;
		}
		switch (choice) {
			cout << endl;
			case 'A':
				AddVertex();
				break;
			case 'B':
				AddEdge();
				break;
			case 'C':
				DeleteVertex();
				break;
			case 'D':
				DeleteEdge();
				break;
			case 'E':
				ShowMST();
				break;
			case 'F':
				cout << "退出程序" << endl;
				return;
			default:
				break;
		}
	}
}

int main() {
	NetWork nw;
	nw.StartSystem();
	return 0;
}

//TEST
/*
A
8
0 1 2 3 4 5 6 7
B
10
0 1 6
0 2 1
0 3 5
1 2 5
2 3 5
1 4 3
2 4 6
2 5 4
3 5 2
4 5 6
*/