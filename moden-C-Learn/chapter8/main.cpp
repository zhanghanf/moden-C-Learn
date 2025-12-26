#include<iostream>
#include<cstdint>
void test();
void test1();
void test2();
void randomize(uint32_t&);//函数声明
#include<cstdio>
#include<stdexcept>

template<class to, class from>
struct NarrowCaster const {
	to cast(from value) {
		const auto cons = static_cast<to>val;
		const auto back = static_cast<from>cons;
		if (value != back) throw std::runtime_error{ "Narrow!" };
		return cons;
	}
};

template<class from>
using short_cast = NarrowCaster<short, from>;

void test2(){
	try {
		const short_cast<int> caster;
		const auto sho = caster.cast(12345);
		printf("%d", sho);
	}
catch (const std::runtime_error& e) {
	printf("Exception: %s\n", e.what());
   }
}
struct RandomNumberGenerator {
	RandomNumberGenerator(uint32_t seed) :value{ seed }, iterations{} {}
	uint32_t next();
	size_t Getiter() { return iterations; }
private:
	uint32_t value;
	size_t iterations;
};

namespace B1 {
	namespace B2 {

	}
}
namespace B3::Shaltanac {
	enum class Color {
		Mauve,
		Pink,
		Blue
	};
}
int main() {
	//test();
	using B3::Shaltanac::Color;
	using c = B3::Shaltanac::Color;//类型别名使用
	//c::Blue;
	RandomNumberGenerator ran{ 0x12345 };

	test2();
	while (ran.next() != 0x234) {

	}
	std::cout << ran.Getiter() << std::endl;
	return 0;
}
uint32_t RandomNumberGenerator::next()
{
	++iterations;
	value = 0x3fffffff & (0x41c6416d * value+12345) % 0x80000000;
	return value;
}
