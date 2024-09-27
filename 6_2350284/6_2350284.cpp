#include <iostream>
using namespace std;
#define DEBUG 0

class FamilyTree;
class FamilyManager;
class String;

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
	//����=�����
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



//���ö�����洢����
class FamilyTree {
	friend class FamilyManager;
private:
	FamilyTree* father;
	FamilyTree* children;
	String name;
	int childCount;
	int maxChildCount;
public:
	FamilyTree(const String& name = "", FamilyTree* father = nullptr) :name(name), father(father), childCount(0),maxChildCount(0),children(nullptr) {}
	FamilyTree& operator=(const FamilyTree& f) {//����=�����(���)
		if (this == &f) {//������Լ����Լ���ֵ,ֱ�ӷ���
			return *this;
		}
		name = f.name;
		father = f.father;
		childCount = f.childCount;
		maxChildCount = f.maxChildCount;
		if (children != nullptr) {
			delete[] children;
		}
		if (f.children != nullptr) {
			children = new FamilyTree[childCount];
			for (int i = 0; i < childCount; i++) {
				children[i] = f.children[i];
			}
		}
		return *this;
	}
	FamilyTree(const FamilyTree& f) :name(f.name), father(father), maxChildCount(f.maxChildCount),childCount(f.childCount), children(nullptr) {
		//���
		if (f.children != nullptr) {
			children = new FamilyTree[childCount];
			for (int i = 0; i < childCount; i++) {
				children[i] = f.children[i];
			}
		}
	}
	
	String GetFather() {
		if (father == nullptr) {
			return String("���ڼ���֮��");
		}
		return father->name;
	}

	int ChildCount() {
		return childCount;
	}

	String GetName() {
		return name;
	}

	void ChangeName(const String& newName) {
		name = newName;
	}

	String GetSon(int i=0) {
		if(childCount == 0){
			return String("����Ů");
		}
		if(i < 0 || i >= childCount){
			return String("���޴���");
		}
		return children[i].name;
	}

	bool HasChild() {
		return childCount > 0;
	}

	bool IsAncestor() {
		return (father == nullptr);
	}

	void ResizeChild(int newSize) {
		if(childCount > newSize){//������Ӹ��������µĴ�С
			childCount = newSize;//��Ӹ��������µĴ�С,���߼���ɾ������ĺ���
		}
		FamilyTree* temp = new FamilyTree[newSize];//�½�һ������
		for(int i = 0;i < childCount;i++){//��ԭ���ĺ��Ӹ��Ƶ��µ�������
			temp[i] = children[i];
		}
		delete[] children;
		children = temp;
		maxChildCount = newSize;
	}
	void AddChild(const String& name) {
		if(childCount >= maxChildCount){//������Ӹ�����������Ӹ���
			int newSize = (maxChildCount + 1)*2;
			while (newSize <= childCount) {
				newSize *= 2;
			}
			ResizeChild(newSize);//����
		}
		children[childCount++] = FamilyTree(name, this);//��Ӻ���
	}

	void DeleteChild(const String& name) {
		for(int i = 0;i < childCount;i++){
			if(children[i].name == name){
				for(int j = i;j < childCount - 1;j++){
					children[j] = children[j + 1];
				}
				childCount--;
				return;
			}
		}
	}
	~FamilyTree() {
		if (children != nullptr)
#if DEBUG
			cout << name << " deletes children" << endl;
#endif
		delete[] children;
	}
};

class FamilyManager {
private:
	FamilyTree* ancestor;//����,�����׵ĸ��ڵ�
public:
	FamilyManager(const String& name):ancestor(new FamilyTree(name)){}
	~FamilyManager() {
		if (ancestor != nullptr)
#if DEBUG
			cout << ancestor->name << " deletes ancestor" << endl;
#endif
			delete ancestor;
	}
	FamilyTree* FindMember(const String& targetName, FamilyTree* Node = nullptr) {//dfs���Ҽ�ͥ��Ա
		if (Node == nullptr) {
			Node = ancestor;
		}
		if (Node->name == targetName) {
			return Node;
		}
		while (Node != nullptr) {
			for (int i = 0; i < Node->childCount; i++) {
				FamilyTree* temp = FindMember(targetName, &Node->children[i]);
				if (temp != nullptr) {
					return temp;
				}
			}
			return nullptr;
		}
		return nullptr;
	}

	void BuildFamily() {
		cout << "������Ҫ������ͥ���˵�����: ";
		String fatherName;
		cin >> fatherName;
		FamilyTree* father = FindMember(fatherName);
		if(father == nullptr){
			cout << "���޴���" << endl;
			return;
		}
		if(father->HasChild()){
			cout << fatherName << "�Ѿ�������ͥ��" << endl;
			return;
		}
		cout << "������" << fatherName << "�Ķ�Ů����: ";
		int childCnt = 0;
		cin >> childCnt;
		while (childCnt <= 0) {
			cout << "�������,����������: ";
			cin.clear();
			cin.ignore(100, '\n');
			cin >> childCnt;
		}
		father->ResizeChild(childCnt);
		cout << "����������" << fatherName << "�Ķ�Ů����: ";
		for (int i = 0; i < childCnt; i++) {
			String temp;
			cin >> temp;
			father->AddChild(temp);
		}
		cout << "��ӳɹ�!" << endl;
		cout << fatherName << "�ĵ�һ����Ů��: ";
		for (int i = 0; i < childCnt; i++) {
			cout << father->GetSon(i) << " ";
		}
		cout << endl;
	}

