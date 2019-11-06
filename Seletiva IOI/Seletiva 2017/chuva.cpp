// Seletiva IOI 2017 - Chuva
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e3+5;
const int maxk = 252;

int n, m, k;
int h[maxn][maxn];

bool mark[maxn][maxn];

bitset<maxk> tree[3*maxn][3*maxn], bs[maxn][maxn];

int linha[] = {-1, 1, 0, 0};
int coluna[] = {0, 0, -1, 1};

void build_y(int node_x, int l_x, int r_x, int node_y, int l_y, int r_y)
{
	if (l_y == r_y)
	{
		if (l_x == r_x) tree[node_x][node_y] = bs[l_x][l_y];
		else tree[node_x][node_y] = tree[2*node_x][node_y]|tree[2*node_x+1][node_y];
		return;
	}

	int mid = (l_y+r_y)>>1;

	build_y(node_x, l_x, r_x, 2*node_y, l_y, mid);
	build_y(node_x, l_x, r_x, 2*node_y+1, mid+1, r_y);

	tree[node_x][node_y] = tree[node_x][2*node_y]|tree[node_x][2*node_y+1];
}

void build_x(int node_x, int l_x, int r_x)
{
	int mid = (l_x+r_x)>>1;

	if (l_x != r_x)
	{
		build_x(2*node_x, l_x, mid);
		build_x(2*node_x+1, mid+1, r_x);
	}

	build_y(node_x, l_x, r_x, 1, 1, m);
}

bitset<maxk> query_y(int node_x, int node_y, int l_y, int r_y, int a_y, int b_y)
{
	if (l_y > b_y || r_y < a_y) return 0;
	if (l_y >= a_y && r_y <= b_y) return tree[node_x][node_y];

	int mid = (l_y+r_y)>>1;

	return query_y(node_x, 2*node_y, l_y, mid, a_y, b_y)|query_y(node_x, 2*node_y+1, mid+1, r_y, a_y, b_y);
}

bitset<maxk> query_x(int node_x, int l_x, int r_x, int a_x, int b_x, int a_y, int b_y)
{
	if (l_x > b_x || r_x < a_x) return 0;
	if (l_x >= a_x && r_x <= b_x) return query_y(node_x, 1, 1, m, a_y, b_y);

	int mid = (l_x+r_x)>>1;

	return query_x(2*node_x, l_x, mid, a_x, b_x, a_y, b_y)|query_x(2*node_x+1, mid+1, r_x, a_x, b_x, a_y, b_y);
}

void bfs(int x, int y, int t)
{
	memset(mark, 0, sizeof mark);

	queue<pii> fila;

	bs[x][y][t] = 1;
	fila.push({x, y}), mark[x][y] = 1;

	while (!fila.empty())
	{
		int x = fila.front().first, y = fila.front().second;
		fila.pop();

		for (int i = 0; i < 4; i++)
		{
			int a = x+linha[i], b = y+coluna[i];

			if (a < 1 || a > n || b < 1 || b > m || mark[a][b] || h[a][b] < h[x][y]) continue;

			bs[a][b][t] = 1;
			fila.push({a, b}), mark[a][b] = 1;
		}
	}
}

int main(void)
{
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &h[i][j]);

	for (int i = 1; i <= k; i++)
	{
		int x, y;
		scanf("%d %d", &x, &y);

		bfs(x, y, i-1);
	}

	build_x(1, 1, n);

	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++)
	{
		int a_x, b_x, a_y, b_y;

		scanf("%d %d %d %d", &a_x, &a_y, &b_x, &b_y);

		printf("%d\n", (int)query_x(1, 1, n, a_x, b_x, a_y, b_y).count());
	}
}
