//本节讨论常见的数学函数和常数处理数值
//以及如何处理复数、随机数、数值转换并计算比例
//stdlib和boost Math库提供了丰富的数学函数和常数
//复数
#include<catch_amalgamated.hpp>
#include<complex>
TEST_CASE("complex numbers") {
	std::complex<double> a(1.0, 2.0); // 1 + 2i
	std::complex<double> b(3.0, 4.0); // 3 + 4i
	auto sum = a + b;               // (1+3) + (2+4)i = 4 + 6i
	REQUIRE(sum == std::complex<double>(4.0, 6.0));
	REQUIRE(std::abs(a) == Catch::Approx(std::sqrt(5.0))); // Magnitude: sqrt(1^2 + 2^2) = sqrt(5)
	REQUIRE(std::real(a) == Catch::Approx(1.0));
}

//数学常数
#include<boost/math/constants/constants.hpp>

TEST_CASE("boost ::math offers constants") {
	using namespace boost::math::double_constants;
	auto sphere_volume = four_thirds_pi * std::pow(10, 3);
	REQUIRE(sphere_volume == Catch::Approx(4188.7902047));
}

//随机数
//随机数引擎:boost 和stdlib有很多随机数引擎：考虑可重复伪随机数考虑：std：：mt19937_64;
//加密安全随机数：std::random_device;
#include<random>
TEST_CASE("mt 19937 64 test") {
	std::mt19937_64 mt_engine{ 99 };
	REQUIRE(mt_engine() == 8015931446409328671);
	
}
//random device是一个函数对象
TEST_CASE("random device") {
	std::random_device rd_engine{};
	REQUIRE_NOTHROW(rd_engine());
}

//随机数分布
//模拟离散分布
TEST_CASE(" std uniform int distribution") {
	std::mt19937_64 mt_engine{ 102787 };//构造随机数种子
	std::uniform_int_distribution<int> int_d{0, 10};
	size_t size = 1000000;
	int sum{};
	for (size_t i{}; i < size; i++) {
		sum += int_d(mt_engine );             
	}
	auto average = sum / double(size);
	REQUIRE(average == Catch::Approx(5).epsilon(.1));//误差不超过0.1
}
//数值极限：stdlib在头文件中提供了numeric_limits提供各种算术类型在编译期的信息

//boost Numeric Conversion库