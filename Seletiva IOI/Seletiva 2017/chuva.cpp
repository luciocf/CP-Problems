// Seletiva IOI 2017 - Chuva
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3+10;

const int maxk = 253;

int num[maxn][maxn], tipo[maxn][maxn], n, m;

bool mark[maxn][maxn];

bitset<maxk> tree[4*maxn][4*maxn], B[maxn][maxn];

int linha[] = {-1, 1, 0, 0};
int coluna[] = {0, 0, -1, 1};

void build_y(int nodex, int lx, int rx, int nodey, int ly, int ry)
{
	if (ly == ry)
	{
		if (lx == rx) tree[nodex][nodey] = B[lx][ry];
		else tree[nodex][nodey] = tree[2*nodex][nodey]|tree[2*nodex+1][nodey];
		return;
	}

	int my = (ly+ry)>>1;

	build_y(nodex, lx, rx, 2*nodey, ly, my); build_y(nodex, lx, rx, 2*nodey+1, my+1, ry);

	tree[nodex][nodey] = tree[nodex][2*nodey]|tree[nodex][2*nodey+1];
}

void build_x(int nodex, int lx, int rx)
{
	int mx = (lx+rx)>>1;

	if (lx != rx)
	{
		build_x(2*nodex, lx, mx); build_x(2*nodex+1, mx+1, rx);
	}

	build_y(nodex, lx, rx, 1, 1, m);
}

bitset<maxk> query_y(int nodex, int nodey, int ly, int ry, int ay, int by)
{
	if (ly > by || ry < ay) return 0;
	if (ly >= ay && ry <= by) return tree[nodex][nodey];

	int my = (ly+ry)>>1;

	return (query_y(nodex, 2*nodey, ly, my, ay, by)|query_y(nodex, 2*nodey+1, my+1, ry, ay, by));
}

bitset<maxk> query_x(int nodex, int lx, int rx, int ax, int bx, int ay, int by)
{
	if (lx > bx || rx < ax) return 0;
	if (lx >= ax && rx <= bx) return query_y(nodex, 1, 1, m, ay, by);

	int mx = (lx+rx)>>1;

	return (query_x(2*nodex, lx, mx, ax, bx, ay, by)|query_x(2*nodex+1, mx+1, rx, ax, bx, ay, by));
}

void bfs(int x, int y)
{
	memset(mark, 0, sizeof mark);

	int tt = tipo[x][y];

	queue<pair<int, int> > fila;
	fila.push({x, y}), mark[x][y] = 1;
	B[x][y][tt] = 1;

	while (!fila.empty())
	{
		int x = fila.front().first, y = fila.front().second;
		fila.pop();

		for (int i = 0; i < 4; i++)
		{
			int a = x+linha[i], b = y+coluna[i];

			if (a < 1 || a > n || b < 1 || b > m) continue;

			if (mark[a][b] || num[a][b] < num[x][y]) continue;

			B[a][b][tt] = 1;
			fila.push({a, b}), mark[a][b] = 1;
		}
	}
}

int main(void)
{
	int k;
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &num[i][j]);

	for (int i = 1; i <= k; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);

		tipo[a][b] = i-1;

		bfs(a, b);
	}

	build_x(1, 1, n);

	int q;
	cin >> q;

	for (int i = 1; i <= q; i++)
	{
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

		printf("%d\n", (int)query_x(1, 1, n, x1, x2, y1, y2).count());
	}
}