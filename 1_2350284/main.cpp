//考试报名系统
#include <iostream>
using namespace std;
//定义String类
class String {
public:
	char* str;
	int length;
	//三个构造函数
	String() :length(0), str(nullptr) {}
	String(const char* s) {
		for (int i = 0; s[i] != '\0'; i++) {
			length++;
		}
		str = new char[length + 1];
		for (int i = 0; i < length; i++) {
			str[i] = s[i];
		}
		str[length] = '\0';
	}
	String(const String& s) {
		length = s.length;
		str = new char[length + 1];
		for (int i = 0; i < length; i++) {
			str[i] = s.str[i];
		}
		str[length] = '\0';
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
		s.length = 0;
		for (int i = 0; temp[i] != '\0'; i++) {
			s.length++;
		}
		s.str = new char[s.length + 1];
		for (int i = 0; i < s.length; i++) {
			s.str[i] = temp[i];
		}
		s.str[s.length] = '\0';
	}
	return is;
}

class Student;
class Node;
class StudentList;
//定义Student类
class Student {
	friend class Node;
	friend class StudentList;
	int id;//考号
	String name;//姓名
	String gender;//性别
	int age;//年龄
	String major;//报考类别
public:
	Student(int id, const String& name, const String& gender, int age, const String& major)
		:id(id), name(name), gender(gender), age(age), major(major) {}//初始化列表
	//打印信息
	void printInfo() {
		cout << "考号:" << id;
		cout << "   \t姓名:" << name;
		cout << "   \t性别:" << gender;
		cout << "   \t年龄:" << age;
		cout << "   \t报考类别:" << major << endl;
	}
};
//链表节点
class Node {
	friend class StudentList;
	Student stu;
	Node* next;
	Node* prev;
	Node(int id, const String& name, const String& gender, int age, const String& major) :stu(id, name, gender, age, major), next(nullptr), prev(nullptr) {}
};
//链表
class StudentList {
	Node* head;
	Node* tail;
	int size;
public:
	StudentList() :head(nullptr), tail(nullptr) ,size(0){}
	//添加学生
	void AddStudent(int id, const String& name, const String& gender, int age, const String& major) {
		if (head == nullptr) {//链表为空
			head = new Node(id, name, gender, age, major);
			tail = head;
		}
		else {//链表不为空
			tail->next = new Node(id, name, gender, age, major);
			tail->next->prev = tail;
			tail = tail->next;
		}
		cout << "添加成功!" << endl;
		size++;
	}
	//插入学生
	void InsertStudent(int id, const String& name, const String gender, int age, const String& major, int pos) {
		if (pos < 1 || pos > size + 1) {
			cout << "插入位置错误!" << endl;
			return;
		}
		Node* temp = head;
		Node* newNode = new Node (id, name,gender ,age ,major);
		if (pos == 1) {//插入到头节点
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
			cout << "插入成功!" << endl;
			size++;
			return;
		}
		for (int i = 1; i < pos - 1; i++) {
			temp = temp->next;
		}
		newNode->next = temp->next;
		newNode->prev = temp;
		temp->next = newNode;
		if (newNode->next != nullptr) {//如果后面还有节点
			newNode->next->prev = newNode;
		}
		else {
			tail = newNode;//后面没有节点,则新节点为尾节点
		}
		cout << "插入成功!" << endl;
		size++;
	}
	//查找学生
	void SearchStudent(int id) {
		Node* temp = head;
		while (temp != nullptr) {
			if (temp->stu.id == id) {
				temp->stu.printInfo();
				return;
			}
			temp = temp->next;
		}
		cout << "未找到考生!" << endl;
	}
	//删除学生
	void DeleteStudent(int id) {
		Node* temp = head;
		while (temp != nullptr) {
			if (temp->stu.id == id) {
				cout << "你删除的考生信息是:" << endl;
				temp->stu.printInfo();
				if (temp->prev != nullptr) {
					temp->prev->next = temp->next;
				}
				else {
					head = temp->next;
					head->prev = nullptr;
				}
				if (temp->next != nullptr) {
					temp->next->prev = temp->prev;
				}
				else {
					tail = temp->prev;
					tail->next = nullptr;
				}
				delete temp;
				cout << "删除成功!" << endl;
				size--;
				return;
			}
			else {
				temp = temp->next;
			}
		}
		cout << "未找到考生!" << endl;
	}
	//修改学生
	void ModifyStudent(int id) {
		Node* temp = head;
		while (temp != nullptr) {
			if (temp->stu.id == id) {
				cout << "请输入新的考生的考号,姓名,性别,年龄,报考类别!" << endl;
				cout << "考号\t姓名\t性别\t年龄\t报考类别\n";
				int id, age;
				String name;
				String gender;
				String major;
				cin >> id >> name >> gender >> age >> major;
				if (cin.good() && (gender == "男" || gender == "女")) {
					temp->stu = Student(id, name, gender, age, major);
					cout << "修改成功!" << endl;
				}
				else
				{
					cout << "无效输入." << endl;
					cin.clear();
					cin.ignore(1024, '\n');
				}
				return;
			}
			temp = temp->next;
		}
		cout << "未找到考生!" << endl;
	}
	//打印全部
	void PrintAll() {
		//打印内容
		Node* temp = head;
		while (temp != nullptr) {
			temp->stu.printInfo();
			temp = temp->next;
		}
	}

