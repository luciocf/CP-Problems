// POI 2018 - Plan Metra
// Lúcio Cardoso

// Solution is the same as: https://github.com/thecodingwizard/competitive-programming/blob/master/POI/POI%2018-Plan_Metra.cpp

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5+10;
const int inf = 1e9+10;

int d_1[maxn], d_n[maxn];

bool mark[maxn];

vector<int> path;
map<int, vector<int>> mp;

bool comp(int a, int b) {return d_1[a] < d_1[b];}

bool is_equal(int n)
{
    for (int i = 3; i < n; i++)
        if (abs(d_1[i]-d_n[i]) != abs(d_1[2]-d_n[2]))
            return false;

    return (true && d_1[2] != d_n[2]);
}

bool is_valid(int n)
{
    for (int i = 1; i < path.size(); i++)
        if (d_1[path[i]] == d_1[path[i-1]])
            return false;

    for (auto u: path)
    {
        for (auto v: mp[d_1[u]-d_n[u]])
        {
            if (!mark[v] && d_1[v] <= d_1[u])
                return false;

            mark[v] = 1;
        }
    }

    for (auto v: mp[-d_1[path[0]]-d_n[path[0]]])
        mark[v] = 1;
    for (auto v: mp[d_1[path[0]]+d_n[path[0]]])
        mark[v] = 1;

    for (int i = 2; i < n; i++)
        if (!mark[i])
            return false;

    return true;
}

int main(void)
{
    int n;
    scanf("%d", &n);

    for (int i = 2; i <= n-1; i++)
        scanf("%d", &d_1[i]);

    for (int i = 2; i <= n-1; i++)
        scanf("%d", &d_n[i]);

    if (n == 2)
    {
        printf("TAK\n1 2 1\n");
        return 0;
    }

    if (is_equal(n))
    {
        printf("TAK\n");

        printf("1 %d %d\n", n, abs(d_1[2]-d_n[2]));

        for (int i = 2; i < n; i++)
        {
            if (d_1[i] > d_n[i]) printf("%d %d %d\n", n, i, d_n[i]);
            else printf("1 %d %d\n", i, d_1[i]);
        }

        return 0;
    }

    int mn = inf;

    for (int i = 2; i < n; i++)
    {
        mn = min(mn, d_1[i]+d_n[i]);

        mp[d_1[i]-d_n[i]].push_back(i);
    }

    for (int i = 2; i < n; i++)
    {
        if (d_1[i]+d_n[i] == mn)
        {
            path.push_back(i);
            mark[i] = true;
        }
    }

    sort(path.begin(), path.end(), comp);

    if (!is_valid(n))
    {
        printf("NIE\n");
        return 0;
    }

    memset(mark, 0, sizeof mark);
    for (auto u: path)
        mark[u] = 1;

    printf("TAK\n");

    printf("1 %d %d\n", path[0], d_1[path[0]]);

    for (int i = 1; i < path.size(); i++)
        printf("%d %d %d\n", path[i-1], path[i], d_1[path[i]]-d_1[path[i-1]]);

    printf("%d %d %d\n", path.back(), n, d_n[path.back()]);

    for (auto u: path)
    {
        for (auto v: mp[d_1[u]-d_n[u]])
        {
            if (!mark[v])
            {
                printf("%d %d %d\n", u, v, d_1[v]-d_1[u]);
                mark[v] = 1;
            }
        }
    }

    for (auto v: mp[-d_1[path[0]]-d_n[path[0]]])
    {
        if (!mark[v])
        {
            printf("1 %d %d\n", v, d_1[v]);
            mark[v] = 1;
        }
    }
    for (auto v: mp[d_1[path[0]]+d_n[path[0]]])
    {
        if (!mark[v])
        {
            printf("%d %d %d\n", n, v, d_n[v]);
            mark[v] = 1;
        }
    }
}
