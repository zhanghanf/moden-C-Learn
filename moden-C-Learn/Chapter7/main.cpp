//hello world
#include <iostream>
#include <stdexcept>
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

//控制自由存储区heap和bucket的分配和释放
struct Bucket {
	const static size_t SIZE = 4096;
	std::byte data[SIZE];
};

struct Heap {
	void* allocate(size_t size) {
		if (size > Bucket::SIZE) {//请求的大小超过单个Bucket的大小
			throw std::bad_alloc();
		}
		for (auto& bucket : buckets) {//查找一个未使用的Bucket
			if (!bucketInUse[&bucket - buckets]) {
				bucketInUse[&bucket - buckets] = true;
				return static_cast<void*>(bucket.data);//返回Bucket的数据指针
			}
		}
		throw std::bad_alloc();
	}
	void free(void* ptr) {//接受一个指针并释放对应的Bucket
		for (auto& bucket : buckets) {
			if (static_cast<void*>(bucket.data) == ptr) {
				bucketInUse[&bucket - buckets] = false;
				return;
			}
		}
	}
	static const size_t MAX_BUCKETS = 10;
	Bucket buckets[MAX_BUCKETS]{};//包含MAX_BUCKETS个Bucket对象
	bool bucketInUse[ MAX_BUCKETS ] = { false };//跟踪每个Bucket是否被使用
};

// 测试Heap和Bucket
	//通过重载运算符new和delete来使用自定义的Heap分配器
Heap heap;
void* operator new(std::size_t size) {
	return heap.allocate(size);
}
void operator delete(void* ptr) noexcept {
	heap.free(ptr);
}
//布置运算符new和delete的重载

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
	return 0;
}