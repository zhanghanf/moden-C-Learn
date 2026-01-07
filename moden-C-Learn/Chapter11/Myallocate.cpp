#include<new>
#include<iostream>
#include<catch2/catch_amalgamated.hpp>
#include<boost/smart_ptr/shared_ptr.hpp>
static size_t n_allocate, d_allocate;
template<typename T>
struct MyAllocate {
	using value_type = T;
	MyAllocate()noexcept {

	};
	template<typename U>
	MyAllocate(const MyAllocate<U>&)noexcept {

	};
	T* allocate(size_t n) {
		auto p = operator new(sizeof(T) * n);
		++n_allocate;
		return static_cast<T*>(p);
	}
	void deallocate(T* p, size_t n) {
		operator delete(p);
		++d_allocate;
	}
};
template<typename T1, typename T2>
bool operator==(const MyAllocate<T1>&, const MyAllocate<T2>&) {

	return true;
}
template<typename T1, typename T2>
bool operator!=(const MyAllocate<T1>&, const MyAllocate<T2>&) {
	return false;
}
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
TEST_CASE("my allocate test") {
	auto message = "thw way is shut";
	MyAllocate<DeadMenofDunharraw> alloc;
	{
		auto aragorn = std::allocate_shared<DeadMenofDunharraw>(alloc,message);//分配器构造
		REQUIRE(aragorn->message == message);
	}
}