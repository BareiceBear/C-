#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

void get_next(const string &pat, vector<int> &vec)
{
    vec = vector<int>(pat.size(), 0);
    vec[0] = -1;
    int k = -1, i = 0;
    while(i < pat.size())
    {
        if(-1 == k || pat[k] == pat[i])
        {
            ++k;
            ++i;
            vec[i] = k;
        }
        else
            k = vec[k];
    }
}

int main()
{
    string pat("ABCDABD");
    vector<int> next;
    get_next(pat, next);

    for(int i = 0; i < next.size(); ++i)
        std::cout << next[i] << std::endl;
}