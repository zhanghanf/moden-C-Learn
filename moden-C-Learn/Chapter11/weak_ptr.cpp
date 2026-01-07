#include<boost/smart_ptr//weak_ptr.hpp>
#include<catch2/catch_amalgamated.hpp>
//弱指针
//不直接拥有对象
auto sp = std::make_shared<int>(33);
std::weak_ptr<int> wk{ sp };

//痛过lock获取临时对象所有权。
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
TEST_CASE("weakPtr lock() yields") {
	auto message = "the way to shut";
	SECTION(" a shared pointer when trach object alive") {
		auto araorn = std::make_shared<DeadMenofDunharraw>( message );
		std::weak_ptr<DeadMenofDunharraw> wlegolas{ araorn };
		auto sh = wlegolas.lock();//创建一个共享指针，如果被跟踪对象还在，返回被跟踪对象，否则返回空
		REQUIRE(sh->message == message);
		REQUIRE(sh.use_count() == 1);

	}
	SECTION("lock test") {
		std::weak_ptr<DeadMenofDunharraw> wkPtr;
		{
			auto araorn = std::make_shared<DeadMenofDunharraw>();
			wkPtr = araorn;//获取
			REQUIRE(wkPtr.expired());//跟踪对象存在
		}
		auto sh_ptr = wkPtr.lock();
		REQUIRE(nullptr == sh_ptr);
		REQUIRE(0 == sh_ptr.use_count());
	}
}