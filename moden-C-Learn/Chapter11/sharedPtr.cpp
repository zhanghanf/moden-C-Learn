#include<boost/smart_ptr/shared_ptr.hpp>
#include<catch2/catch_amalgamated.hpp>
//共享指针构造
struct DeadMenofDunharraw {//声明该类：接受空字符结尾的字符串
	DeadMenofDunharraw(const char* message = "") :message{ message }
	{
		oaths_to_fullfill++;//构造函数递增：记录该类对象个数
	}
	~DeadMenofDunharraw() {
		//delete[]message;
		oaths_to_fullfill--;//表示有一个对象被释放
	}
	const char* message;
	static int oaths_to_fullfill;
};
int DeadMenofDunharraw::oaths_to_fullfill = 0;
std::shared_ptr<int> sp{ new int{808} };//两次分配
auto myptr = std::make_shared<int>(808);//将参数转发给指向类型的构造函数
//指定分配器
std::shared_ptr<int> sh{
	new int,
	[](int* x) {delete x; },
	std::allocator<int>{}
};
using Share = std::shared_ptr<DeadMenofDunharraw>;
TEST_CASE("shartPtr test") {//支持复制语义
	auto arg = std::make_shared<DeadMenofDunharraw>();
	SECTION("construction") {
		auto share{ arg };
		REQUIRE(share->oaths_to_fullfill == 1);
	}
	SECTION("assignment") {
		Share share_p;
		share_p = arg;
		REQUIRE(DeadMenofDunharraw::oaths_to_fullfill == 1);

	}
	SECTION("orignal get discard") {
		auto son_of_arathors = std::make_shared<DeadMenofDunharraw>();
		REQUIRE(DeadMenofDunharraw::oaths_to_fullfill == 2);
		son_of_arathors = arg;//此时两个指针共享对象
		REQUIRE(DeadMenofDunharraw::oaths_to_fullfill == 1);
		REQUIRE(arg.get()->oaths_to_fullfill == 1);
	}
}
