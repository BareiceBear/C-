#include <string>
#include <iostream>
#include <vector>

using namespace std;

void test1(string &s, const string &oldVal, const string &newVal)
{
    auto it = s.begin();
    string::size_type pos = 0;
    while((pos = s.find(oldVal, pos)) != string::npos)
    {
        it += pos;
        pos++;
        auto itOld = oldVal.cbegin();
        auto itNew = newVal.cbegin();
        for(; itOld != oldVal.cend() && it != s.end(); ++itOld, ++itNew)
        {
            //返回被删除字符的下一个字符
            it = s.erase(it);           //下标版本如不指定第二个参数len,则删除pos之后所有字符
            
            //在it所指之前插入字符，返回被插入字符的位置
            it = s.insert(it, *itNew);  //下标版本返回指向s的引用，迭代器版本返回指向第一个插入字符的迭代器

            ++it;

        }

        it = s.insert(it, itNew, newVal.cend());
    }
}

void test2(string &s, const string &oldVal, const string &newVal)
{

}

int main()
{
    vector<char> vecCh({'H', 'e', 'l', 'l', 'o'});
    string str(100, '\0');
    for(const auto &c : vecCh)
        str += c;
    cout << str << endl;

    string str1("go truthru"), str2("thru"), str3("through");
    test1(str1, str2, str3);
    cout << str1 << endl;
}
