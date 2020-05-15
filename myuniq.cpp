#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    vector<string> strings;
    string line;
    while (getline(cin, line))
    {
        if (line.empty())
            break;
        strings.push_back(line);
    }
    sort(strings.begin(), strings.end());
    string prev = strings[0];
    cout << prev << endl;
    for (int i = 1; i < strings.size(); ++i)
    {
        if (strings[i] != prev)
            cout << strings[i] << endl;
        prev = strings[i];
    }

}
