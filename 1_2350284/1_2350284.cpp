//���Ա���ϵͳ
#include <iostream>
using namespace std;
//����String��
class String {
public:
	char* str;
	int length;
	//�������캯��
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
	//��������
	~String() {
		if (str != nullptr)
			delete[] str;
	}
};

//����==,<<,>>�����
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
//����Student��
class Student {
	friend class Node;
	friend class StudentList;
	int id;//����
	String name;//����
	String gender;//�Ա�
	int age;//����
	String major;//�������
public:
	Student(int id, const String& name, const String& gender, int age, const String& major)
		:id(id), name(name), gender(gender), age(age), major(major) {}//��ʼ���б�
	//��ӡ��Ϣ
	void printInfo() {
		cout << "����:" << id;
		cout << "   \t����:" << name;
		cout << "   \t�Ա�:" << gender;
		cout << "   \t����:" << age;
		cout << "   \t�������:" << major << endl;
	}
};
//����ڵ�
class Node {
	friend class StudentList;
	Student stu;
	Node* next;
	Node* prev;
	Node(int id, const String& name, const String& gender, int age, const String& major) :stu(id, name, gender, age, major), next(nullptr), prev(nullptr) {}
};
//����
class StudentList {
	Node* head;
	Node* tail;
	int size;
public:
	StudentList() :head(nullptr), tail(nullptr) ,size(0){}
	//���ѧ��
	void AddStudent(int id, const String& name, const String& gender, int age, const String& major) {
		if (head == nullptr) {//����Ϊ��
			head = new Node(id, name, gender, age, major);
			tail = head;
		}
		else {//����Ϊ��
			tail->next = new Node(id, name, gender, age, major);
			tail->next->prev = tail;
			tail = tail->next;
		}
		cout << "��ӳɹ�!" << endl;
		size++;
	}
	//����ѧ��
	void InsertStudent(int id, const String& name, const String gender, int age, const String& major, int pos) {
		if (pos < 1 || pos > size + 1) {
			cout << "����λ�ô���!" << endl;
			return;
		}
		Node* temp = head;
		Node* newNode = new Node (id, name,gender ,age ,major);
		if (pos == 1) {//���뵽ͷ�ڵ�
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
			cout << "����ɹ�!" << endl;
			size++;
			return;
		}
		for (int i = 1; i < pos - 1; i++) {
			temp = temp->next;
		}
		newNode->next = temp->next;
		newNode->prev = temp;
		temp->next = newNode;
		if (newNode->next != nullptr) {//������滹�нڵ�
			newNode->next->prev = newNode;
		}
		else {
			tail = newNode;//����û�нڵ�,���½ڵ�Ϊβ�ڵ�
		}
		cout << "����ɹ�!" << endl;
		size++;
	}
	//����ѧ��
	void SearchStudent(int id) {
		Node* temp = head;
		while (temp != nullptr) {
			if (temp->stu.id == id) {
				temp->stu.printInfo();
				return;
			}
			temp = temp->next;
		}
		cout << "δ�ҵ�����!" << endl;
	}
	//ɾ��ѧ��
	void DeleteStudent(int id) {
		Node* temp = head;
		while (temp != nullptr) {
			if (temp->stu.id == id) {
				cout << "��ɾ���Ŀ�����Ϣ��:" << endl;
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
				cout << "ɾ���ɹ�!" << endl;
				size--;
				return;
			}
			else {
				temp = temp->next;
			}
		}
		cout << "δ�ҵ�����!" << endl;
	}
	//�޸�ѧ��
	void ModifyStudent(int id) {
		Node* temp = head;
		while (temp != nullptr) {
			if (temp->stu.id == id) {
				cout << "�������µĿ����Ŀ���,����,�Ա�,����,�������!" << endl;
				cout << "����\t����\t�Ա�\t����\t�������\n";
				int id, age;
				String name;
				String gender;
				String major;
				cin >> id >> name >> gender >> age >> major;
				if (cin.good() && (gender == "��" || gender == "Ů")) {
					temp->stu = Student(id, name, gender, age, major);
					cout << "�޸ĳɹ�!" << endl;
				}
				else
				{
					cout << "��Ч����." << endl;
					cin.clear();
					cin.ignore(1024, '\n');
				}
				return;
			}
			temp = temp->next;
		}
		cout << "δ�ҵ�����!" << endl;
	}
	//��ӡȫ��
	void PrintAll() {
		//��ӡ����
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
	cout << "�����뽨��������Ϣϵͳ!" << endl;
	cout << "�����뿼������:";
	cin >> stuNum;
	cout << "���������뿼���Ŀ���,����,�Ա�,����,�������!" << endl;
	cout << "\t\t����\t����\t�Ա�\t����\t�������\n";
	for (int i = 0; i < stuNum; i++) {
		cout << "��" << i + 1 << "������: \t";
		int id, age;
		String name;
		String major;
		String gender;
		cin >> id >> name >> gender >> age >> major;
		if (cin.good() && (gender == "��" || gender == "Ů")) {
			stuList.AddStudent(id, name, gender, age, major);
		}
		else {
			cout << "�������,����������!" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			i--;
		}
	}
	cout << "�������!" << endl;

	//�˵�
	printf("\n\t1.���뿼����Ϣ\n");
	printf("\t2.ɾ��������Ϣ\n");
	printf("\t3.���ҿ�����Ϣ\n");
	printf("\t4.�޸Ŀ�����Ϣ\n");
	printf("\t5.��ӡȫ��������Ϣ\n");
	printf("\t6.�˳�\n\n");
	enum {
		Insert = 1,
		Delete,
		Search,
		Modify,
		Print,
		Exit
	};
	while (1) {
		cout << "��ѡ����Ҫ���еĲ���:";
		int choice;
		cin >> choice;
		while (!(cin.good() && choice >= Insert && choice <= Exit))
		{
			cout << "�������!����������:" << endl;
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
			cout << "�����뿼���Ŀ���,����,�Ա�,����,�������,����λ��!" << endl;
			while (1) {
				cout << "����\t����\t�Ա�\t����\t�������\t����λ��\n";
				cin >> id >> name >> gender >> age >> major >> pos;
				if (cin.good() && (gender == "��" || gender == "Ů")) {
					stuList.InsertStudent(id, name, gender, age, major,pos);
					break;
				}
				else {
					cout << "�������!����������:" << endl;
					cin.clear();
					cin.ignore(1024, '\n');
				}
			}
			break;
		case Delete:
			cout << "������Ҫɾ���Ŀ����Ŀ���:";
			cin >> id;
			if (cin.good()) {
				stuList.DeleteStudent(id);
			}
			else {
				cout << "�����������!" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
			}
			break;
		case Search:
			cout << "������Ҫ���ҵĿ����Ŀ���:";
			cin >> id;
			if (cin.good())
				stuList.SearchStudent(id);
			else {
				cout << "�����������!" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
			}
			break;
		case Modify:
			cout << "������Ҫ�޸ĵĿ����Ŀ���:";
			cin >> id;
			if (cin.good())
				stuList.ModifyStudent(id);
			else {
				cout << "�����������!" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
			}
			break;
		case Print:
			stuList.PrintAll();
			break;
		case Exit:
			cout << "\n��лʹ�ñ�ϵͳ\n";
			exit(0);
			break;
		}
	}
	return 0;
}