// JOI Spring Camp 2019 - Mergers
// Lúcio Cardoso

// Solution:

// 1. Root the tree at any vertex. For every vertex U, if the amount of vertices from state X in its subtree is smaller than
// the total amount of vertices from state X, then U and his parent will have to be in the same group.

// 2. By merging all vertices to their parents in case the condition above holds, we will compress the tree into another
// tree, where each "vertex" in the compressed tree is a set of several vertices that were merged. We can merge the vertices
// by using Union-Find and DSU on Tree. Call the compressed tree T.

// 3. A process of merging two states X and Y is equivalent to merging all vertices in the path from S(X) to S(Y) in T
// into a single vertex, where S(x) is the vertex in T that state x is. That is, we mark every vertex in the path S(X)->S(Y).
// Our goal is to mark every vertex with as few merges as possible. Notice, then, that is is optimal to choose X and Y as leaves in T.
// Define the amount of leaves as L. If we sort leaves by their order, we can choose the pairs of leaves (1, (L/2)+1), (2, (L/2)+2), etc. and7
// like this, cover all vertices. Therefore, the answer is (L+1)/2.

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5+10;

int n, k;

// union find stuff
int pai[maxn], peso[maxn];

int s[maxn], tot[maxn];

// dsu on tree stuff
int in[maxn], out[maxn], val[maxn], sz[maxn], tt;
int qtdZero, qtdTot, sub[maxn];

int grau[maxn];

vector<int> grafo[maxn];

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

void dfs(int u, int p)
{
	sz[u] = 1;
	in[u] = ++tt, val[tt] = s[u];

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		dfs(v, u);

		sz[u] += sz[v];
	}

	out[u] = tt;
}

void solve(int u, int p, bool heavy)
{
	int maior = -1, ind = -1;

	for (auto v: grafo[u])
		if (v != p && sz[v] > maior)
			maior = sz[v], ind = v;

	for (auto v: grafo[u])
		if (v != p && v != ind)
			solve(v, u, 0);

	if (ind != -1)
		solve(ind, u, 1);

	--sub[s[u]];

	if (sub[s[u]] == 0)
		++qtdZero;
	if (sub[s[u]] == tot[s[u]]-1)
		--qtdTot;

	for (auto v: grafo[u])
	{
		if (v != p && v != ind)
		{
			for (int i = in[v]; i <= out[v]; i++)
			{
				--sub[val[i]];
				
				if (sub[val[i]] == 0)
					++qtdZero;
				if (sub[val[i]] == tot[val[i]]-1)
					--qtdTot;
			}
		}
	}

	if (qtdZero+qtdTot < k)
		Join(u, p);

	if (!heavy)
	{
		for (int i = in[u]; i <= out[u]; i++)
		{
			++sub[val[i]];
			
			if (sub[val[i]] == 1)
				--qtdZero;
			if (sub[val[i]] == tot[val[i]])
				++qtdTot;
		}
	}
}

int main(void)
{
	scanf("%d %d", &n, &k);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &s[i]);

		tot[s[i]]++;
		sub[s[i]]++;
	}


	Init();

	dfs(1, 0);

	qtdTot = k;
	solve(1, 0, 0);

	for (int i = 1; i <= n; i++)
		for (auto v: grafo[i])
			if (Find(v) != Find(i))
				grau[Find(v)]++;

	int leaf = 0;

	for (int i = 1; i <= n; i++)
		if (grau[i] == 1)
			leaf++;

	printf("%d\n", (leaf+1)/2);
}
