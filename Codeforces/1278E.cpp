// Codeforces 1278E - Tests for problem D
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e6+10;

int n;

int bit[maxn];

set<int> st;

pii interv[maxn];

vector<int> grafo[maxn];

void upd(int x, int v)
{
	for (; x < maxn; x += (x&-x))
		bit[x] += v;
}

int soma(int x)
{
	int ans = 0;
	for (; x > 0; x -= (x&-x))
		ans += bit[x];
	return ans;
}

int busca(int x)
{
	int s = 0, at = 0;

	for (int i = 20; i >= 0; i--)
		if (at+(1<<i) < maxn && s+bit[at+(1<<i)] < x)
			s += bit[at+(1<<i)], at += (1<<i);

	return at+1;
}

void dfs(int u, int p, int l)
{
	int deg = (u == 1 ? grafo[u].size() : grafo[u].size()-1);

	int ind = deg+soma(l)+1;
	int r = busca(ind);

	interv[u] = {l, r};

	upd(l, -1); upd(r, -1);
	st.erase(l); st.erase(r);

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		set<int>::iterator it = st.upper_bound(r);
		--it;

		dfs(v, u, *it);
	}
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	for (int i = 1; i <= 2*n; i++)
	{
		upd(i, 1);
		st.insert(i);
	}

	dfs(1, 0, 1);

	for (int i = 1; i <= n; i++)
		printf("%d %d\n", interv[i].ff, interv[i].ss);
}
