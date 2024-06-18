// Codeforces 1981E - Turtle and Intersected Segments
// Lucio Figueiredo

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <cstring>
#include <set>
#include <map>
#include <cmath>

#define ff first
#define ss second
#define mkp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 5e5+10;

struct Range
{
	int l, r, v, ind;
} a[maxn];

// t = 0 open
// t = 1 close
struct Event
{
	int p, v, ind;
	bool t;

	bool operator<(const Event &o) const
	{
		if (p == o.p) return t < o.t;
		return p < o.p; 
	}
} event[2*maxn];

int m;
struct Edge
{
	int u, v, w;

	bool operator<(const Edge &o) const
	{
		return w < o.w;
	}
} edge[2*maxn];

struct DSU
{
	int pai[maxn], peso[maxn];

	void init(int n)
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

		pai[y] = x;
		peso[x] += peso[y];
	}
} dsu;

void makeGraph(int e)
{
	set<pii> st;

	for (int i = 1; i <= e; i++)
	{
		int p = event[i].p, v = event[i].v, ind = event[i].ind;
		if (event[i].t == 0)
		{
			auto it = st.lower_bound({v, -1});

			if (it != st.end()) edge[++m] = {ind, it->ss, it->ff-v};
			if (st.size() >= 1 and it != st.begin())
			{
				it = prev(it);
				edge[++m] = {ind, it->ss, v-it->ff};
			}

			st.insert({v, ind});
		}
		else st.erase({v, ind});
	}
}

void cleanup(int n)
{
	m = 0;
	dsu.init(n);
}

int main(void)
{
	int tc;
	cin >> tc;

	while (tc--)
	{
		int n;
		cin >> n;

		cleanup(n);

		int e = 0;
		for (int i = 1; i <= n; i++)
		{
			cin >> a[i].l >> a[i].r >> a[i].v;
			a[i].ind = i;

			event[++e] = {a[i].l, a[i].v, i, 0};
			event[++e] = {a[i].r, a[i].v, i, 1};
		}

		sort(event+1, event+e+1);

		makeGraph(e);

		sort(edge+1, edge+m+1);

		ll ans = 0;

		int qtd = 0;

		for (int i = 1; i <= m; i++)
		{
			auto [u, v, w] = edge[i];

			if (dsu.Find(u) != dsu.Find(v))
			{
				dsu.Join(u, v);
				ans += 1ll*w;
				qtd++;
			}
		}

		if (qtd < n-1) cout << "-1\n";
		else cout << ans << "\n";
	}
}
