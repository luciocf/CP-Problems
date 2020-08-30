// 2018-2019 XIX Open Cup, Grand Prix of Korea - D - Dumae
// Lúcio Cardoso

// Solution is the same as in editorial.

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 3e5+10;

pii range[maxn];

int n;

vector<int> ord;

int grau[maxn];
vector<int> grafo[maxn], rev[maxn];

vector<pii> event[maxn];
int ans[maxn];

void get(void)
{
	queue<int> fila;

	for (int i = 1; i <= n; i++)
		if (!grau[i])
			fila.push(i);

	while (fila.size())
	{
		int u = fila.front(); fila.pop();
		ord.push_back(u);

		for (auto v: grafo[u])
		{
			grau[v]--;
			if (grau[v] == 0) fila.push(v);
		}
	}
}

int main(void)
{
	int m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &range[i].ff, &range[i].ss);

	map<pair<int, int>, bool> mp;

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		if (mp[{u, v}]) continue;

		mp[{u, v}] = 1;

		grafo[u].push_back(v);
		rev[v].push_back(u);

		grau[v]++;
	}

	get();

	if (ord.size() != n)
	{
		printf("-1\n");
		return 0;
	}

	for (auto u: ord)
		for (auto v: rev[u])
			range[u].ff = max(range[u].ff, range[v].ff+1);

	reverse(ord.begin(), ord.end());

	for (auto u: ord)
		for (auto v: grafo[u])
			range[u].ss = min(range[u].ss, range[v].ss-1);

	for (int i = 1; i <= n; i++)
	{
		if (range[i].ff > range[i].ss)
		{
			printf("-1\n");
			return 0;
		}
	}

	for (int i = 1; i <= n; i++)
	{
		event[range[i].ff].push_back({0, i});
		event[range[i].ss].push_back({1, i});
	}

	for (int i = 1; i <= n; i++)
		sort(event[i].begin(), event[i].end());

	set<pii> st;

	for (int i = 1; i <= n; i++)
	{
		for (auto e: event[i])
		{
			if (e.ff == 1) break;

			st.insert({range[e.ss].ss, e.ss});
		}

		if (st.size() == 0)
		{
			printf("-1\n");
			return 0;
		}

		ans[i] = st.begin()->ss;
		st.erase(st.begin());

		for (auto e: event[i])
			if (e.ff == 1 && st.find({range[e.ss].ss, e.ss}) != st.end())
				st.erase({range[e.ss].ss, e.ss});
	}

	for (int i = 1; i <= n; i++)
		printf("%d\n", ans[i]);
}
