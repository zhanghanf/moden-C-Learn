//函数调用运算符
#include<cstdio>
#include<cstdint>

struct Countif {
	const char x;
	Countif(char t) : x(t) {}
	size_t operator()(const char*str) const {
		size_t i=0,count = 0;
		while (str[i++]) {
			if(str[i]==x){
				count++;
			}

		}
		return count;
	}
};

void test2() {
	char c = 'h';
	//refrence object to function
	auto func = [&c](const char* str)->double {
		size_t i = 0, count{};
		while (str[i++]) {
			if (str[i] == 'c') count++;
		}
		return count;
		};
	const char*testt="chinese china chengdu";
	const char* str = "hello world, welcome to china";
	Countif count_e('o');
	size_t count = count_e(str);
	auto count_c = func(testt);
	std::printf("The character 'o' appears %zu times in the string.\n", count);
	std::printf("The character 'c' appears %.2f times in the string.\n", count_c);
}
//函数指针：函数式编程是一种编程范式，它将函数作为一等公民对待，允许将函数作为参数传递给其他函数，或者将函数作为返回值从其他函数返回。
//声明一个函数指针类型
using FuncPtr = size_t(*)(const char*);//指向函数的指针类型，函数接受一个const char*参数，返回一个size_t值
//定义一个函数，接受一个函数指针作为参数
size_t count_char(const char* str, FuncPtr func) {
	return func(str);
}
//定义一个具体的函数，符合FuncPtr类型
size_t count_a(const char* str) {
	size_t i = 0, count = 0;
	while (str[i++]) {
		if (str[i] == 'a') count++;
	}
	return count;
}