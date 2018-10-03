#include <iostream>
#include <string>
#include <set>

using namespace std;

class Sort
{
  public:
    bool operator()(const string &str1, const string &str2) const
    {
        return str1 > str2;
    }
};

void oops2()
{
    set<string, Sort> myset;
    myset.insert("A");
    myset.insert("B");
}
