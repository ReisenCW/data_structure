//表达式转换
#include <iostream>
using namespace std;

//栈的模板类
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
        if(top == -1)
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

//函数
//判断字符是否是数字
bool isNumber(char c) {
    return c >= '0' && c <= '9';
}
//判断字符是否是运算符
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
//根据运算符进行计算
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
    //输入在一行中给出以空格分隔不同对象的中缀表达式，可包含+, -, *, /,以及左右括号，表达式不超过20个字符
    //在一行中输出转换后的后缀表达式，要求不同对象（运算数，运算符号）之间以空格分隔，但是结尾不得有多余空格。
    char* str = new char[60];//存储中缀表达式
    char answer[60];//存储后缀表达式
    cin.getline(str, 60);//输入
    Stack<char> oper(60);//存储运算符的栈
    int index = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if(isNumber(str[i]) || str[i] == '.') {//如果是数字或小数点,直接放入answer中
            while(isNumber(str[i]) || str[i] == '.') {//一直读取数字或小数点,直到遇到非数字(输入正确时应为空格)
                answer[index++] = str[i++];
            }
            answer[index++] = ' ';//加一个空格
            i--;//因为for循环中有i++,所以这里要回退一个字符
        }
        else if (str[i] == '(') {//如果是'(',直接入栈
            oper.push(str[i]);
        }
        else if (str[i] == ')') {//如果是')',则依次弹出栈中的元素加入answer,直到遇到'('
            while (oper.getTop() != '(') {
                answer[index++] = oper.pop();
                answer[index++] = ' ';
            }
            oper.pop();//弹出'('
        }
        else if (isOper(str[i])) {//如果是运算符
            if (i == 0 || (!isNumber(str[i - 2]) && str[i-2] != ')')) {//如果是第一个字符,或者前一个字符不是数字,则说明是负号
                if (str[i] == '-') {//如果是负号,则加入answer
                    answer[index++] = '-';
                }
                else if (str[i] != '+') {//如果是正号,则忽略,不是正负号的情况,则表达式错误
                    cerr << "表达式错误" << endl;
                    exit(1);
                }
                continue;//跳过后续,继续下一次循环
            }
            while (!oper.empty() && priority(oper.getTop()) >= priority(str[i])) {
                //如果栈不为空,且栈顶元素的优先级大于等于当前元素,则弹出栈顶元素加入answer
                answer[index++] = oper.pop();
                answer[index++] = ' ';
            }
            oper.push(str[i]);//当前运算符入栈
        }
    }
    //将栈中剩余的元素加入answer
    while (!oper.empty()) {
        answer[index++] = oper.pop();
        answer[index++] = ' ';
    }
    //去除结尾多余的空格
    while(index > 0 && answer[index-1] == ' ') {
		index--;
	}
    answer[index] = '\0';
    cout << answer;
    

    return 0;
}

/*测试数据
输入															输出
2 + 3 * ( 7 - 4 ) + 8 / 4							2 3 7 4 - * + 8 4 / +
( ( 2 + 3) * 4 - ( 8 + 2 ) ) / 5					2 3 + 4 * 8 2 + - 5 /
1314 + 25.5 * 12									1314 25.5 12 * +
-2 * ( +3 )											-2 3 *
123													123
*/