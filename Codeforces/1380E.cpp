// Codeforces 1380E - Merging Towers
// Lúcio Cardoso

// Solution is the same as in editorial (using small to large)

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

set<int> st[maxn];

int get_tot(int i)
{
	int ant = -1, ans = 0;

	for (auto it: st[i])
	{
		if (it == ant+1) ans++;
		ant = it;
	}

	return ans;
}

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	int tot = 0;

	for (int i = 1; i <= n; i++)
	{
		int t;
		scanf("%d", &t);

		st[t].insert(i);
	}

	for (int i = 1; i <= m; i++)
		tot += get_tot(i);

	printf("%d\n", n-tot-1);

	for (int i = 1; i < m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		if (st[v].size() <= st[u].size())
		{
			for (auto x: st[v])
			{
				if (st[u].find(x-1) != st[u].end())
					tot++;

				if (st[u].find(x+1) != st[u].end())
					tot++;
			}

			for (auto x: st[v])
				st[u].insert(x);
		}
		else
		{
			for (auto x: st[u])
			{
				if (st[v].find(x-1) != st[v].end())
					tot++;

				if (st[v].find(x+1) != st[v].end())
					tot++;
			}

			for (auto x: st[u])
				st[v].insert(x);

			swap(st[u], st[v]);
		}

		printf("%d\n", n-tot-1);
	}
}
