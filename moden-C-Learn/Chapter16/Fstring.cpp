//文件流：读取和写入字符序列提供便利：与字符串流类结构类似
//文件流的优势：通常的流接口、提供用于格式化和操纵输出的功能
//围绕文件的RALL包装器：不会出现资源泄露
//支持移动语义，可以严格控制文件在作用域的位置

//使用binary标志，表示添加二进制文件
#include<fstream>
#include<iostream>
using namespace std;
void test1() {
	ofstream file("lunchtime.txt", ios::out | ios::app);
	file << "hello world" << endl;
	file << "lunth file" <<2<<" x.so"<< endl;

}
void test2() {
	ifstream file("lunchtime.txt");
	int num,min=-1;
	while (file >> num) {
		min = num > min ? min : num;
	}
	cout << min << endl;
}
//生成ifstring的工厂函数：用异常处理错误
ifstream open(const char* path, ios_base::openmode mode = ios_base::in) {
	ifstream ifile(path, mode);
	if (!ifile.is_open()) {
		string err{ "Unable file open" };
		err.append(path);
		throw runtime_error{ err };
	}
	ifile.exceptions(ifstream::badbit);
	return ifile;
}

//流缓冲区：发送或提取字符的模板，获取流缓冲区方法：rdbuf
//cout<<file.rdbuf();
//输出流缓冲区：
void test3() {
	ostreambuf_iterator<char> it{ cout };
	*it = 'H';
	//++it;
	*it = 'i';
	//使用输入流缓冲区
	istreambuf_iterator<char> cin_itr{ cin }, end{};
	const string name{ cin_itr,end };
	cout << name;
}

//随机访问方法：输入流：tellg（不接受参数并返回光标位置）和seekg（允许设置光标位置）
//输出流：tellp和seekp方法
int main() {
	//test1();
	//test2();
	test3();
}