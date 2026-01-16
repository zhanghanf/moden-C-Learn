//流：对数据进行建模，使数据在对象间流动，这些对象可以对数据任意处理
//使用流时：输入是进入流的数据，输出是流出来的数据
//c++中：流是执行输入或输出（I/O）的主要机制
//宽字符版本：用于处理unicode宽字符配合wchar_t使用

#include<iostream>
//流类：STL流类：istream ostream iostream wistream
//1.全局流对象
//stdin 键盘stdout控制台 stderr 控制台 输入、输出和错误流：桌面环境中
//cout cin cerr clog (错误输出缓冲)

//格式化操作和未格式化操作：格式化操作指在数据传输前进行预处理，再指定格式进行输入输出
//未格式化：输入输出原始数据cin.read();

#include<bitset>
#include<string>
#include<iomanip>//执行printf格式
using namespace std;
void test1() {
	cout << boolalpha << true << endl;
	cout << noboolalpha << false << endl;
	cout << oct << 106 << endl;
	cout << hex << 6789990 << endl;
	cout << scientific << 877989.888 << endl;
	cout << fixed << setprecision(2) << 1.2345 << endl;//保留两位小数
	cout << setw(4) << 0x11 <<endl<< 0x1111<<endl << 0x11111111 << endl;
}

void test() {
	//格式化操作
	int x, y;
	cout << "X:";
	cin >> x;
	cout << "Y:";
	cin >> y;
	string op;
	cout << "Operation:";
	cin >> op;
	if (op == "+") {
		cout << x + y;
	}
	else cout << "error cin";
}
#include<vector>
//使用vector实现输出运算符重载
template<typename T>
ostream& operator<<(ostream& os, vector<T> num) {
	os << "nums.size:" << num.size() << endl;
	os << "nums.capacity" << num.capacity() << endl;
	os << "nums address" << &num << endl;
	for (auto e : num) {
		os << "\t" << e << "\n ";
	}
	return os;
}

//输入运算符重载
template<class T>
istream& operator>>(istream& in, vector<T>& t) {
	T elem;
	while (in >> elem) {
		t.emplace_back(move(elem));
	}
	return in;
}
int main() {
	bitset<8> bits{ "01101100" };
	string str{ "crying zero and i'am hearing" };
	size_t num{ 111 };
	cout << str;
	cout << '\n';
	cout << bits;
	cout << num;
	cout << "s\n";
	cout << "-------------------------------------------------------" << endl;

	//test();
	cout << "---------------------------------------------------------" << endl;
	test1();

	const vector<string> str1{
		"gygygyy","dhhdhhh","dddd","hello"
	};
	const vector<bool> bits1{ true,false,true,false };
	cout << str1<<bits1;
	vector<int> str3;
	cin >> str3;
	cout << str3;
}