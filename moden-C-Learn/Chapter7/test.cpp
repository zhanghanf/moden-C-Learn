#include<cstdio>
#include<cstdint>
void hello(const char* read) {
	auto str= (char*)read;
}
//4字节和8字节整数类型显示转换
int32_t to_int32(const void* ptr) {
	return *(int32_t*)ptr;
}
int64_t to_int64(const void* ptr) {
	return *(int64_t*)ptr;
}
//有关色彩的示例：色相-饱和度-值
struct Color {
	float H, S, V;
};
constexpr uint8_t max(uint8_t a, uint8_t b) {
	return a > b ? a : b;
}
constexpr uint8_t max(uint8_t a, uint8_t b,uint8_t c) {
	return max(max(a, b), c);
}
//找到较小值
constexpr uint8_t min(uint8_t a, uint8_t b) {
	return a < b ? a : b;
}
constexpr uint8_t min(uint8_t a, uint8_t b,uint8_t c) {
	return min(min(a, b), c);
}
//计算模数：两个浮点数相除后的余数
constexpr float modulo(float a, float b) {
	const auto div = a/b;
	return b* (div - static_cast<uint8_t>(div));
}
//从RGB转换到HSV
constexpr Color rgb_to_hsv(uint8_t r, uint8_t g, uint8_t b) {
	Color hc{};
	const auto max_rgb = max(r, g, b);
	const auto min_rgb = min(r, g, b);
	hc.V = static_cast<float>(max_rgb) / 255.0f;
	const auto delta = max_rgb - min_rgb;
	if (max_rgb != 0) {
		hc.S = static_cast<float>(delta) / static_cast<float>(max_rgb);
	} else {
		hc.S = 0;
		hc.H = -1;
		return hc;
	}
	float a = 10;
	long double c = 10;
	auto d = c+a;
}