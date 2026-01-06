#define CATCH_CONFIG_MAIN //引入Catch单元测试套件
#include<catch2\catch_amalgamated.hpp>
#include<boost/smart_ptr/scoped_ptr.hpp>//包含boost作用域头文件
#include<boost/smart_ptr/scoped_array.hpp>
#include<cstdlib>
struct DeadMenofDunharraw {//声明该类：接受空字符结尾的字符串
	DeadMenofDunharraw(const char* message="") :message{message}
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
using Scope = boost::scoped_ptr<DeadMenofDunharraw>;//声明该类型别名
using ScopeArray = boost::scoped_array<int>;
using Unique = std::unique_ptr<DeadMenofDunharraw>;
Unique uni{ new DeadMenofDunharraw };
auto uni2 = std::move(uni);//将所有权转移给uni2，uni被析构
TEST_CASE("unique_ptr test") {
	REQUIRE_FALSE(uni);
}
//确定作用域指针是否为空或者有一个对象
TEST_CASE("ScopedPtr is empty or") {
	SECTION("true or full") {
		Scope scop{ new DeadMenofDunharraw{} };
		REQUIRE(scop);//隐式bool转换：scop为空为false
	}
	SECTION("false when empty") {
		Scope scop;
		REQUIRE_FALSE(scop);
	}
	SECTION("~scoped_ptr test") {
		Scope scop{ new DeadMenofDunharraw{} };
		REQUIRE(scop->oaths_to_fullfill == 1);
		{
			Scope scop2{ new DeadMenofDunharraw };//在内部作用域生成一个对象
			REQUIRE(DeadMenofDunharraw::oaths_to_fullfill == 2);
		}//离开作用域并销毁一个对象
		REQUIRE(scop->oaths_to_fullfill == 1);
	}
	
}
TEST_CASE("ScopedPtr support pointer andsementics") {

	auto message = "helloworld";
	Scope scop{ new DeadMenofDunharraw{message} };
	SECTION("operator*") {
		REQUIRE((*scop).message == message);
	}
	SECTION("operator->") {
		REQUIRE(scop->message == message);
	}
	SECTION("get()") {
		REQUIRE(scop.get() != nullptr);//get 获取包装的指针
	}
	SECTION("==") {
		REQUIRE(scop != nullptr);//get 获取包装的指针
	}
	auto message1 = " no hello world";
	Scope scop1{ new DeadMenofDunharraw{message1} };
	scop1.swap(scop);
	SECTION("swap") {
		REQUIRE(scop1->message == message);
		REQUIRE((*scop).message == message1);
	}
	SECTION("reset") {
		scop.reset();//导致作用域指针销毁其拥有的对象
		//REQUIRE(scop==nullptr);//销毁对象后
		auto message2 = "hello world 3";
		REQUIRE(DeadMenofDunharraw::oaths_to_fullfill == 1);
		scop.reset(new DeadMenofDunharraw{ message2 });//销毁原有对象，将新对象作为scop拥有的动态对象
		//REQUIRE_FALSE(scop);
		REQUIRE(DeadMenofDunharraw::oaths_to_fullfill == 2);
		REQUIRE(scop->message == message2);
	}
	
}
void by_ref(Scope&) {};
void by_val(Scope) {};
TEST_CASE("Scope can") {
	Scope scop{ new DeadMenofDunharraw };
	SECTION("be passed by refrence") {
		by_ref(scop);
	}
	SECTION("be passed by value") {
		//auto scop1 = scop;无法编译
		//by_val(scop);无法编译
	}
	SECTION("be passed by move") {
		//auto scop1 = scop;无法编译
		//by_val(scop);无法编译
		//by_val(std::move(scop));
		//auto val = std::move(scop);
	}
}
ScopeArray scopa{ new int[5] {1,2,3,4,5} };
TEST_CASE("scoped_array test") {
	REQUIRE(scopa[1] == 2);
}