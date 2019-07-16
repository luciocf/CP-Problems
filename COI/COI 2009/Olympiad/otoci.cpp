// COI 2009 - Otoci
// Lúcio Cardoso

// ACs at PEG but TLEs at DMOJ :(

// Solution is the same as this one: http://hsin.hr/coci/archive/2008_2009/

// Ideia is to use small to large when adding an edge and reconstruct HLD at every
// sqrt(n) edges added

// Complexity: O(Q * sqrt(n) * log n)

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e4+10;
const int maxc = 3e6+10;
const int bucket = 180;

int n;
int val[maxn];

int bit[maxc];

int nivel[maxn], pai[maxn], sz[maxn];
int comp[maxn], root[maxn], szComp[maxn];

int head[maxc], chain[maxn], pos[maxn];
int chainCnt, posCnt;

int edgeCnt;

vector<int> grafo[maxn];

void upd(int x, int v)
{
	for (; x < maxc; x += (x&-x))
		bit[x] += v;
}

int soma(int x)
{
	int ans = 0;
	for (; x > 0; x -= (x&-x))
		ans += bit[x];
	return ans;
}

int dfs_sz(int u, int p)
{
	sz[u] = 1;

	for (auto v: grafo[u])
		if (v != p)
			sz[u] += dfs_sz(v, u);

	return sz[u];
}

void dfs(int u, int p)
{
	sz[u] = 1;

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		pai[v] = u, nivel[v] = nivel[u]+1;
		comp[v] = comp[u], szComp[comp[u]]++;

		dfs(v, u);

		sz[u] += sz[v];
	}
}

void hld(int u, int p)
{
	if (!head[chainCnt]) head[chainCnt] = u;

	upd(pos[u], -val[u]);
	chain[u] = chainCnt, pos[u] = ++posCnt;
	upd(pos[u], val[u]);

	int maior = -1, ind = -1;
	for (auto v: grafo[u])
		if (v != p && sz[v] > maior)
			maior = sz[v], ind = v;

	if (ind != -1)
		hld(ind, u);

	for (auto v: grafo[u])
		if (v != p && v != ind)
			++chainCnt, hld(v, u);
}

void rebuild(void)
{
	chainCnt = 0, posCnt = 0, edgeCnt = 0;
	memset(head, 0, sizeof head);
	memset(chain, 0, sizeof chain);

	for (int i = 1; i <= n; i++)
	{
		if (root[comp[i]] == i)
		{
			++chainCnt;
			dfs_sz(i, 0);
			hld(i, 0);
		}
	}
}

int add(int u, int v)
{
	if (comp[u] == comp[v]) return 0;

	if (szComp[comp[u]] < szComp[comp[v]]) swap(u, v);

	grafo[u].push_back(v); grafo[v].push_back(u);

	pai[v] = u, nivel[v] = nivel[u]+1;
	comp[v] = comp[u], szComp[comp[u]]++;

	dfs(v, u);

	++chainCnt;
	hld(v, u);

	if (++edgeCnt == bucket)
		rebuild();

	return 1;
}

int lca(int u, int v)
{
	while (chain[u] != chain[v])
	{
		if (nivel[head[chain[u]]] > nivel[head[chain[v]]])
			u = pai[head[chain[u]]];
		else
			v = pai[head[chain[v]]];
	}

	return (nivel[u] > nivel[v] ? v : u);
}

void updPath(int u, int v)
{
	upd(pos[u], v-val[u]);
	val[u] = v;
}

int queryPath(int u, int v)
{	
	int ans = 0;

	while (true)
	{
		if (chain[u] == chain[v])
			return (ans + soma(pos[u]) - soma(pos[v]-1));

		ans += (soma(pos[u])-soma(pos[head[chain[u]]]-1));
		u = pai[head[chain[u]]];
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin >> n;

	chainCnt = n, posCnt = n;
	for (int i = 1; i <= n; i++)
	{
		cin >> val[i];

		sz[i] = 1, chain[i] = i, head[i] = i, pos[i] = i;
		comp[i] = i, szComp[i] = 1, root[i] = i;

		upd(i, val[i]);
	}

	int q;
	cin >> q;

	while (q--)
	{
		string s;
		int a, b;
		cin >> s >> a >> b;

		if (s == "bridge")
		{
			int x = add(a, b);

			if (x) cout << "yes\n";
			else cout << "no\n";

			cout << flush;
		}
		else if (s == "penguins")
		{
			updPath(a, b);
		}
		else
		{
			if (comp[a] != comp[b])
			{
				cout << "impossible\n";
				cout << flush;
				continue;
			}

			int l = lca(a, b);

			cout << queryPath(a, l) + queryPath(b, l) - val[l] << "\n";
			cout << flush;
		}
	}
}
