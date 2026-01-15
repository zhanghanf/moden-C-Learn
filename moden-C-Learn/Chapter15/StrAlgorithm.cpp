//boost字符串算法：
#include<boost/test/unit_test.hpp>
#define BOOST_TEST_MODULE StrAlgorithm
#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>
//boost字符串算法库提供了一组用于字符串处理和操作的函数和工具，涵盖了字符串的拆分、连接、替换、修剪等常见操作。
//boost Range库提供了一组用于处理范围（如容器、数组等）的算法和工具，允许以更简洁和高效的方式操作数据范围。
//range库中的算法可以与标准库算法结合使用，以实现更复杂的数据处理任务。
//range库还提供了一些适用于范围的适配器和视图，使得对数据进行转换和过滤变得更加方便。
//支持的操作：单程Range和双向Range
//谓词：is_equal、is_less、is_greater等：boost库广泛的引入了各种谓词，用于比较和判断范围内的元素关系。
#include<boost/algorithm/string/predicate.hpp>
//谓词测试
BOOST_AUTO_TEST_CASE(Algorithm) {
	using namespace boost::algorithm;	BOOST_TEST(is_equal()( 'a', 'a' )); // 测试字符相等
	BOOST_TEST(is_less()( 3, 5 ));       // 测试整数小于关系
	using namespace std::literals::string_literals;
	std::string word("sdysfnigfmdm;lll;dos");
	//starts_with测试
	BOOST_TEST(starts_with(word, "sdy"s));
	BOOST_TEST(!starts_with(word, "dy"s));
	//ends_with测试
	BOOST_TEST(ends_with(word, "dos"s));
	BOOST_TEST(!ends_with(word, "ll"s));
	//contains测试
	BOOST_TEST(contains(word, "fnig"s));
	BOOST_TEST(!contains(word, "fnigx"s));
	//all测试
	
}
BOOST_AUTO_TEST_CASE(StrAlgorithmCase0)
{
	std::string s = "  Hello, World!  ";
	std::string trimmed = boost::algorithm::trim_copy(s); // 去除字符串两端的空白字符
	BOOST_TEST(trimmed == "Hello, World!");
}
BOOST_AUTO_TEST_CASE(StrAlgorithmCase1)
{
	std::string s = "apple,banana,cherry";
	std::vector<std::string> fruits;
	boost::algorithm::split(fruits, s, boost::is_any_of(",")); // 按逗号分割字符串
	BOOST_TEST(fruits.size() == 3);
	BOOST_TEST(fruits[0] == "apple");
	BOOST_TEST(fruits[1] == "banana");
	BOOST_TEST(fruits[2] == "cherry");
}
BOOST_AUTO_TEST_CASE(StrAlgorithmCase2)
{
	std::string s = "The quick brown fox";
	boost::algorithm::replace_all(s, "fox", "dog"); // 替换字符串中的子串
	BOOST_TEST(s == "The quick brown dog");
}
BOOST_AUTO_TEST_CASE(StrAlgorithmCase3)
{
	std::string s = "   Boost C++ Libraries   ";
	std::string trimmed = boost::algorithm::trim_copy(s); // 去除字符串两端的空白字符
	BOOST_TEST(trimmed == "Boost C++ Libraries");
}
BOOST_AUTO_TEST_CASE(StrAlgorithmCase4)
{
	std::string s = "one;two;three;four";
	std::vector<std::string> parts;
	boost::algorithm::split(parts, s, boost::is_any_of(";")); // 按分号分割字符串
	BOOST_TEST(parts.size() == 4);
	BOOST_TEST(parts[0] == "one");
	BOOST_TEST(parts[1] == "two");
	BOOST_TEST(parts[2] == "three");
	BOOST_TEST(parts[3] == "four");
}
//分类器：