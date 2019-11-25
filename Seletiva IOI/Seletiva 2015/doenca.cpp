// Seletiva IOI 2015 - Doença
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+2;

int n;
int S[maxn], V[maxn];

int ans;

int menor[maxn], child[maxn];

bool mark[maxn];

vector<int> grafo[maxn];

void solve(int u, int p)
{
	int aux = 0;

	for (auto v: grafo[u])
		if (v != p)
			solve(v, u);

	for (auto v: grafo[u])
	{
		if (v != p)
		{
			if (mark[v]) child[++aux] = menor[v];
			else V[u] = min(V[u], V[v]-1);
		}
	}

	int last = 0;

	sort(child+1, child+aux+1);

	for (int i = 1; i <= aux; i++)
	{
		if (child[i] >= V[u] || S[u] == 0) break;
		S[u]--, last = child[i];
	}

	if (!V[u]) mark[u] = 1, menor[u] = 0, ans++;
	else if (!S[u]) menor[u] = last+1, mark[u] = 1;
	else if (u == 1) ans++;
	else if (S[u] != 1) mark[u] = 1, menor[u] = 0, ans++;
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &S[i], &V[i]);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	solve(1, 0);

	printf("%d\n", ans);
}
