#pragma once
#include<cstdio>
template<typename T>
class SimpleiUniquePoint
{
public:
	SimpleiUniquePoint() = default;
	explicit SimpleiUniquePoint(T* p):ptr(p){}
	~SimpleiUniquePoint() {
		if (ptr) { delete ptr; ptr = nullptr; }
	}
	SimpleiUniquePoint& operator=(const SimpleiUniquePoint&) = delete;
	SimpleiUniquePoint(const SimpleiUniquePoint&) = delete;
	SimpleiUniquePoint(SimpleiUniquePoint&& other) noexcept :ptr(other.ptr) {
		other.ptr = nullptr;
	}
	SimpleiUniquePoint& operator=(SimpleiUniquePoint&& other) noexcept {
		if (this != &other) {
			if (ptr) { delete ptr; ptr = nullptr; }
			ptr = other.ptr;
			other.ptr = nullptr;
		}
		return *this;
	}
	T& operator*() {
		return *ptr;
	}
	T*get() {
		return ptr;
	}
private:
	T* ptr;
};

#include<utility>

struct Tracer {
	Tracer(const char* n) :name(n) {
		std::printf("Constructing %s\n", name);
	}
	~Tracer() {
		std::printf("Destructing %s\n", name);
	}

private:
	const char* const name;
};
void testSimpleiUniquePoint() {
	SimpleiUniquePoint<Tracer> p1(new Tracer("p1"));
	{
		SimpleiUniquePoint<Tracer> p2(new Tracer("p2"));
		p1 = std::move(p2);
		printf("ptr_p1%p\n", p2.get());
	}
	printf("ptr_p1%p\n", p1.get());
	SimpleiUniquePoint<Tracer> p3 = std::move(p1);
	printf("ptr_p1%p\n", p1.get());
	//printf("ptr_p1%p\n", p2.get());
}
