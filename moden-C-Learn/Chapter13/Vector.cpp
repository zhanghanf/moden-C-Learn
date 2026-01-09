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
	lst.sort([](int a, int b) {return a >= b; });
	mlst2.sort([](int a, int b) {return a >= b; });
	lst.merge(mlst2, [](int a, int b) {return a > b; });
}
BOOST_AUTO_TEST_SUITE_END()
//栈:针对定制情况公开了有限的接口
#include<stack>
BOOST_AUTO_TEST_SUITE(StackTest)
BOOST_AUTO_TEST_CASE(StackBasicTest) {
	std::stack<int> stk;
	BOOST_CHECK(stk.empty());
	stk.push(10);
	stk.push(20);
	BOOST_CHECK_EQUAL(stk.size(), 2);
	BOOST_CHECK_EQUAL(stk.top(), 20);
	stk.pop();
	BOOST_CHECK_EQUAL(stk.size(), 1);
	BOOST_CHECK_EQUAL(stk.top(), 10);
	stk.pop();
	BOOST_CHECK(stk.empty());
}
//使用栈包装向量
BOOST_AUTO_TEST_CASE(StackVectorTest) {
	std::stack<int, std::vector<int>> stk_vec;
	BOOST_CHECK(stk_vec.empty());
	stk_vec.push(100);
	stk_vec.push(200);
	BOOST_CHECK_EQUAL(stk_vec.size(), 2);
	BOOST_CHECK_EQUAL(stk_vec.top(), 200);
	stk_vec.pop();
	BOOST_CHECK_EQUAL(stk_vec.size(), 1);
	BOOST_CHECK_EQUAL(stk_vec.top(), 100);
	stk_vec.pop();
	BOOST_CHECK(stk_vec.empty());
	//emplace测试
	stk_vec.emplace(300);
	BOOST_CHECK_EQUAL(stk_vec.top(), 300);
	auto v2{ stk_vec };
	BOOST_CHECK_EQUAL(v2.top(), 300);
	stk_vec.push(400);
	v2.swap(stk_vec);
	BOOST_CHECK_EQUAL(v2.top(), 400);
}
BOOST_AUTO_TEST_SUITE_END()
//队列:队列是一种先进先出（FIFO）的数据结构
#include<queue>
BOOST_AUTO_TEST_SUITE(QueueTest)
BOOST_AUTO_TEST_CASE(QueueBasicTest) {
	std::queue<int> que;
	BOOST_CHECK(que.empty());
	que.push(10);
	que.push(20);
	BOOST_CHECK_EQUAL(que.size(), 2);
	BOOST_CHECK_EQUAL(que.front(), 10);
	BOOST_CHECK_EQUAL(que.back(), 20);
	que.pop();
	BOOST_CHECK_EQUAL(que.size(), 1);
	BOOST_CHECK_EQUAL(que.front(), 20);
	que.pop();
	BOOST_CHECK(que.empty());
}
BOOST_AUTO_TEST_SUITE_END()
//优先队列
#include<queue>
BOOST_AUTO_TEST_SUITE(PriorityQueueTest)
BOOST_AUTO_TEST_CASE(PriorityQueueBasicTest) {
	std::priority_queue<int> pque;//默认是最大堆
	BOOST_CHECK(pque.empty());
	pque.push(30);
	pque.push(10);
	pque.push(20);
	BOOST_CHECK_EQUAL(pque.size(), 3);
	BOOST_CHECK_EQUAL(pque.top(), 30); //最大元素在顶部
	pque.pop();
	BOOST_CHECK_EQUAL(pque.size(), 2);
	BOOST_CHECK_EQUAL(pque.top(), 20);
	pque.pop();
	BOOST_CHECK_EQUAL(pque.size(), 1);
	BOOST_CHECK_EQUAL(pque.top(), 10);
	pque.pop();
	BOOST_CHECK(pque.empty());
	//三个底层元素模板参数
	std::priority_queue<int, std::vector<int>, std::greater<int>> min_pque; //最小堆（被包装类型，底层容器，比较函数）
	BOOST_CHECK(min_pque.empty());
	min_pque.push(30);
	min_pque.push(10);
	min_pque.push(20);
	BOOST_CHECK_EQUAL(min_pque.size(), 3);
	BOOST_CHECK_EQUAL(min_pque.top(), 10); //最小元素在顶部
	min_pque.pop();
	BOOST_CHECK_EQUAL(min_pque.size(), 2);
	BOOST_CHECK_EQUAL(min_pque.top(), 20); //最小元素在顶部
}
BOOST_AUTO_TEST_SUITE_END()
//6.位级别操作的序列容器：存储固定大小的位序列数据结构
//作用：节省内存，进行位操作
#include <bitset>
BOOST_AUTO_TEST_SUITE(BitsetTest)
BOOST_AUTO_TEST_CASE(BitsetBasicTest) {
	//初始化一个8位的位集
	std::bitset<8> bits1(0b11100011); //默认初始化为0
	std::bitset<8> bits2("10101011"); //默认初始化为0
	BOOST_CHECK_EQUAL(bits1.size(), 8);
	std::bitset<8> bits; //默认初始化为0
	BOOST_CHECK_EQUAL(bits.size(), 8);
	BOOST_CHECK_EQUAL(bits.count(), 0); //count()返回设置为1的位数
	bits.set(2); //将索引2的位设置为1
	BOOST_CHECK_EQUAL(bits.test(2), true); //test()检查索引2的位是否为1
	BOOST_CHECK_EQUAL(bits.count(), 1);
	bits.set(4);
	BOOST_CHECK_EQUAL(bits.count(), 2);
	bits.reset(2); //将索引2的位重置为0
	BOOST_CHECK_EQUAL(bits.test(2), false);
	BOOST_CHECK_EQUAL(bits.count(), 1);
	bits.flip(4); //翻转索引4的位
	BOOST_CHECK_EQUAL(bits.test(4), false);
	BOOST_CHECK_EQUAL(bits.count(), 0);
	bits.flip(); //翻转所有位
	BOOST_CHECK_EQUAL(bits.count(), 8);
	BOOST_CHECK_EQUAL(bits.to_string(), "11111111"); //将位集转换为字符串表示
}
BOOST_AUTO_TEST_SUITE_END()
//动态位集
#include <boost/dynamic_bitset.hpp>
BOOST_AUTO_TEST_SUITE(DynamicBitsetTest)
BOOST_AUTO_TEST_CASE(DynamicBitsetBasicTest) {
	boost::dynamic_bitset<> dbits(8); //初始化一个8位的动态位集，默认值为0
	BOOST_CHECK_EQUAL(dbits.size(), 8);
	BOOST_CHECK_EQUAL(dbits.count(), 0); //count()返回设置为1的位数
	dbits.set(3); //将索引3的位设置为1
	BOOST_CHECK_EQUAL(dbits.test(3), true); //test()检查索引3的位是否为1
	BOOST_CHECK_EQUAL(dbits.count(), 1);
	dbits.set(5);
	BOOST_CHECK_EQUAL(dbits.count(), 2);
	dbits.reset(3); //将索引3的位重置为0
	BOOST_CHECK_EQUAL(dbits.test(3), false);
	BOOST_CHECK_EQUAL(dbits.count(), 1);
	dbits.flip(5); //翻转索引5的位
	BOOST_CHECK_EQUAL(dbits.test(5), false);
	BOOST_CHECK_EQUAL(dbits.count(), 0);
	dbits.flip(); //翻转所有位
	BOOST_CHECK_EQUAL(dbits.count(), 8);
	//BOOST_CHECK_EQUAL(dbits., "11111111"); //将动态位集转换为字符串表示
}
BOOST_AUTO_TEST_SUITE_END()
//特殊的boost容器
#include <boost/container/small_vector.hpp>
//small_vector:在栈上分配小容量的向量，当超过该容量时，自动切换到堆分配
//侵入式容器：容器中的元素包含指向下一个和上一个元素的指针，从而形成链表结构
//没有连续元素的向量：boost::container::stable_vector
//支持高效的插入和删除操作，而不影响其他元素的地址
//具有快速size的单向链表：boost::container::slist
//多维数组：boost::multi_array：支持多维数组的创建和操作