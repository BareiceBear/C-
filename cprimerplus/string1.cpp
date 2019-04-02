#include <string>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
    std::string line;
    std::string word;
    while(getline(cin, line))  //会读入换行符，但不会保存
    {
        cout << line << endl;
        if("word" == line)
	    break;
    }
    cout << "END" << endl;

    while(cin >> word)
    {
	cout << word << endl;
	if("end" == word)
	    break;
    }
    cout << "END" << endl;

    std::string str1;
    std::string str2;
    cin >> str1 >> str2;
    if(str1 != str2)
        cout << (str1 > str2 ? str1 : str2) << endl;
    cout << (str1.size() > str2.size() ? str1 : str2) << endl;

    std::string strlong1;
    std::string strlong2;
    while(cin >> word)
    {
        if("END" == word)
	    break;

        strlong1 += word;
	strlong2 += word + " ";
    }
    strlong2.erase(strlong2.size() - 1, 1);
    cout << strlong1 << endl;
    cout << strlong2 << endl;

    return 0;
}
