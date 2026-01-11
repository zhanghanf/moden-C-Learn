//关联容器：包含key建立和管理的容器，如set、map等。
//有效的插入操作：插入一个新元素，如果该元素的key已经存在，则插入失败。
//删除操作：删除指定key的元素。
//查找操作：根据key查找元素，返回对应的值或指示元素不存在。
//Boost在C++标准库的基础上，提供了更丰富的关联容器和算法支持。
#include<boost/test/unit_test.hpp>
#include<set>
//1.构造
BOOST_AUTO_TEST_CASE(test_set_construction)
{
	//默认构造函数
	std::set<int> s1;
	BOOST_CHECK(s1.empty());
	//初始化列表构造函数
	std::set<int> s2 = {1, 2, 3, 4, 5};
	BOOST_CHECK_EQUAL(s2.size(), 5);
	//拷贝构造函数
	std::set<int> s3(s2);
	BOOST_CHECK_EQUAL(s3.size(), 5);
	//移动构造函数
	std::set<int> s4(std::move(s3));
	BOOST_CHECK_EQUAL(s4.size(), 5);
	BOOST_CHECK(s3.empty());
	//类模板接受三个参数：key_type、Compare、Allocator：键值、比较函数、分配器
	std::set<int, std::greater<int>> s5 = {5, 4, 3, 2, 1};
	BOOST_CHECK_EQUAL(*s5.begin(), 5); //降序排列
}
//2.插入
BOOST_AUTO_TEST_CASE(test_set_insertion)
{
	std::set<int> s;
	//插入单个元素
	auto result1 = s.insert(10);
	BOOST_CHECK(result1.second); //插入成功
	BOOST_CHECK_EQUAL(s.size(), 1);
	//插入重复元素
	auto result2 = s.insert(10);
	BOOST_CHECK(!result2.second); //插入失败
	BOOST_CHECK_EQUAL(s.size(), 1);
	//插入多个元素
	s.insert({20, 30, 40});
	BOOST_CHECK_EQUAL(s.size(), 4);
}
//元素访问
BOOST_AUTO_TEST_CASE(test_set_access)
{
	std::set<int> s = {10, 20, 30, 40, 50};
	//查找元素
	auto it = s.find(30);//接受一个key参数，返回指向该元素的迭代器
	BOOST_CHECK(it != s.end());
	BOOST_CHECK_EQUAL(*it, 30);
	//查找不存在的元素
	it = s.find(60);
	BOOST_CHECK(it == s.end());
	//计数元素
	size_t count = s.count(20);//接受一个key参数，返回该key的元素个数
	BOOST_CHECK_EQUAL(count, 1);
	count = s.count(60);
	BOOST_CHECK_EQUAL(count, 0);
	//范围查找
	auto range = s.equal_range(30);//接受一个key参数，返回一个pair，表示该key的范围
	BOOST_CHECK_EQUAL(*range.first, 30);
	BOOST_CHECK_EQUAL(*range.second, 40);
	//lower_bound和upper_bound
	auto lower = s.lower_bound(25);//返回第一个不小于key的元素的迭代器
	BOOST_CHECK_EQUAL(*lower, 30);
	auto upper = s.upper_bound(30);//返回第一个大于key的元素的迭代器
	BOOST_CHECK_EQUAL(*upper, 40);

}
//4.删除
BOOST_AUTO_TEST_CASE(test_set_deletion)
{
	std::set<int> s = {10, 20, 30, 40, 50};
	//按key删除元素
	size_t erased = s.erase(30);//接受一个key参数，返回删除的元素个数
	BOOST_CHECK_EQUAL(erased, 1);
	BOOST_CHECK_EQUAL(s.size(), 4);
	//按迭代器删除元素
	auto it = s.find(20);
	s.erase(it);//接受一个迭代器参数，删除该位置的元素
	BOOST_CHECK_EQUAL(s.size(), 3);
	//按范围删除元素
	auto it1 = s.find(40);
	auto it2 = s.end();
	s.erase(it1, it2);//接受两个迭代器参数，删除该范围内的元素
	BOOST_CHECK_EQUAL(s.size(), 2);
	//清空容器
	s.clear();
	BOOST_CHECK(s.empty());
}
//存储自定义类型：集合的操作很快，通常被实现为平衡二叉树（如红黑树），插入、删除和查找操作的时间复杂度为O(log n)。
//支持的操作：插入、删除、查找、计数、范围查找等操作。
//如果存储多个具有相同key的元素，可以使用multiset容器。
struct Person
{
	std::string name;
	int age;
	//定义比较函数
	bool operator<(const Person& other) const
	{
		return name < other.name; //按名字排序
	}
};
BOOST_AUTO_TEST_CASE(test_set_custom_type)
{
	std::set<Person> people;
	people.insert({"Alice", 30});
	people.insert({"Bob", 25});
	people.insert({"Charlie", 35});
	BOOST_CHECK_EQUAL(people.size(), 3);
	auto it = people.find({"Bob", 0});//只需提供name进行查找
	BOOST_CHECK(it != people.end());
	BOOST_CHECK_EQUAL(it->age, 25);
}
//总结：关联容器set提供了高效的元素管理方式，适用于需要快速查找和唯一性保证的场景。通过自定义类型和比较函数，可以灵活地存储和操作各种数据类型。
//Boost.Test框架为测试关联容器的功能提供了便利，确保代码的正确性和稳定性。
#include<boost/container/container_fwd.hpp>
//#include<boost/container/set.hpp>
boost::container::multiset<int> boost_set;
#include<unordered_set>
//无序集合：unordered_set和unordered_multiset，基于哈希表实现，提供平均O(1)的时间复杂度进行插入、删除和查找操作，适用于需要快速访问且不关心元素顺序的场景。
//有序集合：set和multiset，基于平衡二叉树实现，提供O(log n)的时间复杂度进行插入、删除和查找操作，适用于需要保持元素有序的场景。
//存储模型：unordered_set使用哈希表存储元素，set使用红黑树存储元素。
BOOST_AUTO_TEST_CASE(test_boost_unordered_set)
{
	std::unordered_set<int> uset;
	uset.insert(10);
	uset.insert(20);
	uset.insert(30);
	BOOST_CHECK_EQUAL(uset.size(), 3);
	auto it = uset.find(20);
	BOOST_CHECK(it != uset.end());
	BOOST_CHECK_EQUAL(*it, 20);
	uset.erase(10);
	BOOST_CHECK_EQUAL(uset.size(), 2);
}
//哈希函数有几个要求：1.接受一个参数，返回一个size_t类型的哈希值。2.相等的对象必须具有相同的哈希值。3.不同的对象尽量产生不同的哈希值，以减少冲突。4.它不会抛出异常
//构造函数：unordered_set接受三个模板参数：key_type、Hash、KeyEqual，分别表示键值类型、哈希函数类型和键值相等函数类型，分配器类型。
BOOST_AUTO_TEST_CASE(test_unordered_set_construction)
{
	//unordered_set支持与set等效的构造函数
	std::unordered_set<int> uset1; //默认构造函数
	BOOST_CHECK(uset1.empty());
	std::unordered_set<int> uset2 = {1, 2, 3, 4, 5}; //初始化列表构造函数
	BOOST_CHECK_EQUAL(uset2.size(), 5);
	std::unordered_set<int> uset3(uset2); //拷贝构造函数
	BOOST_CHECK_EQUAL(uset3.size(), 5);
	std::unordered_set<int> uset4(std::move(uset3)); //移动构造函数
	BOOST_CHECK_EQUAL(uset4.size(), 5);
	BOOST_CHECK(uset3.empty());
}
//支持的集合操作：插入、删除、查找、计数等操作，平均时间复杂度为O(1)。与set相同，除了不保证元素有序外，其他操作类似。
BOOST_AUTO_TEST_CASE(test_unordered_set_operations)
{
	std::unordered_set<int> uset = {10, 20, 30, 40, 50};
	//插入元素
	auto result1 = uset.insert(60);
	BOOST_CHECK(result1.second); //插入成功
	BOOST_CHECK_EQUAL(uset.size(), 6);
	auto result2 = uset.insert(20);
	BOOST_CHECK(!result2.second); //插入失败
	BOOST_CHECK_EQUAL(uset.size(), 6);
	//查找元素
	auto it = uset.find(30);
	BOOST_CHECK(it != uset.end());
	BOOST_CHECK_EQUAL(*it, 30);
	it = uset.find(70);
	BOOST_CHECK(it == uset.end());
	//删除元素
	size_t erased = uset.erase(40);
	BOOST_CHECK_EQUAL(erased, 1);
	BOOST_CHECK_EQUAL(uset.size(), 5);
}
//4.桶管理：unordered_set使用桶（buckets）来存储元素，桶的数量和负载因子（load factor）影响性能。
//基本的桶操作：bucket_count()返回桶的数量，load_factor()返回当前负载因子，max_load_factor()设置最大负载因子，rehash()调整桶的数量。
BOOST_AUTO_TEST_CASE(test_unordered_set_buckets)
{
	std::unordered_set<int> uset;
	uset.insert(10);
	uset.insert(20);
	uset.insert(30);
	size_t bucket_count = uset.bucket_count();
	BOOST_CHECK(bucket_count > 0);
	float load_factor = uset.load_factor();
	BOOST_CHECK(load_factor > 0.0f);
	uset.max_load_factor(1.0f);
	uset.rehash(10); //调整桶的数量
	BOOST_CHECK(uset.bucket_count() >= 10);
}

