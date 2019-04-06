#include <string>
#include <vector>
#include <string.h>
#include <iostream>

using std::vector;
using std::string;

void LSD_constant_len(vector<string>& strs)
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
            frequency[c.at(i)]++;

        for(int j =  1; j < R; ++j)
            count[j] = frequency[j -  1] + count[j - 1];

        for(auto str : strs)
        {
            aux[count[str.at(i)]] = str;
            count[str.at(i)]++;
        }

        strs = aux;
    }

    return;
}

int maxLen(const vector<string> &strs)
{
    int maxLen = 0;
    for(const auto &str : strs)
        maxLen = std::max(maxLen, (int)str.length());
    return maxLen;
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
    int len = maxLen(strs);
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
    LSD_constant_len(strs);
    for(auto str : strs)
        std::cout << str << std::endl;
}