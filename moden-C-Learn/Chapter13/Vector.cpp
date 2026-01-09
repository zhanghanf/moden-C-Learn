//向量：
#define BOOST_TEST_MODULE VectorTestModule
#include<boost/test/included/unit_test.hpp>
#include <vector>
#include <deque>

BOOST_AUTO_TEST_SUITE(VectorTest)
//元素访问测试
//1.构造
BOOST_AUTO_TEST_CASE(VectorTestSuite) {
	std::vector<int> vec1; //默认构造函数
	BOOST_CHECK(vec1.empty());
	std::vector<int> vec2(5, 10); //带初始大小和默认值的构造函数
	BOOST_CHECK_EQUAL(vec2.size(), 5);//BOOST_CHECK_EQUAL用于检查vec2的大小是否为5
	std::vector<int> vec3 = { 1, 2, 3, 4, 5 }; //初始化列表构造函数
	BOOST_CHECK_EQUAL(vec3.size(), 5);//BOOST_CHECK_EQUAL用于检查vec3的大小是否为5
	//从某个范围构造
	std::vector<int> vec4(vec3.begin(), vec3.end());
	BOOST_CHECK_EQUAL(vec4.size(), 5);//BOOST_CHECK_EQUAL用于检查vec4的大小是否为5

	//移动语义与复制语义
	std::vector<int> vec5 = vec3; //复制构造
	BOOST_CHECK_EQUAL(vec5.size(), 5);//BOOST_CHECK_EQUAL用于检查vec5的大小是否为5
	std::vector<int> vec6 = std::move(vec3); //移动构造
	BOOST_CHECK_EQUAL(vec6.size(), 5);//BOOST_CHECK_EQUAL用于检查vec6的大小是否为5
}
//2.元素访问
std::vector<int> vec = { 10, 20, 30, 40, 50 };
BOOST_AUTO_TEST_CASE(VectAccessTest) {
	//测试
	BOOST_CHECK_EQUAL(vec.at(2), 30); //使用at()方法访问元素
	BOOST_CHECK(vec[2] == 30); //使用下标操作符访问元素
	BOOST_CHECK_EQUAL(vec.front(), 10); //访问第一个元素
	//BOOST_CHECK_EQUAL和BOOST_CHECK区别是：BOOST_CHECK_EQUAL用于比较两个值是否相等，而BOOST_CHECK用于检查一个条件是否为真。
	BOOST_CHECK_EQUAL(vec.back(), 50); //访问最后一个元素
	//data
	BOOST_CHECK(vec.data()[1] == 20); //使用data()方法获取底层数组指针并访问元素

}

//删除元素
BOOST_AUTO_TEST_CASE(VectorEraseTest) {
	std::vector<int> v2 = { 1,2,3,4,5,6,7,8,9 };
	auto it = v2.begin() + 4;
	v2.erase(it); //删除单个元素
	BOOST_CHECK_EQUAL(v2.size(), 8);
	BOOST_CHECK_EQUAL(v2[4], 6); //检查删除后第五个元素是否为6
	auto it_start = v2.begin() + 2;
	auto it_end = v2.begin() + 5;
	v2.erase(it_start, it_end); //删除一个范围内的元素
	BOOST_CHECK_EQUAL(v2.size(), 5);
	BOOST_CHECK_EQUAL(v2[2], 7); //检查删除后第三个元素是否为7
	//清空元素
	v2.clear();
	BOOST_CHECK(v2.empty()); //检查向量是否为空
}
//添加元素
BOOST_AUTO_TEST_CASE(VectorIteratorTest) {
	vec.assign({ 100, 200, 300 }); //使用assign方法重新分配元素
	BOOST_CHECK_EQUAL(vec.size(), 3); //检查大小是否为3
	BOOST_CHECK_EQUAL(vec[0], 100); //检查第一个元素是否为100
	BOOST_CHECK_EQUAL(vec[1], 200); //检查第二个元素是否为200
	//向量insert方法
	std::vector<int> v1(3, 0);


	auto end = v1.begin() + 2;
	v1.insert(end, 100);//使用inset后。所有迭代器都失效
	BOOST_CHECK_EQUAL(v1.size(), 4);
	BOOST_CHECK_EQUAL(v1[2], 100);


	//如果在元素尾端插入元素，只有end迭代器失效
	v1.push_back(400);
	BOOST_CHECK_EQUAL(v1.size(), 5);
	//使用emplace_back在末尾构造元素:可变参数模板
	v1.emplace_back(10);
	//emplace方法：第一个参数为迭代器
	auto it = v1.begin() + 1;
	v1.emplace(it, 555);//指定位置插入
	//知道向量还有多少容量
	BOOST_CHECK(v1.capacity() >= v1.size());
}
	//结束
