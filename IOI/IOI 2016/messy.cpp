// IOI 2016 - Unscrambling a Messy Bug
// Lúcio Figueiredo

#include <bits/stdc++.h>
#include "messy.h"

using namespace std;

const int maxn = 210;

int p[maxn];

void write(string s)
{
    vector<int> pos;

    for (int i = 0; i < s.size(); i++)
        if (s[i] == '1')
            pos.push_back(i);

    if (pos.size() == 1) return;

    if (pos.size() == 2)
    {
        s[pos[0]] = '0';
        add_element(s);
        return;
    }

    int mid = pos.size()/2;

    for (int i = 0; i < mid; i++)
    {
        s[pos[i]] = '0';
        add_element(s);
        s[pos[i]] = '1';
    }

    for (int i = mid; i < pos.size(); i++)
        s[pos[i]] = '0';

    write(s);

    for (int i = 0; i < mid; i++)
        s[pos[i]] = '0';
    for (int i = mid; i < pos.size(); i++)
        s[pos[i]] = '1';

    write(s);
}

void read(string s, string match)
{
    vector<int> pos[2];

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '1')
            pos[0].push_back(i);

        if (match[i] == '1')
            pos[1].push_back(i);
    }

    if (pos[0].size() == 1)
    {
        p[pos[1][0]] = pos[0][0];
        return;
    }

    string match2, match3;

    for (int i = 0; i < match.size(); i++)
        match2 += '0', match3 += '0';

    for (int i = 0; i < pos[1].size(); i++)
    {
        match[pos[1][i]] = '0';

        if (check_element(match)) match2[pos[1][i]] = '1';
        else match3[pos[1][i]] = '1';

        match[pos[1][i]] = '1';
    }

    int mid = pos[0].size()/2;

    for (int i = mid; i < pos[0].size(); i++)
        s[pos[0][i]] = '0';

    if (pos[0].size() == 2)
        s[pos[0][1]] = '0';

    read(s, match2);

    for (int i = mid; i < pos[0].size(); i++)
        s[pos[0][i]] = '1';
    for (int i = 0; i < mid; i++)
        s[pos[0][i]] = '0';

    if (pos[0].size() == 2)
        s[pos[0][1]] = '1', s[pos[0][0]] = '0';

    read(s, match3);
}

vector<int> restore_permutation(int n, int w, int r)
{
    string s, match;
    for (int i = 0; i < n; i++)
    {
        s += '1';
        match += '1';
    }

    write(s);

    compile_set();

    read(s, match);

    vector<int> ans;
    for (int i = 0; i < n; i++)
        ans.push_back(p[i]);

    return ans;
}
