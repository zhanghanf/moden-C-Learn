//fold函数模板
#include<cstdio>
#include<cstdint>//这个头文件包含了固定宽度整数类型的定义，如int32_t、uint64_t等。还有一些与整数类型相关的宏和函数。

template<typename Fn,typename In,typename Out>
constexpr Out fold(Fn fn, In* in, size_t length, Out init) {
	for(size_t i=1;i<length;i++){
		init = fn(init,in[i]);
	}
	return init;
}

void test3() {
	const size_t length = 5;
	int input[length] = {100, 200, 300, 400, 500 };
	auto sum_fn = [](int a, int b) { return a + b; };
	auto max_fn = [](int a, int b) { return (a > b) ? a : b; };
	auto min_fn = [](int a, int b) { return (a < b) ? a : b; };
	auto total = fold(sum_fn, input, length, input[0]);
	auto maximum = fold(max_fn, input, length, input[0]);
	auto minimum = fold(min_fn, input, length, input[0]);
	std::printf("Sum: %d\n", total);
	std::printf("Max: %d\n", maximum);
	std::printf("Min: %d\n", minimum);
}