//测试向量
std::vector<std::pair<int, std::string>> vec_pair;
//BOOST_TEST是BOOST_AUTO_TEST_CASE的简写
BOOST_AUTO_TEST_CASE(VectorPairTest) {
	vec_pair.emplace_back(1, "one");
	vec_pair.emplace_back(2, "two");
	BOOST_CHECK_EQUAL(vec_pair.size(), 2);
	BOOST_CHECK_EQUAL(vec_pair[0].first, 1);
	BOOST_CHECK_EQUAL(vec_pair[0].second, "one");
	BOOST_CHECK_EQUAL(vec_pair[1].first, 2);
	BOOST_CHECK_EQUAL(vec_pair[1].second, "two");
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(DequeTest) 
//双端队列
BOOST_AUTO_TEST_CASE(DequeBasicTest) {
	std::deque<int> deq;
	BOOST_CHECK(deq.empty());
	deq.push_back(10);//在末尾添加元素
	deq.push_front(20);//在前端添加元素
	BOOST_CHECK_EQUAL(deq.size(), 2);
	BOOST_CHECK_EQUAL(deq.front(), 20);
	BOOST_CHECK_EQUAL(deq.back(), 10);
	deq.pop_front();//删除前端元素
	BOOST_CHECK_EQUAL(deq.size(), 1);
	BOOST_CHECK_EQUAL(deq.front(), 10);
	deq.pop_back();//删除末尾元素
	//emplace_front与emplace_back:将素有参数转发给元素的构造函数，在队列的前端或末尾构造元素
	deq.emplace_front(30);
	BOOST_CHECK_EQUAL(deq.front(), 30);
}
BOOST_AUTO_TEST_SUITE_END()


//列表
#include <list>
BOOST_AUTO_TEST_SUITE(ListTest)
BOOST_AUTO_TEST_CASE(ListBasicTest) {
	std::list<int> lst;
	BOOST_CHECK(lst.empty());
	lst.push_back(10);//
	lst.push_front(20);//在前端添加元素
	BOOST_CHECK_EQUAL(lst.size(), 2);
	BOOST_CHECK_EQUAL(lst.front(), 20);
	BOOST_CHECK_EQUAL(lst.back(), 10);
	lst.pop_front();//删除前端元素
	BOOST_CHECK_EQUAL(lst.size(), 1);
	BOOST_CHECK_EQUAL(lst.front(), 10);
	lst.pop_back();//删除末尾元素
	BOOST_CHECK(lst.empty());
	//插入元素
	lst.emplace_back(30);
	BOOST_CHECK_EQUAL(lst.back(), 30);
	lst.emplace_front(40);
	BOOST_CHECK_EQUAL(lst.front(), 40);
	//列表支持remove_if
	std::list<int> mlst2 = { 11,22,33,44,55,66,77,88,99 };
	//mlst2.remove_if([](int x) { return x % 2 == 0; }); //删除所有偶数
	mlst2.remove_if([](auto x) {return x % 2 == 0; });
	auto it = mlst2.begin();
	++it;
	BOOST_CHECK_EQUAL(*it, 33);
	mlst2.remove(33);//删除等于3的元素
	it = mlst2.begin();
	++it;
	BOOST_CHECK_EQUAL(*it, 55);
	//merge合并两个链表
	//lst.merge(mlst2, [](int x, int y) {return x <= y; });
}
BOOST_AUTO_TEST_SUITE_END()