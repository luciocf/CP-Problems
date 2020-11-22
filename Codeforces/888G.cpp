// Codeforces 888G - Xor-MST
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 2e5+10;
const int inf = 1e9+10;

struct DSU
{
	int pai[maxn], peso[maxn];

	void init(int n)
	{
		for (int i = 0; i < n; i++)
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
} dsu;

struct Trie
{
	int tot = 1;

	int b[2][31*maxn], sz[31*maxn];

	void add(int v)
	{
		int at = 1;
		sz[at]++;

		for (int i = 29; i >= 0; i--)
		{
			int x = (v&(1<<i) ? 1 : 0);

			if (b[x][at] == 0)
				b[x][at] = ++tot;

			at = b[x][at];
			sz[at]++;
		}
	}

	void rem(int v)
	{
		int at = 1;
		sz[at]--;

		for (int i = 29; i >= 0; i--)
		{
			int x = (v&(1<<i) ? 1 : 0);

			at = b[x][at];
			sz[at]--;
		}
	}

	int get(int v)
	{
		int at = 1;
		int ans = 0;

		for (int i = 29; i >= 0; i--)
		{
			int x = (v&(1<<i) ? 1 : 0);

			if (!b[x][at] || sz[b[x][at]] == 0)
			{
				ans += (1<<i);
				at = b[x^1][at];
			}
			else at = b[x][at];
		}

		return ans;
	}
} trie;

pii best[maxn];

map<int, int> ind;

vector<int> comp[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	vector<int> a;

	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);

		a.push_back(x);
	}

	sort(a.begin(), a.end());
	a.erase(unique(a.begin(), a.end()), a.end());

	n = a.size();

	int cc = n;
	dsu.init(n);

	for (int i = 0; i < n; i++)
	{
		ind[a[i]] = i;
		trie.add(a[i]);
	}
	
	ll ans = 0;

	while (cc > 1)
	{
		for (int i = 0; i < n; i++)
		{
			best[i] = {inf, n+1};
			comp[i].clear();
		}

		for (int i = 0; i < n; i++)
			comp[dsu.Find(i)].push_back(i);

		for (int i = 0; i < n; i++)
		{
			if (!comp[i].size()) continue;

			for (auto u: comp[i])
				trie.rem(a[u]);

			for (auto u: comp[i])
			{
				int v = trie.get(a[u]);

				best[i] = min(best[i], {v, ind[v^a[u]]});
			}

			for (auto u: comp[i])
				trie.add(a[u]);

			if (dsu.Find(i) != dsu.Find(best[i].ss))
			{
				ans += 1ll*best[i].ff;
				dsu.Join(i, best[i].ss), --cc;
			}
		}
	}

	printf("%lld\n", ans);
}
