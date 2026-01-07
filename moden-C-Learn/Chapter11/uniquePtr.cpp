#include<catch2/catch_amalgamated.hpp>
//#include<boost/smart_ptr/un>
#include<stdlib.h>
#include<cstdio>
#include<memory>
//删除器实例
auto my_del = [](int* x) {
	delete x;
	};
using fileGrund = std::unique_ptr<FILE, int(*)(FILE*)>;//int(*)(FILE*):指向函数的指针，删除器与fclose匹配
std::unique_ptr<int,decltype(my_del)> uni{new int{808} ,my_del};//使用自定义删除器
void say_hello(fileGrund file) {
	fprintf(file.get(), "hello AEVD");
}
int main() {
	FILE* fp = nullptr;
	auto file = fopen_s(&fp,"HAL600", "w");
	if (file!=0)return errno;
	fileGrund fg{ fp,fclose };
	say_hello(std::move(fg));
	return 0;
}