// Balkan OI 2017 - City Attractions
// Lúcio Cardoso

// The idea used is called "Spin Trick". Basically, root the tree on vertex 1 and calculate the greatest and second greatest cost
// for each vertex assuming it can only jump to a vertex in its subtree. This way, we can find the vertex that 1 will jump.
// Then, we can "root" the tree on any neighbour of 1. We don't have to do that directly - we can just update the costs
// for this neighbour. Then, we found the vertex this "root" will jump to. Doing that recursively, we will have the answer for every vertex.

// Note: The second greatest cost is needed only to help in calculations when rerooting the tree.

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e5+10;
const int inf = 2e9+10;

typedef pair<int, int> pii;

int n, a[maxn];

int nxt[maxn];

int ant[maxn];

pii d[2][maxn];

vector<int> grafo[maxn];

bool check(pii a, pii b)
{
	if (a.first == b.first) return a.second < b.second;
	return a.first > b.first;
}

void dfs(int u, int p)
{
	d[0][u] = d[1][u] = {-inf, n+1};

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		dfs(v, u);

		pii x = {d[0][v].first-1, d[0][v].second};

		if (check({a[v]-1, v}, x)) x = {a[v]-1, v};

		if (check(x, d[0][u])) d[1][u] = d[0][u], d[0][u] = x;
		else if (check(x, d[1][u])) d[1][u] = x;
	}
}

void rotate(int u, int p)
{
	nxt[u] = d[0][u].second;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		pii ant = d[0][u]; 

		if (d[0][u].second == d[0][v].second || d[0][u].second == v) d[0][u] = d[1][u];

		pii x = {d[0][u].first-1, d[0][u].second};
		if (check({a[u]-1, u}, x)) x = {a[u]-1, u};

		if (check(x, d[0][v])) d[1][v] = d[0][v], d[0][v] = x;
		else if (check(x, d[1][v])) d[1][v] = x;

		rotate(v, u);

		d[0][u] = ant;
	}
}

int main(void)
{
	long long k;

	scanf("%d %lld", &n, &k);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	dfs(1, 0); rotate(1, 0);

	int u = 1;
	bool cycle = 0;

	for (int i = 1; i <= k; i++)
	{
		ant[u] = i;
		u = nxt[u];

		if (ant[u] != 0)
		{
			k -= i; k %= (i-ant[u]+1);
			cycle = 1;

			break;
		}
	}

	if (cycle)
		for (int i = 1; i <= k; i++)
			u = nxt[u];

	printf("%d\n", u);
}
