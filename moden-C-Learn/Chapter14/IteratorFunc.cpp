//如果使用迭代器编写泛型编程代码，则使用头文件的迭代器辅助函数来简化代码编写
//使用辅助函数的优势在于它们可以隐藏迭代器的复杂性，使代码更易读、更易维护
#define BOOST_TEST_MODULE IteratorFunc
#include <vector>
//advance函数用于将迭代器前进指定的步数
#include <iterator>
#include<boost/test/auto_unit_test.hpp>
BOOST_AUTO_TEST_CASE(IeratorFunc) {
	//next和prev函数用于获取迭代器的下一个或上一个位置的迭代器
	BOOST_CHECK_EQUAL(*std::next(std::vector<int>{1, 2, 3}.begin()), 2);
}
//end函数用于获取容器的结束迭代器
BOOST_AUTO_TEST_CASE(EndFunc) {
	std::vector<int> vec = { 1, 2, 3, 4, 5 };
	auto it = std::end(vec);
	--it; // 移动到最后一个元素
	BOOST_CHECK_EQUAL(*it, 5);
	//使用end函数可以避免直接操作迭代器，提高代码的可读性
	//std::distance函数用于计算两个迭代器之间的距离
	BOOST_CHECK_EQUAL(std::distance(std::begin(vec), std::end(vec)), 5);
	//iter_swap函数用于交换两个迭代器所指向的元素
	std::vector<int> vec2 = { 10, 20 };
	std::iter_swap(std::begin(vec2), std::end(vec2) - 1);
	BOOST_CHECK_EQUAL(vec2[0], 20);

}
//其他类型迭代器辅助函数
BOOST_AUTO_TEST_CASE(OtherIeratorFunc) {
	std::vector<int> vec = { 1, 2, 3, 4, 5 };
	auto it = std::begin(vec);
	//使用std::advance将迭代器前进3个位置
	std::advance(it, 3);
	BOOST_CHECK_EQUAL(*it, 4);
	//使用std::prev获取前一个位置的迭代器
	auto it_prev = std::prev(it);
	BOOST_CHECK_EQUAL(*it_prev, 3);
	

}
//移动迭代器适配器
struct Moveable {
	Moveable(int v) : value(v) {}
	int value;
	Moveable(Moveable&& other) noexcept : value(other.value) {
		other.value = 0; // 标记为已移动
	}
};
BOOST_AUTO_TEST_CASE(MoveIteratorAdapter) {
	std::vector<Moveable> vec;
	vec.emplace_back(1);
	vec.emplace_back(2);
	vec.emplace_back(3);
	//使用std::make_move_iterator创建移动迭代器
	auto move_begin = std::make_move_iterator(std::begin(vec));
	auto move_end = std::make_move_iterator(std::end(vec));
	std::vector<Moveable> moved_vec(move_begin, move_end);//移动元素到新的容器
	BOOST_CHECK_EQUAL(moved_vec.size(), 3);
	BOOST_CHECK_EQUAL(moved_vec[0].value, 1);
	BOOST_CHECK_EQUAL(moved_vec[1].value, 2);
	BOOST_CHECK_EQUAL(moved_vec[2].value, 3);
	//原始容器中的元素已被移动，值应为0
	BOOST_CHECK_EQUAL(vec[0].value, 0);
	BOOST_CHECK_EQUAL(vec[1].value, 0);
	BOOST_CHECK_EQUAL(vec[2].value, 0);
}
//反向迭代器适配器
BOOST_AUTO_TEST_CASE(ReverseIteratorAdapter) {
	std::vector<int> vec = { 1, 2, 3, 4, 5 };
	//使用std::make_reverse_iterator创建反向迭代器
	auto rbegin = std::make_reverse_iterator(std::end(vec));
	auto rend = std::make_reverse_iterator(std::begin(vec));
	std::vector<int> reversed_vec(rbegin, rend); // 反向复制元素到新的容器
	BOOST_CHECK_EQUAL(reversed_vec.size(), 5);
	BOOST_CHECK_EQUAL(reversed_vec[0], 5);
	BOOST_CHECK_EQUAL(reversed_vec[1], 4);
	BOOST_CHECK_EQUAL(reversed_vec[2], 3);
	BOOST_CHECK_EQUAL(reversed_vec[3], 2);
	BOOST_CHECK_EQUAL(reversed_vec[4], 1);
}