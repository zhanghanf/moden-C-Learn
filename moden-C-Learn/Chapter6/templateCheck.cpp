//模板是类型安全的
//求平方的模板函数
#include"SimpleiUniquePoint.h"
#include<type_traits>
#include<cstdint>
constexpr  const char* as_str(bool x) {
	return x ? "true" : "false";
}
template <typename T>
T square(T x) {
	return x * x;
}
//一个模板实例化失败的例子
template <typename T>
T printDouble(T x) {
	return x + x;
}
//concept测试
void test() {
	printf("is_integral<int>:%s\n", as_str(std::is_integral<int>::value));
	printf("is_integral<char>:%s\n", as_str(std::is_integral<char>::value));
	printf("is_floating_point<int&>:%s\n", as_str(std::is_floating_point<int&>::value));
	printf("is_integral<double&>:%s\n", as_str(std::is_integral<double&>::value));
	printf("is_floating_point<int*>:%s\n", as_str(std::is_floating_point<int*>::value));
	printf("is_floating_point<float>:%s\n", as_str(std::is_floating_point<float>::value));
}
//约束要求测试
template<typename T>
concept bool Avrageable = requires(T a, T b) {
	return std::is_default_constructible_v<T> ::value&&requires {
		{ a += b } -> T;
		{ a / 2 } -> T;
	};
}

//使用static_assert进行约束检查
template <typename T>
T mean(T* value, size_t size) {
	static_assert(Avrageable<T>, "Type T must be Avrageable");
	static_assert(std::is_floating_point_v<T> || std::is_integral_v<T>, "Type T must be floating point or integral");
}
int main() {
	//测试模板函数square
	
	test();
	testSimpleiUniquePoint();
	return 0;
}