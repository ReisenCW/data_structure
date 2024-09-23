//���ʽת��
#include <iostream>
using namespace std;

//ջ��ģ����
template <typename T>
class Stack {
public:
    Stack(int size = 100) : data(nullptr),size(size), top(-1) {
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
        if(top == -1)
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

//����
//�ж��ַ��Ƿ�������
bool isNumber(char c) {
    return c >= '0' && c <= '9';
}
//�ж��ַ��Ƿ��������
bool isOper(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}
//
int priority(char c) {
    if(c == '(' || c == ')')
        return 0;
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    return -1;
}
//������������м���
int calculate(int a, int b, char oper) {
    switch (oper) {
    case '+':
        return a + b;
    case '-':
        return a - b; 
    case '*':
        return a * b;
    case '/':
        return a / b;
    }
    return 0;
}

int main() {
    //������һ���и����Կո�ָ���ͬ�������׺���ʽ���ɰ���+, -, *, /,�Լ��������ţ����ʽ������20���ַ�
    //��һ�������ת����ĺ�׺���ʽ��Ҫ��ͬ������������������ţ�֮���Կո�ָ������ǽ�β�����ж���ո�
    char* str = new char[60];//�洢��׺���ʽ
    char answer[60];//�洢��׺���ʽ
    cin.getline(str, 60);//����
    Stack<char> oper(60);//�洢�������ջ
    int index = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if(isNumber(str[i]) || str[i] == '.') {//��������ֻ�С����,ֱ�ӷ���answer��
            while(isNumber(str[i]) || str[i] == '.') {//һֱ��ȡ���ֻ�С����,ֱ������������(������ȷʱӦΪ�ո�)
                answer[index++] = str[i++];
            }
            answer[index++] = ' ';//��һ���ո�
            i--;//��Ϊforѭ������i++,��������Ҫ����һ���ַ�
        }
        else if (str[i] == '(') {//�����'(',ֱ����ջ
            oper.push(str[i]);
        }
        else if (str[i] == ')') {//�����')',�����ε���ջ�е�Ԫ�ؼ���answer,ֱ������'('
            while (oper.getTop() != '(') {
                answer[index++] = oper.pop();
                answer[index++] = ' ';
            }
            oper.pop();//����'('
        }
        else if (isOper(str[i])) {//����������
            if (i == 0 || (!isNumber(str[i - 2]) && str[i-2] != ')')) {//����ǵ�һ���ַ�,����ǰһ���ַ���������,��˵���Ǹ���
                if (str[i] == '-') {//����Ǹ���,�����answer
                    answer[index++] = '-';
                }
                else if (str[i] != '+') {//���������,�����,���������ŵ����,����ʽ����
                    cerr << "���ʽ����" << endl;
                    exit(1);
                }
                continue;//��������,������һ��ѭ��
            }
            while (!oper.empty() && priority(oper.getTop()) >= priority(str[i])) {
                //���ջ��Ϊ��,��ջ��Ԫ�ص����ȼ����ڵ��ڵ�ǰԪ��,�򵯳�ջ��Ԫ�ؼ���answer
                answer[index++] = oper.pop();
                answer[index++] = ' ';
            }
            oper.push(str[i]);//��ǰ�������ջ
        }
    }
    //��ջ��ʣ���Ԫ�ؼ���answer
    while (!oper.empty()) {
        answer[index++] = oper.pop();
        answer[index++] = ' ';
    }
    //ȥ����β����Ŀո�
    while(index > 0 && answer[index-1] == ' ') {
		index--;
	}
    answer[index] = '\0';
    cout << answer;
    

    return 0;
}

/*��������
����															���
2 + 3 * ( 7 - 4 ) + 8 / 4							2 3 7 4 - * + 8 4 / +
( ( 2 + 3) * 4 - ( 8 + 2 ) ) / 5					2 3 + 4 * 8 2 + - 5 /
1314 + 25.5 * 12									1314 25.5 12 * +
-2 * ( +3 )											-2 3 *
123													123
*/