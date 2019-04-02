#include <string>
#include <cctype>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
    char chTest[5] = "abcd";
    for(auto c : chTest)
        cout << c << endl;

    std::string str;
    std::string str2;
    cin >> str;
    for(const auto& s : str)
	if(!ispunct(s))
	    str2 += s;
    cout << str2 << endl;

    //isalnum()   字母或数字
    //isalpah()   字母
    //iscntrl()   控制字符
    //isdigit()   数字
    //isgraph()   不是空格，但可以打印
    //islower()   小写字母
    //isprint()   可打印字符
    //ispunct()   标点符号
    //isspace()   空格
    //isupper()   大写字母
    //isxdigit()  十六进制
    //tolower()
    //toupper()

    const std::string s = "Keep out!";
    for(auto &c : s)
        cout << c << endl;

    return 0;
}
