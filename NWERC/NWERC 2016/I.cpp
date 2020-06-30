// Codeforces - NWERC 2016 - Problem I - Iron and Coal
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int inf = 1e9+10;

int n;

int d1[maxn], d_iron[maxn], d_coal[maxn];

bool iron[maxn], coal[maxn];

bool mark[maxn];

vector<int> grafo[maxn];
vector<int> grafo_r[maxn];

void bfs(int q)
{
	memset(mark, 0, sizeof mark);
	queue<int> fila;

	if (q == 1) fila.push(1), d1[1] = 0, mark[1] = 1;
	else if (q == 2)
	{
		for (int i = 1; i <= n; i++)
			if (iron[i])
				fila.push(i), d_iron[i] = 0, mark[i] = 1;
	}
	else
	{
		for (int i = 1; i <= n; i++)
			if (coal[i])
				fila.push(i), d_coal[i] = 0, mark[i] = 1;
	}

	while (!fila.empty())
	{
		int u = fila.front(); fila.pop();

		if (q == 1)
		{
			for (auto v: grafo[u])
			{
				if (mark[v]) continue;

				d1[v] = d1[u]+1;
				fila.push(v), mark[v] = 1;
			}
		}
		else
		{
			for (auto v: grafo_r[u])
			{
				if (mark[v]) continue;

				if (q == 2)
					d_iron[v] = d_iron[u]+1;
				else
					d_coal[v] = d_coal[u]+1;

				fila.push(v), mark[v] = 1;
			}
		}
	}
}

int main(void)
{
	int m, k;	
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 1; i <= m; i++)
	{
		int u;
		scanf("%d", &u);

		iron[u] = 1;
	}

	for (int i = 1; i <= k; i++)
	{
		int u;
		scanf("%d", &u);

		coal[u] = 1;
	}

	for (int i = 1; i <= n; i++)
	{
		int e;
		scanf("%d", &e);

		for (int j = 1; j <= e; j++)
		{
			int v;
			scanf("%d", &v);

			grafo[i].push_back(v);
			grafo_r[v].push_back(i);
		}
	}

	for (int i = 1; i <= n; i++)
		d1[i] = d_iron[i] = d_coal[i] = inf;

	bfs(1); bfs(2); bfs(3);

	int ans = inf;

	for (int w = 1; w <= n; w++)
		if (d1[w] != inf && d_iron[w] != inf && d_coal[w] != inf)
			ans = min(ans, d1[w] + d_iron[w] + d_coal[w]);

	if (ans != inf) printf("%d\n", ans);
	else printf("impossible\n");
}
