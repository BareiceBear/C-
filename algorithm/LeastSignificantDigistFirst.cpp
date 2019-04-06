#include <string>
#include <vector>
#include <string.h>
#include <iostream>

using std::vector;
using std::string;

void LSD_constant_len(vector<string>& strs)
{
    int R = 128;                     //ascii字符集
    int frequency[128] = {0};
    int count[128] = {0};
    int len = strs[0].length();
    vector<string> aux(strs);

    for(int i = len - 1; i >= 0; --i)
    {
        memset(frequency, 0, sizeof(frequency));
        memset(count, 0, sizeof(count));
        for(auto c : strs)            //计算第i位字符频率
            frequency[c.at(i)]++;

        for(int j =  1; j < R; ++j)   //将频率转换为索引
            count[j] = frequency[j -  1] + count[j - 1];

        for(auto str : strs)          //排序
        {
            aux[count[str.at(i)]] = str;
            count[str.at(i)]++;
        }

        strs = aux;
    }

    return;
}

int charAt(const string& str, int idx)
{
    if(idx > str.length() - 1)
        return 0;
    else
        return str.at(idx);
}

void LSD_variable_len(vector<string>& strs)
{
    int R = 128;
    int frequency[128] = {0};
    int count[128] = {0};
    int len = strs[0].length();
    vector<string> aux(strs);

    for(int i = len - 1; i >= 0; --i)
    {
        memset(frequency, 0, sizeof(frequency));
        memset(count, 0, sizeof(count));
        for(auto c : strs)
            frequency[charAt(c, i)]++;

        for(int j =  1; j < R; ++j)
            count[j] = frequency[j -  1] + count[j - 1];

        for(auto str : strs)
        {
            aux[count[charAt(str, i)]] = str;
            count[charAt(str, i)]++;
        }

        strs = aux;
    }

    return;
}

int main(int argc, char *argv[])
{
    vector<string> strs({"4PGC938", "2IYE230", "3CI0720", "1ICK750", "10HV845",\
                         "4JZY524", "1ICK750", "3CI0720", "10HV845", "10HV845",\
                         "2RLA629", "2RLA629", "3ATW723"});
    vector<string> strs2({"4PG938", "2I230", "3CI720", "1ICK750", "V845",\
                         "4JZY524", "1ICK750", "3CI0720", "1V845", "10H45",\
                         "2R629", "2RLA629", "3ATW723"});
    LSD_variable_len(strs2);
    for(auto str : strs2)
        std::cout << str << std::endl;
}
