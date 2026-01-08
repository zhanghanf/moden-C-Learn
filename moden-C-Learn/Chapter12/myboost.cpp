#include<catch_amalgamated.hpp>
//工具库使用测试
#include<boost/logic/tribool.hpp>
//using boost::logic::tribool;//三值布尔类型
using boost::logic::indeterminate;//不确定值
boost::logic::tribool a = true,b=false,c=indeterminate;
/*
//测试tribool的基本操作
TEST_CASE("Tribool basic operations") {

	SECTION("Truth values") {
		REQUIRE(truth_value(a)==true);
		REQUIRE_FALSE(b);
		REQUIRE(indeterminate(c));
	}
	SECTION("Logical operations") {
		REQUIRE_FALSE((a && b));
		REQUIRE((a || b) );
		REQUIRE((a && c) == indeterminate);
		REQUIRE((b || c) == indeterminate);
		REQUIRE_FALSE(boost::logic::indeterminate(a && b) ? true : static_cast<bool>(a && b));
	}
}

*/


//optional使用测试
#include<optional>
using std::optional;
//optional是一个类模板，可以包含一个值或者不包含值
struct MyStruct {
	int x;
	double y;
};
enum Priority { LOW, MEDIUM, HIGH };

optional<MyStruct> getMyStruct(Priority Pri) {
	if(Pri== HIGH) {
		return MyStruct{ 42, 3.14 };
	}
	else {
		return std::nullopt; //表示没有值
	}
}

TEST_CASE("Boost Optional Test") {
	SECTION("Get MyStruct with HIGH priority") {
		optional<MyStruct> optStruct = getMyStruct(HIGH);
		REQUIRE(optStruct); //检查是否有值
		REQUIRE(optStruct->x == 42);
		REQUIRE(optStruct->y == Catch::Approx(3.14));
		REQUIRE(optStruct.has_value()); //检查是否有值
		auto myopt=std::make_optional<MyStruct>(MyStruct{10,2.71});//使用make_optional创建optional对象
		REQUIRE(myopt->x==10);
	}
	SECTION("Get MyStruct with LOW priority") {
		optional<MyStruct> optStruct = getMyStruct(LOW);
		REQUIRE_FALSE(optStruct); //检查是否没有值
	}     
}

//pair使用测试
#include<utility>
struct Person {
	std::string name;
	int age;
};
Person person{ "john",30 };
std::pair<std::string, int> personPair = std::make_pair(person.name, person.age);
TEST_CASE("Pair Test") {//测试pair的基本操作
	REQUIRE(personPair.first == "john");
	REQUIRE(personPair.second == 30);
}
//测试pair的结构化绑定
TEST_CASE("Pair Structured Binding Test") {
	auto [name, age] = personPair;
	REQUIRE(name == "john");
	REQUIRE(age == 30);
}
//测试pair的比较操作
TEST_CASE("Pair Comparison Test") {
	std::pair<int, int> pair1 = std::make_pair(1, 2);
	std::pair<int, int> pair2 = std::make_pair(1, 3);
	REQUIRE(pair1 < pair2); //比较第一个元素，如果相等则比较第二个元素
}


//tuple使用测试（元组）
#include<tuple>
TEST_CASE("Tuple Test") {//测试tuple的基本操作，包含任意数量的不同元素
	std::tuple<std::string, int, double> personTuple = std::make_tuple("Alice", 28, 5.6);
	REQUIRE(std::get<0>(personTuple) == "Alice");
	REQUIRE(std::get<1>(personTuple) == 28);
	REQUIRE(std::get<2>(personTuple) == Catch::Approx(5.6));
}
//测试tuple的结构化绑定
TEST_CASE("Tuple Structured Binding Test") {
	std::tuple<std::string, int, double> personTuple = std::make_tuple("Bob", 35, 6.0);
	auto [name, age, height] = personTuple;
	REQUIRE(name == "Bob");
	REQUIRE(age == 35);
	REQUIRE(height == Catch::Approx(6.0));
}
//测试tuple的比较操作
TEST_CASE("Tuple Comparison Test") {
	std::tuple<int, char> tuple1 = std::make_tuple(1, 'a');
	std::tuple<int, char> tuple2 = std::make_tuple(1, 'b');
	REQUIRE(tuple1 < tuple2); //比较第一个元素，如果相等则比较第二个元素
}

//测试tuple的拼接
TEST_CASE("Tuple Concatenation Test") {
	std::tuple<int, char> tuple1 = std::make_tuple(1, 'a');
	std::tuple<double, std::string> tuple2 = std::make_tuple(3.14, "pi");
	auto concatenatedTuple = std::tuple_cat(tuple1, tuple2);//拼接两个tuple
	REQUIRE(std::get<0>(concatenatedTuple) == 1);
	REQUIRE(std::get<1>(concatenatedTuple) == 'a');
	REQUIRE(std::get<2>(concatenatedTuple) == Catch::Approx(3.14));
	REQUIRE(std::get<3>(concatenatedTuple) == "pi");
}
//any使用测试
#include<boost/any.hpp>
using boost::any;
TEST_CASE("Boost Any Test") {//测试any的基本操作，可以存储任意类型的值
	any a = 42; //存储一个整数
	REQUIRE(boost::any_cast<int>(a) == 42);
	a = std::string("Hello, Boost.Any!"); //存储一个字符串
	REQUIRE(boost::any_cast<std::string>(a) == "Hello, Boost.Any!");
	//测试any_cast失败时抛出异常
	a = 3.14;
	REQUIRE_THROWS_AS(boost::any_cast<int>(a), boost::bad_any_cast);
}
//测试any的类型检查
TEST_CASE("Boost Any Type Check Test") {
	any a = 100;
	REQUIRE(a.type() == typeid(int));
	a = 2.71;
	REQUIRE(a.type() == typeid(double));
	a = std::string("Boost");
	REQUIRE(a.type() == typeid(std::string));
}

//variant使用测试,variant是一个类型安全的联合体，可以存储多种类型中的一种
#include<boost/variant.hpp>
using boost::variant;
TEST_CASE("Boost Variant Test") {//测试variant的基本操作，可以存储多种类型中的一种
	variant<int, std::string> v = 10; //存储一个整数
	REQUIRE(boost::get<int>(v) == 10);
	v = std::string("Boost.Variant"); //存储一个字符串
	REQUIRE(boost::get<std::string>(v) == "Boost.Variant");
	//测试get失败时抛出异常
	v = 3.14;
	REQUIRE_THROWS_AS(boost::get<std::string>(v), boost::bad_get);
}

//测试variant的访问
TEST_CASE("Boost Variant Access Test") {
	variant<int, double, std::string> v = 2.5;
	REQUIRE(boost::get<double>(v) == Catch::Approx(2.5));
	v = 42;
	REQUIRE(boost::get<int>(v) == 42);
	v = "Variant Test";
	REQUIRE(boost::get<std::string>(v) == "Variant Test");
}
//测试variant的类型检查
TEST_CASE("Boost Variant Type Check Test") {
	variant<int, double> v = 100;
	REQUIRE(v.type() == typeid(int));
	v = 3.14;
	REQUIRE(v.type() == typeid(double));
}
//std::visit使用测试

TEST_CASE("std::variant") {
	
}