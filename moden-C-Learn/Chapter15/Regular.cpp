#include<boost/test/unit_test.hpp>
#define BOOST_TEST_MODULE Regular
//正则表达式：定义了一种字符串模式，可以用来匹配、搜索和操作字符串。
#include <regex>//引入正则表达式库
//建立正则表达式
//1.模式字符串：模式使用特定的语法来定义字符串的结构。例如，"\\d+"表示一个或多个数字字符。
//2.正则表达式对象：使用模式字符串创建正则表达式对象，例如std::regex re("\\d+");
//1.字符类：常见的字符类包括\\d（数字）、\\w（字母、数字或下划线）、\\s（空白字符）等。
//[]表示字符类，例如[abc]表示匹配字符a、b或c中的任意一个。
//2.量词：量词用于指定前一个元素出现的次数。例如，*表示零次或多次，+表示一次或多次，?表示零次或一次。{n}表示恰好n次，{n,}表示至少n次，{n,m}表示n到m次。
//3.分组：使用括号()将多个元素组合在一起，形成一个子模式。例如，(abc)+表示匹配一个或多个连续的"abc"字符串。
//4.锚点：锚点用于指定匹配的位置。例如，^表示字符串的开头，$表示字符串的结尾，\\b表示单词边界。
//5.其他特殊字符：例如，.表示任意单个字符，|表示逻辑或操作，\\表示转义字符等。\n\r\t等表示换行、回车和制表符。

//basic_regex:从模式字符串创建正则表达式对象的类模板。
BOOST_AUTO_TEST_CASE(RegularCase0)
{
	std::string s = "Hello, World!";
	std::regex re("World");//匹配字符串"World"
	std::smatch match;
	if (std::regex_search(s, match, re)) {
		BOOST_TEST(match.str() == "World");
	} else {
		BOOST_TEST(false); // Should not reach here
	}
	std::regex zip{ R"((\w{2})?(-\d{4})?)" };//使用原始字面量构造
	BOOST_TEST_REQUIRE(zip.mark_count() == 2);
}
BOOST_AUTO_TEST_CASE(RegularCase1)
{
	std::string s = "abc123xyz";
	std::regex re("\\d+");//匹配一个或多个数字字符
	std::smatch match;
	if (std::regex_search(s, match, re)) {
		BOOST_TEST(match.str() == "123");
	} else {
		BOOST_TEST(false); // Should not reach here
	}
}
BOOST_AUTO_TEST_CASE(RegularCase2)
{
	std::string s = "The price is $100.50";
	std::regex re("\\$\\d+\\.\\d{2}");//匹配美元金额格式
	std::smatch match;
	if (std::regex_search(s, match, re)) {
		BOOST_TEST(match.str() == "$100.50");
	} else {
		BOOST_TEST(false); // Should not reach here
	}
}
//assign(s):将新的模式字符串s分配给正则表达式对象。
//mark_count():返回正则表达式中捕获组的数量。
//str():返回匹配的子字符串。
//flags():返回正则表达式对象的标志。

//assign测试
BOOST_AUTO_TEST_CASE(RegularCase3)
{
	std::string s = "Contact:12345678@qq.com";
	std::regex re("\\w+@\\w+\\.com");//初始模式，匹配电子邮件地址
	re.assign("\\w+");//重新分配模式，匹配单词字符
	std::smatch match;
	if (std::regex_search(s, match, re)) {
		BOOST_TEST(match.str() == "Contact");
	}
	else {
		BOOST_TEST(false); // Should not reach here
	}
}
//算法
//匹配算法：用于检查字符串是否与正则表达式匹配。
//regex_match():检查整个字符串是否与正则表达式完全匹配。有四个重载版本，分别用于不同类型的输入。
//：refex_match(const CharT* str, const std::basic_regex<CharT>& re, std::regex_constants::match_flag_type flags = std::regex_constants::match_default);
//常用的操作标志包括：
#include<regex>
#include<string>
BOOST_AUTO_TEST_CASE(RegularCase4)
{
	std::string s = "NJ12345-67";
	std::smatch re;
	std::regex rex{R"((\w{2})(\d{5})(-\d{4})?)"};
	//不区分大小写匹配
	const auto mathoud = std::regex_match(s, re, rex);
	BOOST_TEST(mathoud == true);
	BOOST_TEST(re.size() == 4); //整个匹配和三个捕获组
	BOOST_TEST(re[1].str() == "NJ");
	BOOST_TEST(re[2].str() == "12345");
	BOOST_TEST(re[3].str() == "-67");
}

//搜索算法：用于在字符串中查找与正则表达式匹配的子字符串。
//std::regex_search():在字符串中搜索与正则表达式匹配的子字符串。有四个重载版本，分别用于不同类型的输入。
BOOST_AUTO_TEST_SUITE(Regu)
BOOST_AUTO_TEST_CASE(RegularCase5)
{
	std::string s = "My phone number is 123-456-7890.";
	std::smatch match;
	std::regex re(R"((\d{3})-(\d{3})-(\d{4}))");//匹配电话号码格式
	if (std::regex_search(s, match, re)) {
		BOOST_TEST(match.str() == "123-456-7890");
		BOOST_TEST(match.size() == 4); //整个匹配和三个捕获组
		BOOST_TEST(match[1].str() == "123");
		BOOST_TEST(match[2].str() == "456");
		BOOST_TEST(match[3].str() == "7890");
	} else {
		BOOST_TEST(false); // Should not reach here
	}
}
//match和search的区别在于：match要求整个字符串与正则表达式完全匹配，而search只要求字符串中存在与正则表达式匹配的子字符串。
//替换算法：用于将字符串中与正则表达式匹配的部分替换为指定的字符串。
BOOST_AUTO_TEST_CASE(RegularCase6)
{
	std::string s = "The color is red.";
	std::regex re("red");//匹配字符串"red"
	std::string result = std::regex_replace(s, re, "blue");//将"red"替换为"blue"
	BOOST_TEST(result == "The color is blue.");
}
BOOST_AUTO_TEST_SUITE_END()