// LMIO 2018 - Monthly railway pass
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5+10;

int n;

int pai[maxn], peso[maxn];

bool mark[maxn];

vector<int> grafo[maxn], comp[maxn];

void Init(void)
{
	for (int i = 1; i <= n; i++)
		pai[i] = i, peso[i] = 1; 
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

	pai[y] = x, peso[x] += peso[y];
}

int main(void)
{
	int m;
	scanf("%d %d", &n, &m);

	Init();

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		char c;

		scanf("%d %d %c", &u, &v, &c);

		if (c == 'T')
			Join(u, v);
		else
		{
			grafo[u].push_back(v);
			grafo[v].push_back(u);
		}
	}

	for (int i = 1; i <= n; i++)
		comp[Find(i)].push_back(i);

	int cc = 0;
	for (int i = 1; i <= n; i++)
		if (Find(i) == i)
			cc++;

	int ans = 0;

	for (int i = 1; i <= n; i++)
	{
		if (Find(i) != i) continue;

		set<int> st;

		for (auto u: comp[i])
			for (auto v: grafo[u])
				if (Find(v) != i)
					st.insert(Find(v));

		if (st.size() == cc-1)
			ans += comp[i].size();
	}
		
	printf("%d\n", ans);
}
