// list_929.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<cstdio>
#include<cstdint>

//确定给定字符是否在A-Z或a-z范围内
constexpr char posA{ 65 }, posZ{ 90 }, posa{ 97 }, posz{ 123 };
constexpr bool withinAZ(char c) {
	return c >= posA && c <= posZ;
}
constexpr bool withinaz(char c) {
	return c >= posa && c <= posz;
}

//获取命令行数据元素并存储字符频率
struct AIphaHistogram {
	void ingest(const char* x);
	void print() const;
private:
	size_t counts[26];

};
//ingest方法接受以空字符结尾的字符串指针，并更新26个字母的频率计数
void AIphaHistogram::ingest(const char* x) {
	while (*x != '\0') {
		if (withinAZ(*x)) {
			counts[*x - posA]++;
		}
		else if (withinaz(*x)) {
			counts[*x - posa]++;
		}
		x++;
	}
}
//print方法打印每个字母及其频率计数和直方图信息
void AIphaHistogram::print() const {
	for (size_t i{}; i < 26; i++) {
		printf("%c:", static_cast<char>(i + posa));
		for(int j=0;j< counts[i];j++){
			printf("*");
		}
		printf("\n");
	}
}

int main(int argc, char** argv) {
	AIphaHistogram hist{};
	for (size_t i{ 1 }; i < static_cast<size_t>(argc); i++) {
		//计算每个命令行参数的字符长度
		hist.ingest(argv[i]);
	}
	hist.print();
	printf("Arguments:%d\n", argc);
	for (size_t i{}; i < argc; i++) {
		printf("%zd:%s\n", i, argv[i]);
	}
}
//main函数有效重载变体
//获取命令行数据元素并存储字符长度

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
