#include<boost/test/unit_test.hpp>
#define BOOST_TEST_MODULE StringViewTest
#include<string_view>
//字符串视图：是一个对象，它引用一个字符串的子序列，而不拥有该字符串的数据。
//字符串视图提供了一种高效的方式来处理字符串数据，而无需进行复制或分配新的内存。
//字符串视图通常用于只读操作，可以提高性能，特别是在处理大型字符串或频繁传递字符串参数时。
//C++标准库中的std::string_view类就是一个字符串视图的实现。
//构造
BOOST_AUTO_TEST_CASE(StringView_Construction)
{
	const char* cstr = "Hello, World!";
	std::string str = "Hello, World!";
	
	std::string_view sv1(cstr);//拷贝构造
	std::string_view sv2(str);

	std::string_view sv3(cstr, 5); // "Hello"
	//复制构造和复制赋值
	std::string_view sv4 = sv1; // 复制构造
	BOOST_CHECK_EQUAL(sv1, "Hello, World!");
	BOOST_CHECK_EQUAL(sv4, "Hello, World!");
	BOOST_CHECK_EQUAL(sv3, "Hello");
}
//支持的操作：支持与字符串类似的操作，如访问字符、子串、查找和比较等。
BOOST_AUTO_TEST_CASE(StringView_Operations)
{
	std::string_view sv = "Hello, World!";
	//迭代器：begin(), end()，rbegin(), rend()，cbegin(), cend()
	
	//访问字符：[],at(),front(),back()
	BOOST_CHECK_EQUAL(sv[0], 'H');
	BOOST_CHECK_EQUAL(sv.at(7), 'W');
	//提取方法：substr()，copy() substr()方法：返回字符串视图的子串。
	//copy()方法：从字符串视图中复制指定数量的字符到一个字符数组中。
	std::string_view sv_copy = "Hello, World!";
	char buffer[6] = {};
	sv_copy.copy(buffer, 5, 7); // 从索引7开始复制5个字符到buffer
	BOOST_CHECK_EQUAL(std::string(buffer), "World");
	std::string_view sub_sv = sv.substr(7, 5); // "World"
	BOOST_CHECK_EQUAL(sub_sv, "World");
	//查找：find rfind find_first_of find_last_of find_first_not_of find_last_not_of；
	size_t pos = sv.find("World");
	BOOST_CHECK_EQUAL(pos, 7);
	//比较
	BOOST_CHECK(sv.compare("Hello, World!") == 0);
	BOOST_CHECK(sv.compare("Hello") > 0);

	//容量相关的方法：size(), length(), empty()
	BOOST_CHECK_EQUAL(sv.size(), 13);
	//除了上面提到的方法外，std::string_view还提供了其他一些有用的方法，如remove_prefix()和remove_suffix()，用于调整视图的起始位置和结束位置。
	sv.remove_prefix(7); // 现在sv变为 "World!"
	BOOST_CHECK_EQUAL(sv, "World!");
	sv.remove_suffix(1); // 现在sv变为 "World"
	BOOST_CHECK_EQUAL(sv, "World");
}

//