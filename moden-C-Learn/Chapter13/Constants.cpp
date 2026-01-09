//标准模板库是标准库的一部分，包含了大量的通用模板类和函数，如容器、迭代器、算法等。
//容器（Containers）：用于存储和管理数据的模板类，如vector、list、map等。
//迭代器（Iterators）：用于遍历容器中元素的对象，如begin()、end()等。
//算法（Algorithms）：用于处理容器中数据的通用函数，如sort()、find()等。
//1.顺序容器（Sequence Containers）：如vector、list、deque等，按顺序存储元素。
//2.关联容器（Associative Containers）：如set、map、unordered_set、unordered_map等，基于键值对存储元素，支持快速查找。
//3.无序关联容器（Unordered Associative Containers）：如unordered_set、unordered_map等，基于哈希表实现，提供平均常数时间复杂度的查找操作。
//1.1数组（array）：固定大小的顺序容器，提供与C风格数组类似的功能，但具有更多的成员函数和类型安全性。
#include <array>
#define BOOST_TEST_MODULE ArrayTest
#include<boost/test/included/unit_test.hpp>

std::array<int, 5> arr = {1, 2, 3, 4, 5};
BOOST_AUTO_TEST_CASE(test_array) {
	BOOST_CHECK(arr.size() == 5);
	BOOST_CHECK(arr[0] == 1);//元素访问 导致未定义行为


	BOOST_CHECK(arr.at(1) == 2);//at 抛出异常
	BOOST_REQUIRE_THROW(arr.at(5), std::out_of_range);//BOOST_REQUIRE_THROW 检查是否抛出指定异常类型
	BOOST_REQUIRE(arr.front() == 1);
	BOOST_REQUIRE(arr.back() == 5);
	BOOST_REQUIRE(get<4>(arr) == 5);//gei进行边界检查，超过范围会抛出异常，
	BOOST_CHECK_NO_THROW(get<3>(arr));//BOOST_CHECK_NO_THROW_IMPL 检查代码块是否不抛出异常
}
//boost test框架的使用:其中常用的宏有BOOST_AUTO_TEST_CASE,BOOST_FIXTURE_TEST_CASE,BOOST_CHECK,BOOST_REQUIRE等；

//存储模型：四种方法提取指向数组元素的第一个指针
BOOST_AUTO_TEST_CASE(test_array_pointer) {
	int* p1 = &arr[0]; // 方法1：使用下标运算符获取第一个元素的地址int* p2 = arr.data(); // 方法2：使用data()成员函数获取指向数组数据的指针
	int* p3 = &arr.at(0); // 方法3：使用begin()成员函数获取指向第一个元素的迭代器
	int* p4 = std::addressof(arr.front()); // 方法4：使用front()成员函数和std::addressof获取第一个元素的地址
	
	BOOST_CHECK(p1 == p3);
	BOOST_CHECK(p1 == p4);
}
//迭代器模型：使用迭代器遍历数组元素
BOOST_AUTO_TEST_CASE(test_array_iterator) {
	auto it = arr.begin();
	BOOST_CHECK(*it == 1);
	++it;
	BOOST_CHECK(*it == 2);
	it = arr.end() - 1;
	BOOST_CHECK(*it == 5);
}
