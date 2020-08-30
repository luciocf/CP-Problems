// Codeforces 1227E - Arson In Berland Forest
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e6+1;

int linha[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
int coluna[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

int n, m;

unordered_map<int, char> tab[maxn];
unordered_map<int, int> soma[maxn];
unordered_map<int, char> res[maxn];
unordered_map<int, bool> mark[maxn];

int get(int xa, int ya, int xb, int yb)
{
	return (soma[xb][yb]-soma[xb][ya-1]-soma[xa-1][yb]+soma[xa-1][ya-1]);
}

void bfs(vector<pii> &V, int k)
{
	queue<pair<pii, int>> fila;

	for (auto pp: V)
		fila.push({pp, 0});

	while (!fila.empty())
	{
		int x = fila.front().first.first, y = fila.front().first.second;
		int d = fila.front().second;
		fila.pop();

		if (d == k) continue;

		for (int i = 0; i < 9; i++)
		{
			int a = x+linha[i], b = y+coluna[i];

			if (a < 1 || a > n || b < 1 || b > m || mark[a][b]) continue;

			mark[a][b] = 1;
			fila.push({{a, b}, d+1});
		}
	}
}

bool ok(int k)
{
	vector<pii> V;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			mark[i][j] = 0;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			res[i][j] = '.';

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (i-k < 1 || j-k < 1 || i+k > n || j+k > m) continue;

			if (get(i-k, j-k, i+k, j+k) == (2*k+1)*(2*k+1))
			{
				mark[i][j] = 1;
				V.push_back({i, j});
				res[i][j] = 'X';
			}
		}
	}

	bfs(V, k);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (tab[i][j] == 'X' && !mark[i][j])
				return false;

	return true;
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin >> n >> m;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> tab[i][j];

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			soma[i][j] = soma[i-1][j] + soma[i][j-1] - soma[i-1][j-1] + (tab[i][j] == 'X');

	int ini = 0, fim = 1000001, ans = 0;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		if (ok(mid)) ans = mid, ini = mid+1;
		else fim = mid-1;
	}

	cout << ans << "\n";
	ok(ans);

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
			cout << res[i][j];
		cout << "\n";
	}
}
