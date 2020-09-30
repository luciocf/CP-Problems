// Codeforces 891C - Envy
// Lúcio Cardoso

// Solution is (almost) the same as in editorial. The main difference is that I used DSU with Rollbacks
// to check for cycles.

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 5e5+10;

struct Edge
{
	int u, v, w, ind;
} edge[maxn];

struct Op
{
	int x, pesoX, y, pesoY;
};

struct DSU
{
	int pai[maxn], peso[maxn];
	stack<Op> stk;
 
	void init(int n)
	{
		for (int i = 1; i <= n; i++)
			pai[i] = i, peso[i] = 1;
	}
 
	int Find(int x)
	{
		if (pai[x] == x) return x;
		return Find(pai[x]);
	}
 
	void Join(int x, int y)
	{
		x = Find(x), y = Find(y);
		if (x == y)
		{
			Op vazio = Op();
			stk.push(vazio);
 
			return;
		}
 
		if (peso[x] < peso[y]) swap(x, y);
 
		Op aux;

		aux.x = x, aux.pesoX = peso[x];
		aux.y = y, aux.pesoY = peso[y];
 
		stk.push({x, peso[x], y, peso[y]});
 
		pai[y] = x, peso[x] += peso[y];
	}
 
	void Rollback(void)
	{
		if (stk.empty() || stk.top().x == -1)
		{
			if (!stk.empty()) stk.pop();
			return;
		}
 
		Op topo = stk.top();
		stk.pop();
 
		int x = topo.x, pesoX = topo.pesoX;
		int y = topo.y, pesoY = topo.pesoY;
 
		pai[x] = x, peso[x] = pesoX, pai[y] = y, peso[y] = pesoY;
	}
} dsu;

int back[maxn];

vector<vector<pii>> V[maxn];

bool ruim[maxn];

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		scanf("%d %d %d", &edge[i].u, &edge[i].v, &edge[i].w);
		edge[i].ind = i;
	}

	sort(edge+1, edge+m+1, [&] (Edge a, Edge b) {return a.w < b.w;});

	for (int i = 1; i <= m; i++)
		back[edge[i].ind] = i;

	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++)
	{
		int k;
		scanf("%d", &k);

		vector<int> e;

		while (k--)
		{
			int ind;
			scanf("%d", &ind);

			e.push_back(back[ind]);
		}

		sort(e.begin(), e.end(), [&] (int a, int b) {return edge[a].w < edge[b].w;});

		for (int j = 0; j < e.size(); j++)
		{
			int w = edge[e[j]].w;

			if (j != (int)e.size()-1 && edge[e[j+1]].w == w) continue;

			V[w].push_back(vector<pii>(0));

			for (int l = j; l >= 0 ; l--)
			{
				if (edge[e[l]].w != w) break;

				V[w].back().push_back({e[l], i});
			}
		}
	}

	dsu.init(n);

	int ind = 1;

	for (int i = 1; i < maxn; i++)
	{
		while (ind <= m && edge[ind].w < i)
		{
			if (dsu.Find(edge[ind].u) != dsu.Find(edge[ind].v))
				dsu.Join(edge[ind].u, edge[ind].v);

			++ind;
		}

		for (auto E: V[i])
		{
			int qtd = 0;

			for (int j = 0; j < E.size(); j++)
			{
				int u = edge[E[j].ff].u, v = edge[E[j].ff].v;

				if (dsu.Find(u) == dsu.Find(v)) ruim[E[j].ss] = 1;
				else
				{
					dsu.Join(u, v);
					qtd++;
				}
			}

			for (int j = 0; j < qtd; j++)
				dsu.Rollback();
		}
	}

	for (int i = 1; i <= q; i++)
	{
		if (!ruim[i]) printf("YES\n");
		else printf("NO\n");
	}
}