	~StudentList() {
		Node* temp = head;
		while (temp != nullptr) {
			Node* next = temp->next;
			delete temp;
			temp = next;
		}
	}
};

int main() {
	int stuNum = 0;
	StudentList stuList;
	cout << "首先请建立考生信息系统!" << endl;
	cout << "请输入考生人数:";
	cin >> stuNum;
	cout << "请依次输入考生的考号,姓名,性别,年龄,报考类别!" << endl;
	cout << "\t\t考号\t姓名\t性别\t年龄\t报考类别\n";
	for (int i = 0; i < stuNum; i++) {
		cout << "第" << i + 1 << "个考生: \t";
		int id, age;
		String name;
		String major;
		String gender;
		cin >> id >> name >> gender >> age >> major;
		if (cin.good() && (gender == "男" || gender == "女")) {
			stuList.AddStudent(id, name, gender, age, major);
		}
		else {
			cout << "输入错误,请重新输入!" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			i--;
		}
	}
	cout << "建立完成!" << endl;

	//菜单
	printf("\n\t1.插入考生信息\n");
	printf("\t2.删除考生信息\n");
	printf("\t3.查找考生信息\n");
	printf("\t4.修改考生信息\n");
	printf("\t5.打印全部考生信息\n");
	printf("\t6.退出\n\n");
	enum {
		Insert = 1,
		Delete,
		Search,
		Modify,
		Print,
		Exit
	};
	while (1) {
		cout << "请选择你要进行的操作:";
		int choice;
		cin >> choice;
		while (!(cin.good() && choice >= Insert && choice <= Exit))
		{
			cout << "输入错误!请重新输入:" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			cin >> choice;
		}
		int id, age, pos;
		String name;
		String major;
		String gender;
		switch (choice) {
		case Insert:
			cout << "请输入考生的考号,姓名,性别,年龄,报考类别,插入位置!" << endl;
			while (1) {
				cout << "考号\t姓名\t性别\t年龄\t报考类别\t插入位置\n";
				cin >> id >> name >> gender >> age >> major >> pos;
				if (cin.good() && (gender == "男" || gender == "女")) {
					stuList.InsertStudent(id, name, gender, age, major,pos);
					break;
				}
				else {
					cout << "输入错误!请重新输入:" << endl;
					cin.clear();
					cin.ignore(1024, '\n');
				}
			}
			break;
		case Delete:
			cout << "请输入要删除的考生的考号:";
			cin >> id;
			if (cin.good()) {
				stuList.DeleteStudent(id);
			}
			else {
				cout << "考号输入错误!" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
			}
			break;
		case Search:
			cout << "请输入要查找的考生的考号:";
			cin >> id;
			if (cin.good())
				stuList.SearchStudent(id);
			else {
				cout << "考号输入错误!" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
			}
			break;
		case Modify:
			cout << "请输入要修改的考生的考号:";
			cin >> id;
			if (cin.good())
				stuList.ModifyStudent(id);
			else {
				cout << "考号输入错误!" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
			}
			break;
		case Print:
			stuList.PrintAll();
			break;
		case Exit:
			cout << "\n感谢使用本系统\n";
			exit(0);
			break;
		}
	}
	return 0;
}