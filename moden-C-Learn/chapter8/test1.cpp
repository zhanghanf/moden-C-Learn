#include <iostream>
struct Tacer {
	Tacer(const char*str) :name{str}
	{
		std::cout <<name<< "Tacer constructed" << std::endl;
	}
	~Tacer() {
		std::cout <<name<< "Tacer destructed" << std::endl;
		//delete[] name;
	}
	const char* name;
};
void test() {
	std::cout<<"Test 1"<<std::endl;
	Tacer t{ "c1" };
	Tacer t1{ "c2" };
	{
		std::cout << "Test 2" << std::endl;
		Tacer t11{ "c1" };
		Tacer t12{ "c2" };
		std::cout << "Test 2 end" << std::endl;
	}
}
//线性同余法生成伪随机数
void randomize(uint32_t& val) {
	val = 0x3fffffff & (0x41c6416d * val + 12345) % 0x80000000;
}
void test1() {
	size_t iterations{};
	uint32_t val = 12345678;
	while (val != 0x474343) {
		randomize(val);
		++iterations;
	}
	printf("iterations: %zu\n", iterations);
}

