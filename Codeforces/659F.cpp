// Codeforces 659F - Polycarp and Hay
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 1e3+10;

struct S
{
	int v;
	int x, y;
};

int n, m;
ll k;

int a[maxn][maxn];

bool mark[maxn][maxn];
bool vis[maxn][maxn];

int tot;

int pai[maxn*maxn], peso[maxn*maxn];

int linha[] = {-1, 1, 0, 0};
int coluna[] = {0, 0, -1, 1};

int pos(int i, int j)
{
	return m*(i-1) + j;
}

void init(void)
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			pai[pos(i, j)] = pos(i, j), peso[pos(i, j)] = 1;
}

int Find(int x)
{
	if (pai[x] == x) return x;
	return pai[x] = Find(pai[x]);
}

void Join(int x, int y)
{
	x = Find(x), y = Find(y);
	if (x == y) return;

	if (peso[x] < peso[y]) swap(x, y);
	pai[y] = x, peso[x] += peso[y];
}

void dfs(int x, int y)
{
	if (tot == 0) return;
	vis[x][y] = 1, tot--;

	for (int i = 0; i < 4; i++)
	{
		int a = x+linha[i], b = y+coluna[i];
		if (a < 1 || a > n || b < 1 || b > m || vis[a][b] || !mark[a][b]) continue;

		dfs(a, b);
	}
}

bool comp(S a, S b)
{
	return a.v > b.v;
}

int main(void)
{
	scanf("%d %d %lld", &n, &m, &k);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &a[i][j]);

	vector<S> ord;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			ord.push_back({a[i][j], i, j});

	sort(ord.begin(), ord.end(), comp);

	int mn = -1;

	init();

	for (auto Ord: ord)
	{
		int x = Ord.x, y = Ord.y;
		ll v = Ord.v;

		mark[x][y] = 1;

		for (int i = 0; i < 4; i++)
		{
			int a = x+linha[i], b = y+coluna[i];

			if (a < 1 || a > n || b < 1 || b > m || !mark[a][b]) continue;

			Join(pos(x, y), pos(a, b));
		}

		ll sz = peso[Find(pos(x, y))];
		if (k%v || sz < k/v) continue;

		mn = v, tot = k/v;

		dfs(x, y);
		break;
	}

	if (mn == -1)
	{
		printf("NO\n");
		return 0;
	}

	printf("YES\n");
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (vis[i][j]) printf("%d ", mn);
			else printf("0 ");
		}
		printf("\n");
	}
}
