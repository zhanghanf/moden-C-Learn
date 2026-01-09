// Chapter13.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//容器
#define BOOST_TEST_MODULE MyTest //设置测试模块的名称，如果有多个测试文件，名称必须相同
#include<boost/test/included/unit_test.hpp>
//使用boost test框架
BOOST_AUTO_TEST_CASE(hello) {
	BOOST_CHECK(true);
}
//BOOST_AUTO_TEST_CASE传入的必须是一个标识符，不能有空格等特殊字符
//在单元测试中使用测试装置，使用BOOST_FIXTURE_TEST_CASE宏
struct MyFixture {
	MyFixture() {
		//初始化代码
	}
	~MyFixture() {
		//清理代码
	}
	int value = 42;
};
BOOST_FIXTURE_TEST_CASE(test_with_fixture, MyFixture) {
	BOOST_CHECK(value == 42);
}
//BOOST_FIXTURE_TEST_CASE传入的第一个参数是测试用例的名称，第二个参数是测试装置的类型