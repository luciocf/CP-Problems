// Seletiva IOI 2016 - Energia
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e5+10;
const int maxm = 6e5+10;

typedef pair<int, int> pii;

struct Aresta
{
	int u, v, w;
} edge[maxm];

struct UF
{
	int pai, peso, soma, id;
};

int a[maxn];

vector<UF> uf[maxn];

void init(int n)
{
	for (int i = 1; i <= n; i++)
		uf[i].push_back({i, 1, a[i], 0});
}

UF Find(int x, int tt)
{
	int ini = 0, fim = (int)uf[x].size()-1, ans = 0;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		if (uf[x][mid].id <= tt) ans = mid, ini = mid+1;
		else fim = mid-1;
	}

	if (uf[x][ans].pai == x) return {x, uf[x][ans].peso, uf[x][ans].soma, uf[x][ans].id};

	return Find(uf[x][ans].pai, tt);
}

void Join(int x, int y, int tt)
{
	UF UFx = Find(x, tt), UFy = Find(y, tt);

	x = UFx.pai, y = UFy.pai;
	if (x == y) return;

	if (UFx.peso < UFy.peso) swap(x, y);

	int peso_x = UFx.peso, peso_y = UFy.peso;
	int soma_x = UFx.soma, soma_y = UFy.soma;

	uf[x].push_back({x, peso_x+peso_y, soma_x+soma_y, tt});
	uf[y].push_back({x, peso_x+peso_y, soma_x+soma_y, tt});
}

bool comp(Aresta a, Aresta b) {return a.w < b.w;}

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	int tot = 0;
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]), tot += a[i];

	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		edge[i] = {u, v, w};
	}

	sort(edge+1, edge+m+1, comp);

	init(n);
	for (int i = 1; i <= m; i++)
		Join(edge[i].u, edge[i].v, edge[i].w);

	int q, ant = 0;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++)
	{
		int U, K;
		scanf("%d %d", &U, &K);
		K += ant;

		UF cc = Find(U, K);
		
		printf("%d\n", cc.soma);
		ant = cc.soma;
	}
}
