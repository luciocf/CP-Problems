// Codeforces 1976E - Splittable Permutations
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

const int maxn = 3e5+10;
const int mod = 998244353;

int f[maxn], deg[maxn];
int l[maxn], r[maxn];

struct DSU
{
	int pai[maxn], peso[maxn], mn[maxn], mx[maxn];

	void init(int n)
	{
		for (int i = 1; i <= n; i++)
		{
			pai[i] = mn[i] = mx[i] = i;
			peso[i] = 1;
		}
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

 		pai[y] = x, peso[x] += peso[y];
 		mx[x] = mx[y];
 	}
} dsu;

vector<int> p;
bool mark[maxn];

void dfs(int u)
{
	p.pb(u);
	if (f[u] == 0) return;
	dfs(f[u]);
}

int main(void)
{
	int n, q;
	cin >> n >> q;

	for (int i = 1; i <= q; i++)
		cin >> l[i];
	for (int i = 1; i <= q; i++)
		cin >> r[i];

	dsu.init(n);

	for (int i = q; i >= 1; i--)
	{
		int ant = dsu.mx[dsu.Find(l[i])], post = dsu.mn[dsu.Find(r[i])];
		f[ant] = post;
		deg[post]++;

		dsu.Join(l[i], r[i]);
		mark[l[i]] = mark[r[i]] = 1;
	}

	for (int i = 1; i <= q; i++)
	{
		if (deg[l[i]] == 0)
		{
			dfs(l[i]);
			break;
		}
		if (deg[r[i]] == 0)
		{
			dfs(r[i]);
			break;
		}
	}

	int ans = 1;
	vector<int> v;

	v.pb(p[0]);
	for (int i = 1; i < p.size(); i++)
		v.pb(max(p[i-1], p[i]));
	v.pb(p.back());

	sort(v.begin(), v.end(), greater<int>());

	int ptr = 0;
	int qtd = 0;
	for (int i = n; i >= 1; i--)
	{
		if (mark[i]) continue;

		while (ptr < v.size() and i < v[ptr])
			ptr++;

		ans = (1ll*ans*(ptr+qtd))%mod;
		++qtd;
	}

	cout << ans << "\n";
}
