#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
int main()
{
    vector<int> a;
    cout << a.size() << endl;
    for (int i = 0; i < 10; i++)
    {
        a.push_back(i); // 使用push_back的时候会使得vector变长
    }
    cout << a.size() << endl;
    vector<int> b(15);
    cout << b.size() << endl;

    for (int i = 0; i < b.size(); i++)
    {
        b[i] = 15;
    }
    for (int i = 0; i < b.size(); i++)
    {
        cout << b[i] << ' ';
    }

    system("pause");
    return 0;
}