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

int main(int argc, char *argv[])
{
    vector<string> strs({"4PGC938", "2IYE230", "3CI0720", "1ICK750", "10HV845",\
                         "4JZY524", "1ICK750", "3CI0720", "10HV845", "10HV845",\
                         "2RLA629", "2RLA629", "3ATW723"});
    LSD_constant_len(strs);
    for(auto str : strs)
        std::cout << str << std::endl;
}
