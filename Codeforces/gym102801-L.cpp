// The 14th Chinese Northeast Collegiate Programming Contest - L - PepperLa's Express
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e2+10;
const int inf = 1e9+10;

struct Pt
{
	int z, x, y;
};

int k, n, m;
char tab[maxn][maxn][maxn];

int dist[maxn][maxn][maxn];

void bfs(void)
{
	queue<Pt> fila;

	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int l = 0; l < m; l++)
			{
				if (tab[i][j][l] == '@')
				{
					fila.push({i, j, l});
					dist[i][j][l] = 0;
				}
			}
		}
	}

	while (!fila.empty())
	{
		int i = fila.front().z, j = fila.front().x, l = fila.front().y;
		fila.pop();

		for (int a = max(0, i-1); a <= min(k-1, i+1); a++)
		{
			for (int b = max(0, j-1); b <= min(n-1, j+1); b++)
			{
				for (int c = max(0, l-1); c <= min(m-1, l+1); c++)
				{
					if (abs(a-i)+abs(b-j)+abs(c-l) != 1) continue;

					if (dist[a][b][c] == -1)
					{
						dist[a][b][c] = dist[i][j][l] + 1;
						fila.push({a, b, c});
					}
				}
			}
		}
	}
}

int mx[10];

bool ok(int d)
{
	for (int i = 0; i < 8; i++)
		mx[i] = -inf;

	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int l = 0; l < m; l++)
			{
				if (tab[i][j][l] != '*' || dist[i][j][l] <= d) continue;

				for (int mask = 0; mask < 8; mask++)
				{
					int aux = 0;

					if (mask&(1<<0)) aux += i;
					else aux -= i;

					if (mask&(1<<1)) aux += j;
					else aux -= j;

					if (mask&(1<<2)) aux += l;
					else aux -= l;

					mx[mask] = max(mx[mask], aux);
				}
			}
		}
	}

	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int l = 0; l < m; l++)
			{
				if (tab[i][j][l] != '.') continue;

				int maior = -inf;

				for (int mask = 0; mask < 8; mask++)
				{
					int aux = 0;

					if (mask&(1<<0)) aux -= i;
					else aux += i;

					if (mask&(1<<1)) aux -= j;
					else aux += j;

					if (mask&(1<<2)) aux -= l;
					else aux += l;

					maior = max(maior, aux + mx[mask]);
				}

				if (maior <= d) return 1;
			}
		}
	}

	return 0;
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0);

	while (cin >> k >> n >> m)
	{
		for (int i = 0; i < k; i++)
			for (int j = 0; j < n; j++)
				for (int l = 0; l < m; l++)
					cin >> tab[i][j][l];

		memset(dist, -1, sizeof dist);
		bfs();

		int ini = 0, fim = 601, ans = 601;

		while (ini <= fim)
		{
			int mid = (ini+fim)>>1;

			if (ok(mid)) ans = mid, fim = mid-1;
			else ini = mid+1;
		}

		printf("%d\n", ans);
	}
}
