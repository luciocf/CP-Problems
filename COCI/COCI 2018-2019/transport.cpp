// COCI 2018/2019 - Transport
// Lúcio Cardoso

// Solution:

// 1. Use centroid decomposition. Notice that for a pair (u, v), the minimum prefix sum
// of (sum_of_vertices - sum_of_edges) in the path from the centroid to v plus the remaining
// value from the sum of going from u up to the centroid should be >= 0.

// 2. We can insert the values that remain from going from a vertex u by rising up to the
// centroid in a vector, by using a DFS (check dfs_up()). After that, sort this vector, and
// use a BIT in its positions. Initially, our BIT has 1 in every position from 1 to vector_size.

// 3. Before going from the centroid down to a vertex v, update all positions in the BIT that
// are present in v's subtree to 0. After that, we can maintain the minimum prefix going down to
// v using the same method as in dfs_up(), and use a lower_bound in our vector to check the smallest
// index such that its value + the minimum prefix is >= 0. When we find that index, just add to the total
// answer the suffix in the BIT from the last position to such index.

// Complexity: O(n log^2 n)

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 1e5+10;

int n;
ll ans;

int a[maxn];

int bit[maxn], id[maxn];

int sz[maxn];

bool mark[maxn];

vector<pii> grafo[maxn]; 
vector<pair<ll, int>> tot;

void upd(int x, int v)
{
	for (; x <= n; x += (x&-x))
		bit[x] += v;
}

int soma(int x)
{
	int ans = 0;
	for (; x > 0; x -= (x&-x))
		ans += bit[x];
	return ans;
}

void dfs(int u, int p)
{
	sz[u] = 1;

	for (auto pp: grafo[u])
	{
		int v = pp.first, w = pp.second;
		if (v == p || mark[v]) continue;

		dfs(v, u);

		sz[u] += sz[v];
	}
}

int centroid(int u, int p, int S)
{
	for (auto pp: grafo[u])
	{
		int v = pp.first;
		if (v == p || mark[v]) continue;

		if (sz[v] > S/2) return centroid(v, u, S);
	}

	return u;
}

void dfs_up(int u, int p, ll cost, ll sum)
{
	if (cost >= 0)
	{
		ans++;
		tot.push_back({sum, u});
	}

	for (auto pp: grafo[u])
	{
		int v = pp.first, w = pp.second;
		if (v == p || mark[v]) continue;

		dfs_up(v, u, min(cost+1ll*a[v]-1ll*w, 1ll*a[v]-1ll*w), sum+1ll*a[v]-1ll*w);
	}
}

void dfs_add(int u, int p, ll cost, int add)
{
	if (cost >= 0)
		upd(id[u], add);

	for (auto pp: grafo[u])
	{
		int v = pp.first, w = pp.second;
		if (v == p || mark[v]) continue;

		dfs_add(v, u, min(cost+1ll*a[v]-1ll*w, 1ll*a[v]-1ll*w), add);
	}
}

void dfs_down(int u, int p, ll cost, ll sum)
{
	if (cost >= 0)
		ans++;

	if (lower_bound(tot.begin(), tot.end(), make_pair(-cost, 0)) != tot.end())
	{
		int pos = (int) (lower_bound(tot.begin(), tot.end(), make_pair(-cost, 0))-tot.begin())+1;
		ans += 1ll*(soma(n)-soma(pos-1));
	}

	for (auto pp: grafo[u])
	{
		int v = pp.first, w = pp.second;
		if (v == p || mark[v]) continue;

		dfs_down(v, u, min(cost, sum+1ll*a[u]-1ll*w), sum+1ll*a[u]-1ll*w);
	}
}

void decompose(int u)
{
	dfs(u, 0);

	int c = centroid(u, 0, sz[u]);
	mark[c] = 1;

	for (auto v: grafo[c])
		if (!mark[v.first])
			dfs_up(v.first, c, 1ll*(a[v.first]-v.second), 1ll*(a[v.first]-v.second));

	sort(tot.begin(), tot.end());

	for (int i = 0; i < tot.size(); i++)
		id[tot[i].second] = i+1;

	for (auto v: grafo[c])
		if (!mark[v.first])
			dfs_add(v.first, c, 1ll*(a[v.first]-v.second), 1);

	for (auto pp: grafo[c])
	{
		int v = pp.first, w = pp.second;
		if (mark[v]) continue;

		dfs_add(v, c, 1ll*(a[v]-w), -1);

		dfs_down(v, c, 1ll*(a[c]-w), 1ll*(a[c]-w));

		dfs_add(v, c, 1ll*(a[v]-w), 1);
	}

	for (auto v: grafo[c])
		if (!mark[v.first])
			dfs_add(v.first, c, 1ll*(a[v.first]-v.second), -1);

	tot.clear();

	for (auto v: grafo[c])
		if (!mark[v.first])
			decompose(v.first);
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i < n; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		grafo[u].push_back({v, w});
		grafo[v].push_back({u, w});
	}

	decompose(1);

	printf("%lld\n", ans);
}
