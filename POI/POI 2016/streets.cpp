// POI 2016 - Vari-directional Streets
// Lúcio Cardoso

// Solution:

// 1. Compress SCCs and get the topological sort in the resulting DAG. Let ord[u] be the position
// of vertex u in the top. sort. Also, define mn[u] as the vertex with smallest value ord[] that u reaches, 
// and define mx[u] as the vertex with largest value ord[] that reaches u.

// 2. If a vertex u is correct, every vertex with order smaller than ord[u] should reach u and u
// should reach every vertex with order larger that u. If vertex u is incorrect, one of these cases occur:
//	* There is a vertex v with ord[v] < ord[u] such that mn[v] > ord[u].
//	* There is a vertex v with ord[v] > ord[u] such that mx[v] < ord[u].
// If none of the above conditions are true, then u is valid.

// 3. We can calculate mn[] and mx[] easily in O(n+m). The only detail is that we need to calculate mx[] using
// the DAG with edges reversed. Then, we can check if the conditions above are true for a vertex with a linear
// pass in the vertices sorted increasingly/decreasingly by value ord[], respectively.

// Complexity: O(n+m) (I used sort() to sort the answer but that's not really necessary)

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5+10;
const int inf = 1e9+10;

int n, m;

int in[maxn], low[maxn], tt, cc;

int scc[maxn];

int ord[maxn], x;
int mn[maxn], mx[maxn];

bool mark[maxn];
bool ok1[maxn], ok2[maxn];

vector<int> grafo[maxn], dag[maxn], dagT[maxn];
vector<int> inScc[maxn], topo;

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
			inScc[cc].push_back(v);

			if (v == u) break;
		}
	}
}

void dfs2(int u)
{
	mark[u] = true;

	for (auto v: dag[u])
		if (!mark[v])
			dfs2(v);

	topo.push_back(u);
	ord[u] = x, x--;
}

bool comp1(int a, int b){return ord[a] < ord[b];}

bool comp2(int a, int b){return ord[a] > ord[b];}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
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

	x = cc;
	for (int i = 1; i <= cc; i++)
		if (!mark[i])
			dfs2(i);

	for (int u = 1; u <= cc; u++)
	{
		mn[u] = inf;

		for (auto v: dag[u])
			mn[u] = min(mn[u], ord[v]);

		mx[u] = 0;

		for (auto v: dagT[u])
			mx[u] = max(mx[u], ord[v]);
	}

	int M = 0;
	for (int i = topo.size()-1; i >= 0; i--)
	{
		int u = topo[i];
		ok1[u] = true;

		if (M > ord[u])
			ok1[u] = false;

		M = max(M, mn[u]);
	}

	M = inf;
	for (int i = 0; i < topo.size(); i++)
	{
		int u = topo[i];
		ok2[u] = true;

		if (M < ord[u])
			ok2[u] = false;

		M = min(M, mx[u]);
	}

	vector<int> ans;

	for (int i = 1; i <= cc; i++)
		if (ok1[i] && ok2[i])
			for (auto v: inScc[i])
				ans.push_back(v);

	sort(ans.begin(), ans.end());

	printf("%d\n", ans.size());

	for (int i = 0; i < ans.size(); i++)
	{
		printf("%d", ans[i]);
		
		if (i == ans.size()-1) printf("\n");
		else printf(" ");
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
