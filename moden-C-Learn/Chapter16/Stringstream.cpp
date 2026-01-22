//字符串流：读取和写入字符序列
//将字符数据解析为类型，输入字符串流
//输出字符串流：从可变长度构建字符串
//1.输出字符串流为字符序列提供输出流语义
//特化：ostringstream,wstringstream
#include<sstream>
#include<iostream>
#include<string>
using namespace std;
void test() {
	ostringstream os;
	os << "hello world!";
	os << "by the sun of Worvan";
	const auto larza = os.str();//将数据流转化为对象
	cout << larza << endl;
	os.str("i am god");//使用字面里：替换流中的内容
}
void test1() {
	string str{ "1 22 3.45" };
	istringstream is(str);//将字符串转化为输入流，所有字符串都是可移动的
	float a, b, c;
	is >> a >> b >> c;
	cout << a << " " << b << " " << endl;
	stringstream ss;//支持输入和输出的字符串流
	ss<<"who;s DEAD" ;
	ss >> str;
	int what;
	ss >> hex >> what;

}
void test2() {
	string line = "apple,banana,grape";
	stringstream ss(line);
	string token;

	// 指定分隔符为逗号 ','
	while (getline(ss, token, ',')) {
		cout << token << endl;
	}
	// 输出:
	// apple
	// banana
	// grape
}
void test3() {
    stringstream ss;

    // 1. 写入初始数据
    ss << "Hello World 123";
    cout << "初始内容: \"" << ss.str() << "\"" << endl;

    // --- 读指针操作 (seekg / tellg) ---

    // 2. 获取当前读指针位置 (此时应该在15，因为刚写完)
    // 注意：在输出模式下读指针可能未定义，我们先切换视角
    // 或者直接对字符串流进行操作

    // 3. 将读指针移动到开头，准备读取
    ss.seekg(0, ios::beg); // 或者简写 ss.seekg(0);

    string word;
    ss >> word;
    cout << "第一次读取: " << word << endl; // 输出 "Hello"

    // 4. 查看读指针现在的位置
    cout << "读指针当前在: " << ss.tellg() << " 字节处" << endl; // 通常是6 (Hello+空格)

    // 5. 跳过接下来的5个字符 (从当前位置向后跳)
    ss.seekg(5, ios::cur);
    ss >> word;
    cout << "跳过之后读取: " << word << endl; // 输出 "123" (跳过了 "World")

    // --- 写指针操作 (seekp / tellp) ---

    // 6. 假设我们要修改中间的内容，而不是追加
    // 先回到开头，写入新内容覆盖旧内容
    ss.seekp(0); // 写指针回到开头
    ss << "Hi";  // 覆盖了 "Hello" 的前两个字符

    // 7. 注意：此时读指针还在后面，我们需要移动它或者获取写入后的内容
    // 强制获取最终结果 (写指针不影响 str() 的逻辑，str() 返回全部缓冲区)
    cout << "\n修改后的内容: \"" << ss.str() << "\"" << endl;
    // 输出: "Hi World 123" (前面被覆盖了)
}
int main() {
	
	test();
	test1();
}
