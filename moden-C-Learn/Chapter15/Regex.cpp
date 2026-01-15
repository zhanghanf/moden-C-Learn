#include<string>
#include<iostream>
#include<regex>
using namespace std;
int main() {
	/*
	regex reg{R"((\w{5}).*)" };
	string str{"hello world"};
	
	smatch smat;
	//要求整个字符串完全匹配，smart返回分组
	auto sized = regex_match(str, smat, reg);
	cout << smat.size();
	*/
	regex reg("[aeiou]",regex::icase);//忽视大小写
	smatch smat;
	string str("hello worldOOO!");
	bool isMatch = regex_search(str, smat, reg);
	if (isMatch)cout << "元音字母数量" << smat.size() << endl;
	else cout << "匹配失败" << endl;
	//正则迭代器
	sregex_iterator it(str.begin(), str.end(), reg);
	sregex_iterator end_it;//默认构造表示结束
	int match_count = 0;
	for (; it != end_it; ++it) match_count++;
	cout << "元音字母数量" << match_count << endl;
	//匹配带捕获组的正则表达式
	regex reg1("(\\d+)-(\\d+)");//匹配数字-数字
	string str1("Lili:123-456,num:111-55555");
	sregex_iterator its(str1.begin(), str1.end(), reg1);
	sregex_iterator end_its;
	match_count = 0;
	for (; its != end_its; ++its) {
		match_count++;
		cout << "第" << match_count << "组" << endl;
		cout << (*its)[1].str() << endl;
		cout << (*its)[2].str() << endl;
	}
	return 0;
}