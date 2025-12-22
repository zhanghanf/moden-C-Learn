//hello world
#include <iostream>
#include <stdexcept>
#include"Heap.h"
#include<limits>
//一个运行时溢出检查的Checked-Integer类
struct CheckedInt {
	int value;
	CheckedInt(int v) : value(v) {}
	CheckedInt operator+(const CheckedInt& other) const {
		if ((other.value > 0) && (value > INT_MAX - other.value)) {
			throw std::overflow_error("Integer overflow on addition");
		}
		if ((other.value < 0) && (value < INT_MIN - other.value)) {
			throw std::underflow_error("Integer underflow on addition");
		}
		return CheckedInt(value + other.value);
	}
	CheckedInt operator-(const CheckedInt& other) const {
		if ((other.value < 0) && (value > INT_MAX + other.value)) {
			throw std::overflow_error("Integer overflow on subtraction");
		}
		if ((other.value > 0) && (value < INT_MIN + other.value)) {
			throw std::underflow_error("Integer underflow on subtraction");
		}
		return CheckedInt(value - other.value);
	}
	explicit operator int() const{
		return value;
	}
	CheckedInt operator*(const CheckedInt& other) const {
		if (value > 0 && other.value > 0 && value > INT_MAX / other.value) {
			throw std::overflow_error("Integer overflow on multiplication");
		}
		if (value < 0 && other.value < 0 && value < INT_MAX / other.value) {
			throw std::overflow_error("Integer overflow on multiplication");
		}
		if ((value > 0 && other.value < 0 && other.value < INT_MIN / value) ||
			(value < 0 && other.value > 0 && value < INT_MIN / other.value)) {
			throw std::underflow_error("Integer underflow on multiplication");
		}
		return CheckedInt(value * other.value);
	}
};

struct Point {
	int x;
	int y;
	Point(int x, int y) : x(x), y(y) {
		printf("Point created%p\n",this);
	}
	~Point() {
		printf("Point destroyed%p\n",this);
	}
};
int main() {
	CheckedInt a(INT_MAX);
	CheckedInt b(3000);
	try {
		CheckedInt c = a + b;
		std::cout << "Result: " << c.value << std::endl;
	} catch (const std::overflow_error& e) {
		std::cerr << "Overflow error: " << e.what() << std::endl;
	} catch (const std::underflow_error& e) {
		std::cerr << "Underflow error: " << e.what() << std::endl;
	}

	
	
	try {
		void* ptr1 = heap.allocate(1024);//分配一个Bucket
		void* ptr2 = heap.allocate(2048);
		std::cout << "Allocated two buckets." << std::endl;
		heap.free(ptr1);
		heap.free(ptr2);
		std::cout << "Freed two buckets." << std::endl;
	} catch (const std::bad_alloc& e) {
		std::cerr << "Allocation error: " << e.what() << std::endl;
	}
	//测试new和delete重载
	std::cout << "Testing custom new and delete operators." << std::endl;
	std::cout << "Buckets    :" << heap.buckets << std::endl;
	auto obj = new int{ 200 };//使用自定义Heap分配器
	std::cout << "Buckets    :" << obj<<" " << *obj << std::endl;
	delete obj;//释放内存
	try {
		while (true) {
			new char;
			printf("Allocated a char\n");
		}
	}catch (const std::bad_alloc& e) {
		std::cerr << "Allocation error: " << e.what() << std::endl;
	}
	std::cout << "Hello, World!" << std::endl;
	//long double最大值转float测试
	float m = std::numeric_limits<long double>::max();
	std::cout << m;
	int64_t n = std::numeric_limits<int64_t>::max();
	int32_t b1=static_cast<int32_t>(n);
	if (n!= b1)std::cout << b1 <<" " << n;
	return 0;
}