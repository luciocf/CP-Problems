// CEOI 2011 - Traffic
// Lúcio Cardoso

// Solution:

// 1. Remove all west vertices that can't be reached by east vertices. Since the graph
// is planar, we can notice that for every vertex in the east side, the points it can reach
// in the west are a contiguous interval.

// 2. Let up[U] be the index of the topmost west vertex U can reach, where U is an east vertex
// Define down[U] similarly. Thus, the answer for U is up[u] - down[u] + 1. (Remember we're ignoring
// west points that are unreachable)

// 3. To calculate up[] and down[], compress the SCCs in the graph. We will calculate up[] and
// down[] for each SCC in the resulting DAG. Then, traverse through the DAG in reverse topological
// sort. This way, we have that, when visiting u, for each v such that u -> v:

//	* up[u] := max(mxScc[u], up[v]), where mxScc[u] is the topmost west vertex in SCC u
//	* down[u] := min(mnScc[u], down[v]), where mnScc[u] is the downmost west vertex in SCC u

// 4. We can find the unreachable west vertices similarly, but traversing the transposed DAG
// in topological order.

// Complexity: O(n log n)

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 3e5+10;
const int inf = 1e9+10;

int n, m, A, B;
int x[maxn], y[maxn];

int in[maxn], low[maxn], scc[maxn], tt, cc;

int mnScc[maxn], mxScc[maxn];

int up[maxn], down[maxn], mp[maxn];

bool mark[maxn], isEast[maxn], isWest[maxn];
bool sccEast[maxn], reach[maxn];

vector<int> grafo[maxn];
vector<int> dag[maxn], dagT[maxn], topo;

stack<int> stk;

void dfs(int u)
{
	in[u] = low[u] = ++tt;
	stk.push(u);

	for (auto v: grafo[u])
	{
		if (in[v])
		{
			low[u] = min(low[u], in[v]);
			continue;
		}

		dfs(v);

		low[u] = min(low[u], low[v]);
	}

	if (in[u] == low[u])
	{
		++cc;

		while (true)
		{
			int v = stk.top(); stk.pop();

			scc[v] = cc, in[v] = inf;

			if (isEast[v])
				sccEast[cc] = true;

			if (v == u) break;
		}
	}
}

void topsort(int u)
{
	mark[u] = true;

	for (auto v: dag[u])
		if (!mark[v])
			topsort(v);

	topo.push_back(u);
}

void getWest(void)
{
	reverse(topo.begin(), topo.end());

	for (auto u: topo)
	{
		if (sccEast[u])
			reach[u] = true;

		for (auto v: dagT[u])
			reach[u] |= reach[v];
	}

	reverse(topo.begin(), topo.end());
}

void getEast(void)
{
	for (int i = 1; i <= cc; i++)
		up[i] = 0, down[i] = inf;

	for (auto u: topo)
	{
		up[u] = max(up[u], mxScc[u]);
		down[u] = min(down[u], mnScc[u]);

		for (auto v: dag[u])
		{
			up[u] = max(up[u], up[v]);
			down[u] = min(down[u], down[v]);
		}
	}
}

int main(void)
{
	scanf("%d %d %d %d", &n, &m, &A, &B);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d", &x[i], &y[i]);

		if (x[i] == 0) isEast[i] = true;
		if (x[i] == A) isWest[i] = true;
	}

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		if (w == 1)
			grafo[u].push_back(v);
		else
		{
			grafo[u].push_back(v);
			grafo[v].push_back(u);
		}
	}

	for (int i = 1; i <= n; i++)
		if (!in[i])
			dfs(i);

	for (int i = 1; i <= n; i++)
	{
		for (auto v: grafo[i])
		{
			if (scc[i] != scc[v])
			{
				dag[scc[i]].push_back(scc[v]);
				dagT[scc[v]].push_back(scc[i]);
			}
		}
	}

	for (int i = 1; i <= cc; i++)
		if (!mark[i])
			topsort(i);

	getWest();

	vector<pii> V;
	for (int i = 1; i <= n; i++)
		if (isWest[i])
			V.push_back({y[i], i});

	sort(V.begin(), V.end());

	int aux = 0;
	for (auto u: V)
		if (reach[scc[u.ss]])
			mp[u.ss] = ++aux;

	for (int i = 1; i <= cc; i++)
		mnScc[i] = inf, mxScc[i] = 0;

	for (int i = 1; i <= n; i++)
	{
		if (reach[scc[i]] && isWest[i])
		{
			mnScc[scc[i]] = min(mnScc[scc[i]], mp[i]);
			mxScc[scc[i]] = max(mxScc[scc[i]], mp[i]);
		}
	}

	getEast();

	V.clear();

	for (int i = 1; i <= n; i++)
		if (isEast[i])
			V.push_back({y[i], i});

	sort(V.begin(), V.end());

	for (int i = V.size()-1; i >= 0; i--)
	{
		int u = V[i].ss;

		if (!up[scc[u]]) printf("0\n");
		else printf("%d\n", up[scc[u]]-down[scc[u]]+1);
	}
}

/*
	* bounds (maxn)
	* long long
	* all variables reset?
	* check if indexing is ok
	* off by one? (n-i+1) or (n-i)?
	* edge cases (n=0, n=1, n < 0, n=maxn)
*/
