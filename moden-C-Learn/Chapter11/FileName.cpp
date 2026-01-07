#include<boost/smart_ptr/intrusive_ptr.hpp>
#include<catch2/catch_amalgamated.hpp>
//侵入式指针
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
//使用这个指针，需要嵌入这两个函数，通过这两个函数来释放
using Interrusive = boost::intrusive_ptr<DeadMenofDunharraw>;
size_t count{};
void intrusive_ptr_add_ref(DeadMenofDunharraw* d) {
	count++;
}
void intrusive_ptr_release(DeadMenofDunharraw* d) {
	count--;
	if (count == 0) {
		delete d;
	}     ;

}
TEST_CASE("intrusive point used") {
	REQUIRE(count == 0);
	Interrusive ara{ new DeadMenofDunharraw{} };
	REQUIRE(count == 1);
	{
		Interrusive inter{ ara };
		REQUIRE(count == 2);
	}
}