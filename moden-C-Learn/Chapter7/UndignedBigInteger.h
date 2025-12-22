#pragma once
//处理long类型无符号大整数的类
class UndignedBigInteger
{
	public:
	UndignedBigInteger() {
		data = new uint8_t[128]{0};
		length = 0;
	}
	UndignedBigInteger(uint64_t value) {
		data = new uint8_t[128]{0};
		for (size_t i = 0; i < 8; ++i) {
			data[i] = static_cast<uint8_t>((value >> (i * 8)) & 0xFF);//显示转换即可
		}
	}
	UndignedBigInteger(const UndignedBigInteger& other) {
		data = new uint8_t[128];
		for (size_t i = 0; i < 128; ++i) {
			data[i] = other.data[i];
		}
	}
	//其他类型转为UndignedBigInteger
	UndignedBigInteger&operator=(uint64_t value) {
		size_t i = 0;
		for (; i < 8; ++i) {
			data[i] = static_cast<uint8_t>((value >> (i * 8)) & 0xFF);
		}
		length = i;
		return *this;
	}
	//转换为int类型（仅限低4字节）
	int operator int() const {
		int result = 0;
		for (size_t i = 0; i < 4; ++i) {
			result |= (static_cast<int>(data[i]) << (i * 8));
		}
		if(length>4){
			//溢出处理
			//这里简单返回最大值
			return INT32_MAX;
		}
		return result;
	}
	UndignedBigInteger& operator=(UndignedBigInteger& other) {
		if(this=&other){
			return *this;
		}
		for (size_t i = 0; i < 128; ++i) {
			data[i] = other.data[i];
		}
		return *this;
	}
	~UndignedBigInteger() {
		delete[] data;
	}
private:
	uint8_t* data;
	int lenth;
};
//测试UndignedBigInteger类的使用
void testUndignedBigInteger() {
	UndignedBigInteger bigInt1(1234567890123456789ULL);
	UndignedBigInteger bigInt2 = bigInt1;
	int intValue = static_cast<int>(bigInt2);
	printf("Converted int value: %d\n", intValue);
}
