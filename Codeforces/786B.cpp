// Codeforces 786B - Legacy
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef pair<ll, int> pii;
 
const int maxn = 9e5+10;
const ll inf = 1e18+10;
 
int n, q, s;
int aux;
 
int mp[2][maxn];
int leaf[maxn];
 
ll dist[maxn];
bool mark[maxn];

vector<pii> grafo[maxn];
 
void build(int node, int l, int r)
{
	if (l == r)
	{
		mp[0][node] = ++aux, mp[1][node] = ++aux;
		
		grafo[mp[0][node]].push_back({l, 0});
		grafo[l].push_back({mp[1][node], 0});
 
		return;
	}
 
	int mid = (l+r)>>1;
 
	build(2*node, l, mid); build(2*node+1, mid+1, r);
 
	mp[0][node] = ++aux, mp[1][node] = ++aux;
 
	grafo[mp[0][node]].push_back({mp[0][2*node], 0});
	grafo[mp[0][node]].push_back({mp[0][2*node+1], 0});

	grafo[mp[1][2*node]].push_back({mp[1][node], 0});
	grafo[mp[1][2*node+1]].push_back({mp[1][node], 0});
}
 
void add_edge(int node, int l, int r, int a, int b, int v, int w, int op)
{
	if (l > b || r < a) return;
 
	if (l >= a && r <= b)
	{
		if (op == 2) grafo[v].push_back({mp[0][node], w});
		else grafo[mp[1][node]].push_back({v, w});
 
		return;
	}
 
	int mid = (l+r)>>1;
 
	add_edge(2*node, l, mid, a, b, v, w, op);
	add_edge(2*node+1, mid+1, r, a, b, v, w, op);
}
 
void dijkstra(void)
{
	for (int i = 1; i < maxn; i++)
		dist[i] = inf;
 
	priority_queue<pii, vector<pii>, greater<pii>> fila;
 
	dist[s] = 0;
	fila.push({0, s});
 
	while (!fila.empty())
	{
		int u = fila.top().second; fila.pop();
 
		if (mark[u]) continue;
		mark[u] = 1;
 
		for (auto e: grafo[u])
		{
			int v = e.first, w = e.second;
 
			if (dist[v] > dist[u] + 1ll*w)
			{
				dist[v] = dist[u] + 1ll*w;
				fila.push({dist[v], v});
			}
		}
	}
}
 
int main(void)
{
	scanf("%d %d %d", &n, &q, &s);
 	
 	aux = n;
	build(1, 1, n);
 
	while (q--)
	{
		int op;
		scanf("%d", &op);
 
		if (op == 1)
		{
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
 
			grafo[u].push_back({v, w});
		}
		else
		{
			int v, l, r, w;
			scanf("%d %d %d %d", &v, &l, &r, &w);
 
			add_edge(1, 1, n, l, r, v, w, op);
		}
	}
 
	dijkstra();
 
	for (int i = 1; i <= n; i++)
	{
		if (dist[i] == inf) printf("-1 ");
		else printf("%lld ", dist[i]);
	}
	printf("\n");
}
