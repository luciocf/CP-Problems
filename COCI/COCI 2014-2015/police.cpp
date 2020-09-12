// COCI 2014/2015 - Police
// Lúcio Cardoso

// Solution is the same as in: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2015/contest7_solutions/solutions.pdf

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3+10;

int n, m;
int a[maxn][maxn], b[maxn][maxn];

struct DSU
{
	int pai[maxn], peso[maxn];
	bool zero[maxn];

	void init(int n)
	{
		for (int i = 1; i <= n; i++)
			pai[i] = i, peso[i] = 1, zero[i] = (*min_element(a[i]+1, a[i]+m+1) == 0);
	}

	int Find(int x)
	{
		if (pai[x] == x) return x;
		return pai[x] = Find(pai[x]);
	}

	void Join(int x, int y)
	{
		x = Find(x), y = Find(y);
		if (x == y) return;

		if (peso[x] < peso[y]) swap(x, y);

		pai[y] = x, peso[x] += peso[y], zero[x] |= zero[y];
	}
} dsu;

int pos[2][maxn*maxn];
bool mark[maxn];

int lis(vector<int> &v)
{
	vector<int> p;

	for (auto x: v)
	{
		auto it = lower_bound(p.begin(), p.end(), x);

		if (it == p.end()) p.push_back(x);
		else *it = x;
	}

	return (int)p.size();
}

int main(void)
{
	scanf("%d %d", &n, &m);

	int ans = 0;
	bool tem_zero = 0;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &a[i][j]);

			if (a[i][j]) ans++;
			else tem_zero = 1;

			if (a[i][j]) pos[0][a[i][j]] = i;
		}
	}

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &b[i][j]);

			if (b[i][j]) pos[1][b[i][j]] = i;
		}
	}

	if (!tem_zero)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				if (a[i][j] != b[i][j])
				{
					printf("-1\n");
					return 0;
				}
			}
		}

		printf("0\n");
		return 0;
	}

	for (int i = 1; i <= n*m; i++)
	{
		if ((pos[0][i] && !pos[1][i]) || (!pos[0][i] && pos[1][i]))
		{
			printf("-1\n");
			return 0;
		}
	}

	for (int i = 1; i <= n; i++)
	{
		mark[i] = 1;

		for (int j = 1; j <= m; j++)
		{
			if (a[i][j] && pos[1][a[i][j]] != i)
				mark[i] = 0;

			if (b[i][j] && pos[0][b[i][j]] != i)
				mark[i] = 0;
		}

		map<int, int> mp;
		int aux = 0;

		for (int j = 1; j <= m; j++)
			if (b[i][j])
				mp[b[i][j]] = ++aux;

		vector<int> v;

		for (int j = 1; j <= m; j++)
			if (mp[a[i][j]])
				v.push_back(mp[a[i][j]]);

		ans -= lis(v);

		if (mark[i] && *min_element(a[i]+1, a[i]+m+1) != 0 && lis(v) != v.size())
			ans++;
	}

	dsu.init(n);

	for (int i = 1; i <= n*m && pos[0][i]; i++)
		if (pos[0][i] != pos[1][i])
			dsu.Join(pos[0][i], pos[1][i]);

	for (int i = 1; i <= n; i++)
		if (!mark[i] && dsu.Find(i) == i && !dsu.zero[i])
			ans++;

	printf("%d\n", ans);
}
