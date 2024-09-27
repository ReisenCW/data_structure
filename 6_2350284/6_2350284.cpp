#include <iostream>
using namespace std;
#define DEBUG 0

class FamilyTree;
class FamilyManager;
class String;

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



//利用多叉树存储家谱
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
	FamilyTree& operator=(const FamilyTree& f) {//重载=运算符(深拷贝)
		if (this == &f) {//如果是自己给自己赋值,直接返回
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
		//深拷贝
		if (f.children != nullptr) {
			children = new FamilyTree[childCount];
			for (int i = 0; i < childCount; i++) {
				children[i] = f.children[i];
			}
		}
	}
	
	String GetFather() {
		if (father == nullptr) {
			return String("不在家谱之中");
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
			return String("无子女");
		}
		if(i < 0 || i >= childCount){
			return String("查无此人");
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
		if(childCount > newSize){//如果孩子个数大于新的大小
			childCount = newSize;//令孩子个数等于新的大小,即逻辑上删除多余的孩子
		}
		FamilyTree* temp = new FamilyTree[newSize];//新建一个数组
		for(int i = 0;i < childCount;i++){//将原来的孩子复制到新的数组中
			temp[i] = children[i];
		}
		delete[] children;
		children = temp;
		maxChildCount = newSize;
	}
	void AddChild(const String& name) {
		if(childCount >= maxChildCount){//如果孩子个数超过最大孩子个数
			int newSize = (maxChildCount + 1)*2;
			while (newSize <= childCount) {
				newSize *= 2;
			}
			ResizeChild(newSize);//扩容
		}
		children[childCount++] = FamilyTree(name, this);//添加孩子
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
	FamilyTree* ancestor;//祖先,即家谱的根节点
public:
	FamilyManager(const String& name):ancestor(new FamilyTree(name)){}
	~FamilyManager() {
		if (ancestor != nullptr)
#if DEBUG
			cout << ancestor->name << " deletes ancestor" << endl;
#endif
			delete ancestor;
	}
	FamilyTree* FindMember(const String& targetName, FamilyTree* Node = nullptr) {//dfs查找家庭成员
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
		cout << "请输入要建立家庭的人的姓名: ";
		String fatherName;
		cin >> fatherName;
		FamilyTree* father = FindMember(fatherName);
		if(father == nullptr){
			cout << "查无此人" << endl;
			return;
		}
		if(father->HasChild()){
			cout << fatherName << "已经建立家庭了" << endl;
			return;
		}
		cout << "请输入" << fatherName << "的儿女人数: ";
		int childCnt = 0;
		cin >> childCnt;
		while (childCnt <= 0) {
			cout << "输入错误,请重新输入: ";
			cin.clear();
			cin.ignore(100, '\n');
			cin >> childCnt;
		}
		father->ResizeChild(childCnt);
		cout << "请依次输入" << fatherName << "的儿女姓名: ";
		for (int i = 0; i < childCnt; i++) {
			String temp;
			cin >> temp;
			father->AddChild(temp);
		}
		cout << "添加成功!" << endl;
		cout << fatherName << "的第一代儿女有: ";
		for (int i = 0; i < childCnt; i++) {
			cout << father->GetSon(i) << " ";
		}
		cout << endl;
	}

	void AddFamilyMember() {
		cout << "请输入要添加家庭成员的人的姓名: ";
		String fatherName;
		cin >> fatherName;
		FamilyTree* father = FindMember(fatherName);
		if(father == nullptr){
			cout << "查无此人" << endl;
			return;
		}
		int childCnt = 0;
		cout << "请输入" << fatherName << "要新添加的儿女的个数: ";
		cin >> childCnt;
		while (childCnt <= 0) {
			cout << "输入错误,请重新输入: ";
			cin.clear();
			cin.ignore(100, '\n');
			cin >> childCnt;
		}
		father->ResizeChild(father->ChildCount() + childCnt);
		cout << "请依次输入" << fatherName << "要新添加的儿女的姓名: ";
		for(int i = 0;i < childCnt;i++){
			String temp;
			cin >> temp;
			father->AddChild(temp);
		}
		cout << "添加成功!" << endl;
		cout << fatherName << "的第一代儿女有: ";
		for (int i = 0; i < childCnt; i++) {
			cout << father->GetSon(i) << " ";
		}
		cout << endl;
	}

	void DeleteFamilyMember() {
		cout << "请输入要删除家庭成员的人的姓名: ";
		String fatherName;
		cin >> fatherName;
		FamilyTree* father = FindMember(fatherName);
		if (father == nullptr) {
			cout << "查无此人" << endl;
			return;
		}
		if (!father->HasChild()) {
			cout << fatherName << "没有儿女" << endl;
			return;
		}
		cout << "请输入要删除的儿女的姓名: ";
		String childName;
		cin >> childName;
		FamilyTree* child = FindMember(childName);
		if (child == nullptr) {
			cout << "查无此人" << endl;
			return;
		}
		father->DeleteChild(childName);
		cout << "删除成功!" << endl;
		cout << fatherName << "的第一代儿女有: ";
		for (int i = 0; i < father->ChildCount(); i++) {
			cout << father->GetSon(i) << " ";
		}
		cout << endl;
	}

	void SearchFamilyMember() {
		cout << "请输入要查询家庭成员的人的姓名: ";
		String fatherName;
		cin >> fatherName;
		FamilyTree* father = FindMember(fatherName);
		if (father == nullptr) {
			cout << "查无此人" << endl;
			return;
		}
		if (father->IsAncestor()) {
			cout << fatherName << "是祖先" << endl;
		}
		else {
			cout << fatherName << "的父亲是: " << father->GetFather() << endl;
		}	
		cout << fatherName << "的第一,二代儿女有: " << endl;
		for (int i = 0; i < father->ChildCount(); i++) {
			FamilyTree* child = FindMember(father->GetSon(i));
			cout << "第一代儿女: " << child->GetName();
			if (child->HasChild()) {
				cout << "    此人的儿女: ";
				for (int j = 0; j < child->ChildCount(); j++) {
					cout << child->GetSon(j) << " ";
				}
				cout << endl;
			}
			else {
				cout << "    此人没有儿女" << endl;
				continue;
			}
			//每行输出父亲的儿女及此儿女的儿女
		}
	}

	void ModifyMemberName() {
		cout << "请输入要修改姓名的成员目前的姓名: ";
		String nowName;
		cin >> nowName;
		FamilyTree* member = FindMember(nowName);
		if (member == nullptr) {
			cout << "查无此人" << endl;
			return;
		}
		cout << "请输入新的姓名: ";
		String newName;
		cin >> newName;
		member->ChangeName(newName);
		cout << "修改成功!" << endl;
	}

	void DismissPartialFamily() {
		cout << "请输入要解散家庭的人的姓名: ";
		String fatherName;
		cin >> fatherName;
		FamilyTree* father = FindMember(fatherName);
		if (father == nullptr) {
			cout << "查无此人" << endl;
			return;
		}
		if (!father->HasChild()) {
			cout << fatherName << "此人没有儿女" << endl;
			return;
		}
		father->ResizeChild(0);
		cout << "解散成功!" << endl;
	}
};

void Menu() {
	cout << "**        家谱管理系统        **" << endl
		<< "================================" << endl
		<< "**     请选择要执行的操作:    **" << endl
		<< "**        A--完善家庭         **" << endl
		<< "**        B--添加家庭成员     **" << endl
		<< "**        C--删除家庭成员     **" << endl
		<< "**        D--解散局部家庭     **" << endl
		<< "**        E--更改家庭成员姓名 **" << endl
		<< "**        F--查询家庭成员     **" << endl
		<< "**        G--退出程序         **" << endl;
	cout << "\n首先建立一个家谱" << endl;
	String name;
	cout << "请输入祖先的名字: ";
	cin >> name;
	cout << "此家谱的祖先是: " << name << endl;
	FamilyManager manager(name);
	while (1) {
		cout << endl;
		char choice;
		cout << "请选择要执行的操作: ";
		cin >> choice;
		while (choice > 'G' || choice < 'A') {
			cout << "输入错误,请重新输入: ";
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
			cout << "谢谢使用!" << endl;
			return;
		}
	}
}


int main() {
	Menu();
	system("pause");
	return 0;
}