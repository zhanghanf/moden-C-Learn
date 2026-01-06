// Include a header from the Boost.Lambda library
#include <iostream>
#include <boost/smart_ptr.hpp> // Boost智能指针头文件
#include<boost/version.hpp>
//#include<catch_amalgamated.hpp>
//using namespace boost;
/*
int main() {
    // 测试shared_ptr智能指针
    shared_ptr<int> ptr(new int(2026));
    cout << "Boost智能指针值：" << *ptr << endl;
    cout << "Boost版本号：" << BOOST_VERSION << endl; // 输出Boost版本（109000代表1.90.0）
    return 0;
}
*/
#include<boost/algorithm/string.hpp>//字符串处理头文件
#include<boost/filesystem.hpp>
using namespace std;
namespace fp = boost::filesystem;
int main() {
    string str = "Hello Boost 1.90.0";
    // 转大写
    boost::to_upper(str);
    cout << "转大写后：" << str << endl;
    // 分割字符串
    vector<string> parts;
    split(parts, str, boost::is_space());
    cout << "分割结果：";
    for (auto& p : parts) cout << p << " ";
    cout << endl;
    fp::path current_path = fp::current_path();
    cout << "当前路径：" << current_path << endl;


    return 0;
}