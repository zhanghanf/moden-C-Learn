//迭代器：迭代器是STL中用于遍历容器元素的一种对象。它提供了一种统一的方式来访问不同类型容器中的元素，而不需要了解容器的底层实现细节。
//每个迭代器支持一组操作，如解引用（*）、递增（++）、复制构造和比较（==、!=）等。通过这些操作，用户可以遍历容器中的元素，进行读取或修改操作。
//迭代器的类型根据容器的不同而有所区别，例如vector、list、map等容器都有各自对应的迭代器类型。
//迭代器通常是模板函数；我们可以使用模板函数来编写与容器无关的算法，从而实现代码的复用性和通用性。
//输出迭代器：
//1.插入迭代器（Insert Iterators）：用于将元素插入到容器中，如back_inserter、front_inserter和inserter。
//2.流迭代器（Stream Iterators）：用于将数据从输入流读取到容器中，或将容器中的数据写入输出流中，如istream_iterator和ostream_iterator。
#define BOOST_TEST_MODULE IteratorTest
#include<boost/test/unit_test.hpp>
#include<deque>
#include<iterator>
BOOST_AUTO_TEST_CASE(IteratorTest) {
	std::deque<int> dq;
	//使用插入迭代器将元素插入到deque容器中
	auto dqit = std::back_inserter(dq);
	for (int i = 1; i <= 5; ++i) {
		*dqit = i * 10; //通过解引用插入元素
		++dqit; //移动迭代器位置:指向下一个插入位置
	}
	BOOST_CHECK(dq.size() == 5);
	BOOST_CHECK(dq[0] == 10);
	BOOST_CHECK(dq[4] ==50);
	auto front_it = std::front_inserter(dq);
	*front_it = 5;  //在deque容器前端插入元素
	++front_it;//移动迭代器位置
	//使用流迭代器将deque容器中的元素输出到标准输出流
}
//输入迭代器：
//1.流迭代器（Stream Iterators）：用于将数据从输入流读取到容器中，或将容器中的数据写入输出流中，如istream_iterator和ostream_iterator。
#include<forward_list>
BOOST_AUTO_TEST_CASE(ForwordTest) {
	const std::forward_list<int> fl = { 10,20 };
	//使用输入流迭代器将forward_list容器中的元素读取到标准输入流
	auto it = fl.begin();
	BOOST_CHECK(*it == 10);
	++it;
	BOOST_CHECK(*it == 20);
	BOOST_CHECK(++it == fl.end());
}
//前向迭代器（Forward Iterators）：支持单向遍历容器元素，可以多次通过同一位置访问元素。
#include<set>
BOOST_AUTO_TEST_CASE(SetTest) {
	std::set<int> s = { 1,2,3,4,5 };
	auto it = s.begin();
	BOOST_CHECK(*it == 1);
	++it;
	BOOST_CHECK(*it == 2);
	++it;
	BOOST_CHECK(*it == 3);
}
//双向迭代器（Bidirectional Iterators）：支持双向遍历容器元素，可以向前和向后移动迭代器位置。
#include<list>
BOOST_AUTO_TEST_CASE(ListTest) {
	std::list<int> lst = { 1,2,3,4,5 };
	auto it = lst.begin();
	BOOST_CHECK(*it == 1);
	++it;
	BOOST_CHECK(*it == 2);
	--it;
	BOOST_CHECK(*it == 1);
}
//随机访问迭代器（Random Access Iterators）：支持任意位置的访问，可以通过算术运算符（+、-）和比较运算符（<、>）进行操作。允许使用[]运算符访问元素。
#include<vector>
BOOST_AUTO_TEST_CASE(VectorTest) {
	std::vector<int> vec = { 1,2,3,4,5 };
	auto it = vec.begin();
	BOOST_CHECK(*it == 1);
	it += 2; //移动到第三个元素
	BOOST_CHECK(*it == 3);
	it = it - 1; //移动到第二个元素
	BOOST_CHECK(*it == 2);
	BOOST_CHECK((it < vec.end()) == true);
}
//连续迭代器（Contiguous Iterators）：是随机访问迭代器的一种特殊形式，保证元素在内存中是连续存储的。允许通过指针算术运算直接访问元素。
//可变迭代器（Mutable Iterators）：允许通过迭代器修改容器中的元素值。