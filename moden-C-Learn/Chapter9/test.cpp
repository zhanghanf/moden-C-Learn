#include<cstdio>
#include<cstdint>
template<typename Fn>
void transform(Fn fn, const int* in, int* out, size_t length){
	for (size_t i = 0; i < length; i++) {
		out[i] = fn(in[i]);
	}
}


void test() {

	const size_t length = 5;
	int input[length] = {1, 2, 3, 4, 5};
	int output[length] = {0};
	transform([](int x) { return x * x; }, input, output, length);
	for(size_t i = 0; i < length; i++) {
		std::printf("output[%zu] = %d\n", i, output[i]);
	}
	transform([](int x) {return x + 1; }, input, output, length);
	for (size_t i = 0; i < length; i++) {
		std::printf("output[%zu] = %d\n", i, output[i]);
	}
	std::printf("Test function called.\n");
}
//可变参数的函数
#include<cstdarg>
int sum(int count, ...) {
	int total = 0;
	va_list args;//定义一个变量来存储可变参数列表
	va_start(args, count);//初始化args，使其指向第一个可变参数
	for (int i = 0; i < count; i++) {
		total += va_arg(args, int);//获取下一个可变参数，并指定其类型
	}
	va_end(args);
	return total;
}
//这个函数不是类型安全的


//可变参数模板
template<typename... Args>
int safe_sum(Args... args) {
	return (args + ... + 0); //折叠表达式：将所有参数相加，在C++17及以上版本中可用
}
//用参数包展开实现打印函数
void print_all() {
	std::printf("\n");
}
template<typename T, typename... Args>
void print_all(T first, Args... args) {
	std::printf("%s ", std::to_string(first).c_str());
	print_all(args...);
}