#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum class Op
{
    Plus,
    Minus,
    Mul,
    Merge,
    None
};

using Iterator = vector<pair<int, Op>>::iterator;

int Count(vector<pair<int, Op>> data)
{
    prev(data.end())->second = Op::None;
    for (auto it = data.begin(); it < data.end(); ++it)
    {
        if ((*it).second == Op::Merge)
        {
            int left = (*it).first;
            int right = (*next(it)).first;
            Op p = (*next(it)).second;
            it->first = left * 10 + right;
            it->second = p;
            data.erase(next(it));
            --it;
        }
    }
    for (auto it = data.begin(); it < data.end(); ++it)
    {
        if ((*it).second == Op::Mul)
        {
            int left = (*it).first;
            int right = (*next(it)).first;
            Op p = (*next(it)).second;
            it->first = left * right;
            it->second = p;
            data.erase(next(it));
        }
    }
    for (auto it = data.begin(); it < data.end(); ++it)
    {
        if ((*it).second == Op::Plus || (*it).second == Op::Minus)
        {
            int left = (*it).first;
            int right = (*next(it)).first;
            Op p1 = (*it).second;
            Op p2 = (*next(it)).second;
            if (p1 == Op::Plus)
                it->first = left + right;
            if (p1 == Op::Minus)
                it->first = left - right;
            it->second = p2;
            data.erase(next(it));
            --it;
        }
    }
    return data.begin()->first;
}

void Print_answer(int result, vector<pair<int, Op>> data)
{
    cout << result << " = ";
    for (auto it = data.begin(); it < data.end(); ++it)
    {
        cout << (*it).first;
        if (it != data.end())
        {
            if ((*it).second == Op::Plus)
                cout << " " << "+" << " ";
            if ((*it).second == Op::Minus)
                cout << " " << "-" << " ";
            if ((*it).second == Op::Mul)
                cout << " " << "*" << " ";
            if ((*it).second == Op::Merge)
            {}
        }
    }
    cout << endl;
}

void Solve (int result, Iterator begin, Iterator end, vector<pair<int, Op>> new_data)
{
    vector<Op> ops = {Op::Merge, Op::Minus, Op::Plus, Op::Mul};
    ++begin;
    if (begin != prev(end))
    {
        for (auto op : ops)
        {
            pair<int, Op> p = (*begin);
            p.second = op;
            new_data.push_back(p);
            if (begin == (prev(prev(end))))
                new_data.push_back(pair<int, Op>(prev(end)->first, Op::None));
            Solve(result, begin, end, new_data);
            new_data.pop_back();
            new_data.pop_back();
        }
    }
    else
    {
        int answer = Count(new_data);
        if (answer == result)
        {
            Print_answer(result, new_data);
        }
    }
}



int main(int args, char* argv[])
{
    vector<pair<int, Op>> data;
    int result = std::stoi(argv[1]);
    for (int i = 2; i < args; ++i)
        data.push_back(pair<int, Op>(stoi(argv[i]), Op::None));

    vector<pair<int, Op>> new_data;
    vector<Op> ops = {Op::Merge, Op::Minus, Op::Plus, Op::Mul};
    for (auto op : ops)
    {
        pair<int, Op> p;
        p.first = data[0].first;
        p.second = op;
        new_data.push_back(p);
        Solve(result, data.begin(), data.end(), new_data);
        new_data.erase(new_data.begin());
    }
    return 0;
}