	void AddFamilyMember() {
		cout << "������Ҫ��Ӽ�ͥ��Ա���˵�����: ";
		String fatherName;
		cin >> fatherName;
		FamilyTree* father = FindMember(fatherName);
		if(father == nullptr){
			cout << "���޴���" << endl;
			return;
		}
		int childCnt = 0;
		cout << "������" << fatherName << "Ҫ����ӵĶ�Ů�ĸ���: ";
		cin >> childCnt;
		while (childCnt <= 0) {
			cout << "�������,����������: ";
			cin.clear();
			cin.ignore(100, '\n');
			cin >> childCnt;
		}
		father->ResizeChild(father->ChildCount() + childCnt);
		cout << "����������" << fatherName << "Ҫ����ӵĶ�Ů������: ";
		for(int i = 0;i < childCnt;i++){
			String temp;
			cin >> temp;
			father->AddChild(temp);
		}
		cout << "��ӳɹ�!" << endl;
		cout << fatherName << "�ĵ�һ����Ů��: ";
		for (int i = 0; i < childCnt; i++) {
			cout << father->GetSon(i) << " ";
		}
		cout << endl;
	}

	void DeleteFamilyMember() {
		cout << "������Ҫɾ����ͥ��Ա���˵�����: ";
		String fatherName;
		cin >> fatherName;
		FamilyTree* father = FindMember(fatherName);
		if (father == nullptr) {
			cout << "���޴���" << endl;
			return;
		}
		if (!father->HasChild()) {
			cout << fatherName << "û�ж�Ů" << endl;
			return;
		}
		cout << "������Ҫɾ���Ķ�Ů������: ";
		String childName;
		cin >> childName;
		FamilyTree* child = FindMember(childName);
		if (child == nullptr) {
			cout << "���޴���" << endl;
			return;
		}
		father->DeleteChild(childName);
		cout << "ɾ���ɹ�!" << endl;
		cout << fatherName << "�ĵ�һ����Ů��: ";
		for (int i = 0; i < father->ChildCount(); i++) {
			cout << father->GetSon(i) << " ";
		}
		cout << endl;
	}

	void SearchFamilyMember() {
		cout << "������Ҫ��ѯ��ͥ��Ա���˵�����: ";
		String fatherName;
		cin >> fatherName;
		FamilyTree* father = FindMember(fatherName);
		if (father == nullptr) {
			cout << "���޴���" << endl;
			return;
		}
		if (father->IsAncestor()) {
			cout << fatherName << "������" << endl;
		}
		else {
			cout << fatherName << "�ĸ�����: " << father->GetFather() << endl;
		}	
		cout << fatherName << "�ĵ�һ,������Ů��: " << endl;
		for (int i = 0; i < father->ChildCount(); i++) {
			FamilyTree* child = FindMember(father->GetSon(i));
			cout << "��һ����Ů: " << child->GetName();
			if (child->HasChild()) {
				cout << "    ���˵Ķ�Ů: ";
				for (int j = 0; j < child->ChildCount(); j++) {
					cout << child->GetSon(j) << " ";
				}
				cout << endl;
			}
			else {
				cout << "    ����û�ж�Ů" << endl;
				continue;
			}
			//ÿ��������׵Ķ�Ů���˶�Ů�Ķ�Ů
		}
	}

	void ModifyMemberName() {
		cout << "������Ҫ�޸������ĳ�ԱĿǰ������: ";
		String nowName;
		cin >> nowName;
		FamilyTree* member = FindMember(nowName);
		if (member == nullptr) {
			cout << "���޴���" << endl;
			return;
		}
		cout << "�������µ�����: ";
		String newName;
		cin >> newName;
		member->ChangeName(newName);
		cout << "�޸ĳɹ�!" << endl;
	}

	void DismissPartialFamily() {
		cout << "������Ҫ��ɢ��ͥ���˵�����: ";
		String fatherName;
		cin >> fatherName;
		FamilyTree* father = FindMember(fatherName);
		if (father == nullptr) {
			cout << "���޴���" << endl;
			return;
		}
		if (!father->HasChild()) {
			cout << fatherName << "����û�ж�Ů" << endl;
			return;
		}
		father->ResizeChild(0);
		cout << "��ɢ�ɹ�!" << endl;
	}
};

void Menu() {
	cout << "**        ���׹���ϵͳ        **" << endl
		<< "================================" << endl
		<< "**     ��ѡ��Ҫִ�еĲ���:    **" << endl
		<< "**        A--���Ƽ�ͥ         **" << endl
		<< "**        B--��Ӽ�ͥ��Ա     **" << endl
		<< "**        C--ɾ����ͥ��Ա     **" << endl
		<< "**        D--��ɢ�ֲ���ͥ     **" << endl
		<< "**        E--���ļ�ͥ��Ա���� **" << endl
		<< "**        F--��ѯ��ͥ��Ա     **" << endl
		<< "**        G--�˳�����         **" << endl;
	cout << "\n���Ƚ���һ������" << endl;
	String name;
	cout << "���������ȵ�����: ";
	cin >> name;
	cout << "�˼��׵�������: " << name << endl;
	FamilyManager manager(name);
	while (1) {
		cout << endl;
		char choice;
		cout << "��ѡ��Ҫִ�еĲ���: ";
		cin >> choice;
		while (choice > 'G' || choice < 'A') {
			cout << "�������,����������: ";
			cin.clear();
			cin.ignore(100, '\n');
			cin >> choice;
		}
		switch (choice) {
		case 'A':
			manager.BuildFamily();
			break;
		case 'B':
			manager.AddFamilyMember();
			break;
		case 'C':
			manager.DeleteFamilyMember();
			break;
		case 'D':
			manager.DismissPartialFamily();
			break;
		case 'E':
			manager.ModifyMemberName();
			break;
		case 'F':
			manager.SearchFamilyMember();
			break;
		case 'G':
			cout << "ллʹ��!" << endl;
			return;
		}
	}
}


int main() {
	Menu();
	system("pause");
	return 0;
}