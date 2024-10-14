#include <iostream>
#include <iomanip>
using namespace std;

// 定义一个坐标点结构体
struct Point {
	int x; // x坐标
	int y; // y坐标
	Point(int x, int y) :x(x), y(y) {}
};

// 定义一个节点类
class Node {
	friend class Route;
	Node* next; // 下一个节点指针
	const Point data; // 数据
	Node(const Point& p) :data(p), next(nullptr) {}
};

//以链表形式定义一个路径类
class Route {
private:
	Node* head; // 头节点指针
	Node* tail; // 尾节点指针
public:
	Route() :head(nullptr), tail(nullptr) {}
	~Route() {
		while (head != nullptr) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}
	void push(const Point& p); // 入栈
	void pop(); // 出栈
	void print(); // 打印路径
	char** newMap(char** map); // 生成新地图
};

// 入栈
void Route::push(const Point& p) {
	Node* temp = new Node(p);
	if (temp == nullptr) {
		cerr << "内存分配失败" << endl;
		exit(1);
	}
	if (head == nullptr) {
		head = temp;
		tail = temp;
		return;
	}
	tail->next = temp;
	tail = temp;
}

// 出栈
void Route::pop() {
	if (head == nullptr) {
		cerr << "栈为空" << endl;
		exit(1);
	}
	if (head == tail) {
		delete head;
		head = nullptr;
		tail = nullptr;
		return;
	}
	Node* temp = head;
	while (temp->next != tail) {
		temp = temp->next;
	}
	delete tail;
	tail = temp;
	tail->next = nullptr;
}

// 打印路径
void Route::print() {
	Node* temp = head;
	while (temp != nullptr) {
		cout << "<" << temp->data.x << "," << temp->data.y << ">";
		temp = temp->next;
		if (temp != nullptr) {
			cout << " ---> ";
		}
	}
	cout << endl;
}

// 生成新地图
char** Route::newMap(char** map) {
	Node* temp = head;
	while (temp != nullptr) {
		map[temp->data.x][temp->data.y] = 'x';
		temp = temp->next;
	}
	return map;
}

// 定义一个迷宫类
class Labyrinth {
private:
	const char** map; // 迷宫地图
	const int row; // 行数
	const int col; // 列数
    Point start; // 起点坐标
	Point destination; // 终点坐标
    bool inBoundary(int x, int y); // 判断坐标是否在边界内
	void dfs(int x, int y, Route& route, bool visited[7][7]); // 深度优先搜索
public:
    Labyrinth(const char** map, int row, int col, const Point& st, const Point& dst)
        : map(map), row(row), col(col), start(st), destination(dst){}
	void PrintMap(); // 打印原迷宫地图
	void PrintMap(const char** map); // 打印找出了路径的迷宫地图
	void FindPath(); // 找到一条路径
};

// 打印迷宫地图
void Labyrinth::PrintMap()
{
	PrintMap(this->map);
}

// 打印迷宫地图
void Labyrinth::PrintMap(const char** map)
{
	printf("迷宫地图:\n\n   \t");
	for (int i = 0; i < this->col; ++i) {
		printf("%d列\t", i);
	}
	cout << endl;
	for (int i = 0; i < this->row; ++i) {
		printf("%d行\t", i);
		for (int j = 0; j < this->col; ++j) {
			if (map[i][j] == 'x')
				//利用ANSI控制码设置颜色,输出路径
				printf("\033[33m%c\033[0m\t", map[i][j]);
			else if (map[i][j] == '#')
				printf("\033[31m%c\033[0m\t", map[i][j]);
			else
				printf("\033[32m%c\033[0m\t", map[i][j]);
		}
		printf("\n\n");
	}
}

// 判断坐标是否在边界内
bool Labyrinth::inBoundary(int x, int y) {
	return x >= 0 && x < this->row && y >= 0 && y < this->col;
}

// 深度优先搜索
void Labyrinth::dfs(int x, int y, Route& route, bool visited[7][7]) {
	route.push(Point(x, y));
	if (x == this->destination.x && y == this->destination.y) {
		route.print();
		cout << endl;
		cout << "迷宫路径图:(x表示路径): " << endl << endl;
		// 复制地图
		char** newMap = new char*[this->row];
		for (int i = 0; i < this->row; ++i) {
			newMap[i] = new char[this->col];
			for (int j = 0; j < this->col; ++j) {
				newMap[i][j] = this->map[i][j];
			}
		}
		// 将复制的地图修改成含有路径的地图
		route.newMap(newMap);
		// 打印地图
		PrintMap((const char**)newMap);
		// 释放内存
		for (int i = 0; i < this->row; ++i) {
			delete[] newMap[i];
		}
		route.pop();
		delete[] newMap;
		return;
	}
	visited[x][y] = true;
	int dir[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
	for (int i = 0; i < 4; ++i) {
		int nx = x + dir[i][0];
		int ny = y + dir[i][1];
		if (inBoundary(nx, ny) && this->map[nx][ny] == '0' && !visited[nx][ny]) {
			dfs(nx, ny, route, visited);
		}
	}
	route.pop();
	visited[x][y] = false;
}

// 找一条路径
void Labyrinth::FindPath(){
    Route route;
	bool visited[7][7] = { false };
	cout << "从 <" << start.x << "," << start.y << "> 到 <" << destination.x << "," << destination.y << "> 的迷宫路径为: " << endl << endl;
	dfs(start.x, start.y, route, visited);
	cout << endl << endl;
}

int main(){

	//const char* map[] = {
	//	"#######",
	//	"#0#000#",
	//	"#0#0###",
	//	"#000#0#",
	//	"#0#000#",
	//	"#0#0#0#",
	//	"#######"
	//};

	const char* map[] = {
		"#######",
		"#00000#",
		"#0#0#0#",
		"#000#0#",
		"#0#000#",
		"#0#0#0#",
		"#######"
	};

	Labyrinth lb(map, 7, 7, Point(1,1), Point(5,5));
	lb.PrintMap();
	lb.FindPath();

	return 0;
}