#include <iostream>
#include <cmath>
using namespace std;

//����С����ʵ�����ȶ���
class PriorityQueue {
private:
	int size;
	int count;
	int *data;
public:
	PriorityQueue(int N = 20):size(N),count(0),data(new int[N]){}

	~PriorityQueue() {
		if(data != nullptr)
			delete[] data;
	}

	void ShiftUp(int i) {
		while (i > 0 && data[i] < data[(i - 1) >> 1]) {//�����ǰ�ڵ�С�ڸ��ڵ㣬����
			swap(data[i], data[(i - 1) >> 1]);
			i = (i - 1) >> 1;//���µ�ǰ�ڵ�
		}
	}

	void ShiftDown(int i) {
		while ((i << 1) + 1 < count) {//���������
			int j = (i << 1) + 1;//jָ������
			if (j + 1 < count && data[j + 1] < data[j]) {//������Һ������Һ���С������
				j++;//jָ���Һ���
			}
			if (data[i] <= data[j]) {//�����ǰ�ڵ�С�ڵ������Һ����е���Сֵ
				break;
			}
			swap(data[i], data[j]);//������ǰ�ڵ�����Һ����е���Сֵ
			i = j;//���µ�ǰ�ڵ�
		}
	}

	void Push(int x) {
		if (size <= count) {
			Resize(size << 1);
		}
		data[count] = x;
		count++;
		ShiftUp(count - 1);
	}

	int Front() const{
		if(count == 0) {
			cerr << "PriorityQueue is empty." << endl;
			exit(1);
		}
		return data[0];
	}

	void Pop() {
		if (count == 0) {
			cerr << "PriorityQueue is empty." << endl;
			exit(1);
		}
		data[0] = data[--count];//�����һ��Ԫ�طŵ��Ѷ�,��ɾ�����һ��Ԫ��(�߼���ɾ��,��--count)
		ShiftDown(0);
	}

	bool Empty() const {
		return count == 0;
	}

	int Count() const {
		return count;
	}

	int Size() const {
		return size;
	}

	void Resize(int newSize) {
		int* newData = new int[newSize];
		if(newData == nullptr) {
			cerr << "Memory allocation failed." << endl;
			exit(1);
		}
		for (int i = 0; i < count && i < newSize; i++) {
			newData[i] = data[i];
		}
		delete[] data;
		data = newData;
	}
};

//�����С����
int MiniCost(const int* const length,int N) {
	PriorityQueue q(N);//�������ȶ���
	for (int i = 0; i < N; i++) {
		q.Push(length[i]);//��ľͷ���ȷ������ȶ���
	}
	int result = 0;
	while (q.Count() > 1) {//�����ȶ�����ľͷ��������Ϊ2ʱ
		int a = q.Front();//ȡ����̵�ľͷ
		q.Pop();//ɾ����̵�ľͷ
		int b = q.Front();//ȡ���ζ̵�ľͷ
		q.Pop();//ɾ���ζ̵�ľͷ
		int sum = a + b;//������ľͷ���һ��ľͷ(��Ŀ���������)
		result += sum;//�ۼӻ���
		q.Push(sum);//���µ�ľͷ�������ȶ���
	}
	return result;//������С����
}

int main() {
	int N = 0;//ľͷ���N��
	int* length = nullptr;//ľͷ����
	cin >> N;
	length = new int[N];
	for (int i = 0; i < N; i++) {
		cin >> length[i];//����ÿ��ľͷ�ĳ���
	}
	cout << MiniCost(length, N) << endl;//�����С����
	delete[] length;//�ͷ��ڴ�
	system("pause");
	return 0;
}