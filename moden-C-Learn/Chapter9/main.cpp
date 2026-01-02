#include<cstdio>
#include<cstdint>
int argc = 9;
int main(int argc, char** argv) {
	printf("Arguments:%d\n", argc);
	for (size_t i{}; i < argc; i++) {
		printf("%zd:%s\n", i,argv[i]);
	}
}
//main函数有效重载变体
