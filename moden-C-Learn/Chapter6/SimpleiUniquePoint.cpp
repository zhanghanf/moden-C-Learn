#include "SimpleiUniquePoint.h"
#include<utility>

struct Tracer {
	Tracer(const char* n) :name(n) {
		std::printf("Constructing %s\n", name);
	}
	~Tracer() {
		std::printf("Destructing %s\n", name);
	}

private:
	const char*const name;
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
int main() {
	testSimpleiUniquePoint();
	return 0;
}