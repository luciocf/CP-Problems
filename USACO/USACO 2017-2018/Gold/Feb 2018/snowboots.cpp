// USACO Gold Feb 2018 - Snow Boots
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

struct Boot
{
	int s, d, ind;
} b[maxn];

int n, m;
int a[maxn];

int freq[maxn];

bool ans[maxn];

map<int, int> mp;

vector<int> pos[maxn];

bool comp(Boot a, Boot b)
{
	return a.s < b.s;
}

void compress(void)
{
	int aux = 0;
	for (auto &x: mp)
		x.second = ++aux;

	for (int i = 1; i <= n; i++)
	{
		a[i] = mp[a[i]];
		pos[a[i]].push_back(i);
	}

	for (int i = 1; i <= m; i++)
		b[i].s = mp[b[i].s];
}

int main(void)
{
	freopen("snowboots.in", "r", stdin);
	freopen("snowboots.out", "w", stdout);

	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		mp[a[i]] = 0;
	}

	for (int i = 1; i <= m; i++)
	{
		scanf("%d %d", &b[i].s, &b[i].d);
		b[i].ind = i;

		mp[b[i].s] = 0;
	}

	compress();

	sort(b+1, b+m+1, comp);

	int last = 0, ptr = n+1;
	int ant = -1;

	set<int> St;

	for (int i = 1; i <= m; i++)
	{
		while (last <= b[i].s)
		{
			for (auto p: pos[last])
			{
				St.insert(p);

				set<int>::iterator it1 = St.lower_bound(p);
				--it1;

				set<int>::iterator it2 = St.upper_bound(p);

				if (it1 == St.end() || it2 == St.end()) continue;

				if (a[*it1] <= ant && a[*it2] <= ant)
					--freq[*it2 - *it1];
			}

			++last;
		}

		for (int j = ant+1; j < last; j++)
		{
			for (auto p: pos[j])
			{
				set<int>::iterator it1 = St.lower_bound(p);
				--it1;

				set<int>::iterator it2 = St.upper_bound(p);

				if (it1 != St.end())
					++freq[p - *it1];

				if (it2 != St.end() && a[*it2] <= ant)
					++freq[*it2 - p];
			}
		}

		while (!freq[ptr])
			--ptr;

		if (ptr <= b[i].d)
			ans[b[i].ind] = true;

		ant = b[i].s;
	}

	for (int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
}
