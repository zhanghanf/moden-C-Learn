
#define BOOST_TEST_MODULE BasicStringTest
#include<boost/test/unit_test.hpp>
#include<string>
using std::string;
//STL在头文件中提供了4种基本字符串类型，分别是std::string、std::wstring、std::u16string和std::u32string。
//它们分别对应不同的字符类型：char：ASCII之类的、wchar_t包含实现语言环境的最大字符、char16_tUTF-16之类的和char32_t 指UTF-32之类的。
//构造字符串
//basic_string容器使用三个模板参数：字符类型T、字符特征Traits和分配器类型Alloc。大多数情况下，我们只需要指定字符类型T，Traits和Alloc使用默认值即可。
BOOST_AUTO_TEST_CASE(ConstructString)
{
	//默认构造函数，创建一个空字符串
	std::string str1;
	BOOST_CHECK(str1.empty());
	//使用C风格字符串初始化
	const char* cstr = "hello word";
	std::string str2(cstr);
	BOOST_CHECK_EQUAL(str2, "hello word");
	//使用指定长度的C风格字符串初始化
	string str3(cstr, 5);
	BOOST_CHECK_EQUAL(str3, "hello");
	//使用重复字符初始化
	std::string str4(10, 'A');
	BOOST_CHECK_EQUAL(str4, "AAAAAAAAAA");
	//使用迭代器范围初始化
	std::string str5(str2.begin(), str2.begin() + 5);
	BOOST_CHECK_EQUAL(str5, "hello");
}
//复制构造函数、移动构造函数和子串构造函数
BOOST_AUTO_TEST_CASE(CopyMoveSubstringConstruct)
{
	std::string original = "Hello,World!";
	//复制构造函数
	std::string copy(original);
	BOOST_CHECK_EQUAL(copy, original);
	//移动构造函数
	std::string moved(std::move(original));
	BOOST_CHECK_EQUAL(moved, "Hello,World!");
	BOOST_CHECK(original.empty()); // original is in a valid but unspecified state
	//子串构造函数
	std::string substring(moved, 7, 4);//从下标7开始的5个字符
	BOOST_CHECK_EQUAL(substring, "orld");
}
//字符串储存和小字符串优化
//和vector一样，string使用动态存储空间来连续存储其中的元素
//实现：SSO：小字符串优化：小于24字节一般放在对象存储区域：而非动态存储空间
//string的大小可以通过size()或length()成员函数获取和容量可以通过capacity()成员函数获取
BOOST_AUTO_TEST_CASE(StringStorageAndSSO)
{
	std::string smallStr = "short string";
	BOOST_CHECK_LE(smallStr.size(), smallStr.capacity());
	//大字符串
	std::string largeStr(1000, 'A');
	BOOST_CHECK_LE(largeStr.size(), largeStr.capacity());
	//字符串长度调整
	largeStr.shrink_to_fit();
	BOOST_CHECK_LE(largeStr.size(), largeStr.capacity());
	largeStr.reserve(2000);//预留更多空间
	BOOST_CHECK_GE(largeStr.capacity(), 2000);
}
//元素和迭代器访问
BOOST_AUTO_TEST_CASE(ElementAndIteratorAccess1)
{
	std::string str = "Hello, World!";
	//使用下标访问元素
	BOOST_CHECK_EQUAL(str[7], 'W');
	//使用at()方法访问元素
	BOOST_CHECK_EQUAL(str.at(4), 'o');
	//使用front()和back()方法访问首尾元素
	BOOST_CHECK_EQUAL(str.front(), 'H');
	//BOOST_CHECK_EQUAL(str.back(), '!');
	//使用迭代器访问元素
	auto it = str.begin();
	BOOST_CHECK_EQUAL(*it, 'H');
	it += 7;
	BOOST_CHECK_EQUAL(*it, 'W');
	//c_str和data返回相同地址
	BOOST_CHECK_EQUAL(str.c_str(), str.data());
	auto it2= str.cbegin();//常量迭代器:不改变内容
	BOOST_CHECK_EQUAL(*it2, 'H');

}
//字符串比较
BOOST_AUTO_TEST_CASE(StringComparison)
{
	std::string str1 = "apple";
	std::string str2 = "banana";
	//使用比较运算符
	BOOST_CHECK(str1 < str2);
	BOOST_CHECK(str2 > str1);
	BOOST_CHECK(str1 != str2);
	//使用compare()方法
	BOOST_CHECK_EQUAL(str1.compare(str2), -1); // str1 < str2
	BOOST_CHECK_EQUAL(str2.compare(str1), 1);  // str2 > str1
	BOOST_CHECK_EQUAL(str1.compare("apple"), 0); // str1 == "apple"
	//C风格字符串比较
}
//操作元素
BOOST_AUTO_TEST_CASE(StringElementManipulation)
{
	std::string str = "Hello";
	//添加元素
	str.push_back(' ');
	str += "World";
	BOOST_CHECK_EQUAL(str, "Hello World");
	str.append("aa");
	BOOST_CHECK_EQUAL(str, "Hello Worldaa");
	string str2{ "hello" };
	str.append(str2, 1, 3); // 从str2的下标1开始，取3个字符
	BOOST_CHECK_EQUAL(str, "Hello Worldaaell");
	str.append(str2.begin(), str2.begin() + 2); // 从str2的迭代器范围添加字符
	BOOST_CHECK_EQUAL(str, "Hello Worldaaellhe");
	//删除元素
	str.pop_back();
	BOOST_CHECK_EQUAL(str, "Hello Worldaaellh");
	str.erase(5, 1); // 删除空格:从下标5开始，删除1个字符
	BOOST_CHECK_EQUAL(str, "HelloWorldaaellh");
	//插入元素
	str.insert(5, " ");//在下标5位置插入空格
	BOOST_CHECK_EQUAL(str, "Hello Worldaaellh");
	str.insert(str.end(), 'd');//在末尾插入字符
	BOOST_CHECK_EQUAL(str, "Hello Worldaaellhd");
	//替换元素
	str.replace(6, 4, "Universe");//替换从下标6开始的4个字符
	BOOST_CHECK_EQUAL(str, "Hello Universedaaellhd");
	str.resize(15, 'o');//调整字符串大小，新增字符用'o'填充
	BOOST_CHECK_EQUAL(str, "Hello Universed");
}
//查找和子串
//find\rfind\find_first_of\find_last_of\find_first_not_of\find_last_not_of
BOOST_AUTO_TEST_CASE(StringFindAndSubstring)
{
	std::string str = "Hello, World! Welcome to the World of C++.";
	//查找子串
	size_t pos1 = str.find("World");//查找第一次出现的位置
	BOOST_CHECK_EQUAL(pos1, 7);
	size_t pos2 = str.rfind("World");//查找最后一次出现的位置
	BOOST_CHECK_EQUAL(pos2, 26);
	size_t pos3 = str.find_first_of("aeiou");//查找第一个元音字母的位置
	BOOST_CHECK_EQUAL(pos3, 1); // 'e'的位置
	size_t pos4 = str.find_last_of("aeiou");//查找最后一个元音字母的位置
	BOOST_CHECK_EQUAL(pos4, 33); // 'o'的位置
	size_t pos5 = str.find_first_not_of("Helo, Wrd!");//查找第一个不在指定字符集合中的字符位置
	BOOST_CHECK_EQUAL(pos5, 13); // '!'后面的第一个字符 ' '
	size_t pos6 = str.find_last_not_of("C+.");//查找最后一个不在指定字符集合中的字符位置
	BOOST_CHECK_EQUAL(pos6, 36); // 'f'的位置
	//提取子串
	std::string substr1 = str.substr(7, 5); // 从下标7开始，长度为5的子串
	BOOST_CHECK_EQUAL(substr1, "World");
	std::string substr2 = str.substr(26); // 从下标26开始到结尾的子串
	BOOST_CHECK_EQUAL(substr2, "World of C++.");
}

//字符串转换
//STL提供了一些函数用于将字符串转换为数值类型，反之亦然
//to_string、stoi、stof等
BOOST_AUTO_TEST_CASE(StringConversion)
{
	//数值转字符串
	int intValue = 42;
	double doubleValue = 3.14159;
	std::string intStr = std::to_string(intValue);
	std::string doubleStr = std::to_string(doubleValue);
	BOOST_CHECK_EQUAL(intStr, "42");
	BOOST_CHECK_EQUAL(doubleStr.substr(0, 6), "3.1415"); // 只比较前6位
	//字符串转数值
	std::string str1 = "123";
	std::string str2 = "45.67";
	int intResult = std::stoi(str1);
	double doubleResult = std::stod(str2);
	BOOST_CHECK_EQUAL(intResult, 123);
	BOOST_CHECK_CLOSE(doubleResult, 45.67, 0.0001); // 使用BOOST_CHECK_CLOSE进行浮点数比较
	//如果无法转换，stoi/stod会抛出std::invalid_argument异常
	//转换后的值超出范围，会抛出std::out_of_range异常
	int badValue = std::stoi("abc");//
}

