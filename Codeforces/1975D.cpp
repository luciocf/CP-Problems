// Codeforces 1975D - Paint the Tree
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

const int maxn = 2e5+10;

int mx[maxn], dist[maxn];
vector<int> grafo[maxn];

void dfs(int u, int p)
{
	mx[u] = 0;
	for (auto v: grafo[u])
	{
		if (v == p) continue;

		dist[v] = dist[u]+1;
		dfs(v, u);
		mx[u] = max(mx[u], 1+mx[v]);
	}
}

int main(void)
{
	int tc;
	cin >> tc;

	while (tc--)
	{
		int n, a, b;
		cin >> n >> a >> b;

		for (int i = 1; i <= n; i++)
			grafo[i].clear();
		
		for (int i = 1; i < n; i++)
		{
			int u, v;
			cin >> u >> v;

			grafo[u].pb(v); grafo[v].pb(u);
		}

		int da = 2*(n-1), db = 2*(n-1);
		dfs(a, 0);
		da -= mx[a];

		for (int i = 1; i <= n; i++)
			dist[i] = 0;

		dfs(b, 0);
		db -= mx[b];

		cout << min(da+dist[a], db+dist[a]+(dist[a]%2 ? 1 : 0)) << "\n";
	}
}