#include<map>

//映射容器：包含key-value对建立和管理的容器，如map、unordered_map等。：键值对是有序且唯一的
//使用映射的优点：快速查找、插入和删除操作，适用于需要根据键快速访问值的场景。，并且支持与集合类似的操作，如插入、删除、查找等。
//可用作关联数组：通过键访问对应的值，类似于数组的索引操作。
//1.钩造
//map接受4个模板参数：key_type、mapped_type、Compare、Allocator，分别表示键值类型、映射值类型、比较函数类型和分配器类型。
BOOST_AUTO_TEST_CASE(test_map_construction)
{
	//默认构造函数
	std::map<int, std::string> m1;
	BOOST_CHECK(m1.empty());
	//初始化列表构造函数
	std::map<int, std::string> m2 = {{1, "one"}, {2, "two"}, {3, "three"}};
	BOOST_CHECK_EQUAL(m2.size(), 3);
	//拷贝构造函数
	std::map<int, std::string> m3(m2);
	BOOST_CHECK_EQUAL(m3.size(), 3);
	//移动构造函数
	std::map<int, std::string> m4(std::move(m3));
	BOOST_CHECK_EQUAL(m4.size(), 3);
	BOOST_CHECK(m3.empty());
	//类模板接受四个参数：key_type、mapped_type、Compare、Allocator：键值、映射值、比较函数、分配器
	std::map<int, std::string, std::greater<int>> m5 = {{5, "five"}, {4, "four"}, {3, "three"}};
	BOOST_CHECK_EQUAL(m5.begin()->first, 5); //降序排列
	//存储类型：映射和集合都是用红黑树实现的，提供对元素的有序访问和高效操作。
}
//元素访问：
BOOST_AUTO_TEST_CASE(test_map_access)
{
	std::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
	//通过key访问值
	BOOST_CHECK_EQUAL(m[2], "two");
	//使用at()方法访问值
	BOOST_CHECK_EQUAL(m.at(3), "three");
	//查找元素
	auto it = m.find(1);
	BOOST_CHECK(it != m.end());
	BOOST_CHECK_EQUAL(it->second, "one");
	//查找不存在的元素
	it = m.find(4);
	BOOST_CHECK(it == m.end());
	//计数元素
	size_t count = m.count(2);
	BOOST_CHECK_EQUAL(count, 1);
	count = m.count(4);
	BOOST_CHECK_EQUAL(count, 0);
	//范围查找
	auto range = m.equal_range(2);
	BOOST_CHECK_EQUAL(range.first->first, 2);
	BOOST_CHECK_EQUAL(range.second->first, 3);
	//lower_bound和upper_bound
	auto lower = m.lower_bound(2);
	BOOST_CHECK_EQUAL(lower->first, 2);
	auto upper = m.upper_bound(2);
	BOOST_CHECK_EQUAL(upper->first, 3);
}
//插入和删除
BOOST_AUTO_TEST_CASE(test_map_insertion_deletion)
{
	std::map<int, std::string> m;
	//插入单个元素
	auto result1 = m.insert({1, "one"});
	BOOST_CHECK(result1.second); //插入成功
	BOOST_CHECK_EQUAL(m.size(), 1);
	//插入重复元素
	auto result2 = m.insert({1, "uno"});
	BOOST_CHECK(!result2.second); //插入失败
	BOOST_CHECK_EQUAL(m.size(), 1);
	//插入多个元素
	m.insert({{2, "two"}, {3, "three"}});
	BOOST_CHECK_EQUAL(m.size(), 3);
	//按key删除元素
	size_t erased = m.erase(2);
	BOOST_CHECK_EQUAL(erased, 1);
	BOOST_CHECK_EQUAL(m.size(), 2);
	//按迭代器删除元素
	auto it = m.find(1);
	m.erase(it);
	BOOST_CHECK_EQUAL(m.size(), 1);
	//按范围删除元素
	auto it1 = m.find(3);
	auto it2 = m.end();
	m.erase(it1, it2);
	BOOST_CHECK_EQUAL(m.size(), 0);
}