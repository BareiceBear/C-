#include <iostream>
#include <string>
#include <vector>

#define MIN_SIZE 15
#define R        128

using std::vector;
using std::string;

int charAt(const string& str, int idx)
{
    if(idx > str.length() - 1)
        return -1;
    else
        return str.at(idx);
}


void insectionSort(vector<string>& strs, int lo, int hi, int d)
{
    for(int i = lo; i <= hi; ++i)
    {
        for(int j = i; j > lo && strs[j].substr(d) < strs[j - 1].substr(d); --j)
        {
            swap(strs[j], strs[j - 1]);
        }
    }

    return;
}

void MSDsort(vector<string>& strs, int lo, int hi, int d)
{
     if(hi <= lo + MIN_SIZE)
     {
         insectionSort(strs, lo, hi, d);
         return;
     }

    int count[R + 2] = {0};
    vector<string> aux(hi - lo + 1);

    //计算频率, 因为长度小于d时，返回-1，且count[0]空出，为0，所以要将得到的索引+2
    for(int i = lo; i <= hi; ++i)
        count[charAt(strs[i], d) + 2]++;

    //转换为索引
    for(int i = 1; i < R + 2; ++i)
        count[i] += count[i - 1];

    //分类，因为长度小于d时，返回-1，所以要将得到的索引+1
    for(int i = lo; i <= hi; ++i)
        aux[count[charAt(strs[i], d) + 1]++] = strs[i];

    //赋值
    for(int i = lo; i <= hi; ++i)
        strs[i] = aux[i - lo];

    //此时lo + count[i]为第d个字符的索引值为i的起始索引
    //lo + count[i + 1]为第d个字符的索引值为i + 1的起始索引
    //lo + count[i + 1] - 1为第d个字符的索引值为i的结束索引
    for(int i = 0; i < R; ++i)
        MSDsort(strs, lo + count[i], lo + count[i + 1] - 1, d + 1);

    return;
}

void MSD(vector<string> &strs)
{
    MSDsort(strs, 0, strs.size() - 1, 0);
    return;
}

int main(int argc, char *argv[])
{
    vector<string> strs({"she", "sells", "seashells", "by", "the",\
                         "sea", "shore", "the", "shells", "she", "sells",\
                         "are", "surely", "seashells"});
    MSD(strs);
    for(const auto& str : strs)
        std::cout << str << std::endl;
}
