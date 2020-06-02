// POI 2009 - The Walk of Bytie-boy
// Lúcio Cardoso

// Solution: https://github.com/thecodingwizard/competitive-programming/blob/master/POI/POI09-Walk.cpp

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 410;
const int inf = 1e9+10;

struct S
{
	int a, b, c;
} node[maxn][maxn][30];

int n, m;
int lista[maxn];

int dist[maxn][maxn][30];
bool mark[maxn][maxn][30];

vector<pii> grafo[maxn], grafo_r[maxn];

void bfs(void)
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			for (int c = 0; c <= 26; c++)
				dist[i][j][c] = inf;

	queue<S> fila;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= 26; j++)
		{
			node[i][i][j] = {-1, -1, j};
			dist[i][i][j] = 0, mark[i][i][j] = 1;

			fila.push({i, i, j});
		}
	}

	while (!fila.empty())
	{
		S s = fila.front(); fila.pop();

		if (s.c == 26)
		{
			for (auto pp: grafo[s.b])
			{
				int v = pp.first, c = pp.second;

				if (!mark[s.a][v][c])
				{
					mark[s.a][v][c] = 1, dist[s.a][v][c] = dist[s.a][s.b][s.c]+1;
					node[s.a][v][c] = {s.a, s.b, s.c};

					fila.push({s.a, v, c});
				}
			}
		}
		else
		{
			for (auto pp: grafo_r[s.a])
			{
				int v = pp.first, c = pp.second;

				if (c == s.c && !mark[v][s.b][26])
				{
					mark[v][s.b][26] = 1, dist[v][s.b][26] = dist[s.a][s.b][s.c]+1;
					node[v][s.b][26] = {s.a, s.b, s.c};

					fila.push({v, s.b, 26});
				}
			}
		}
	}
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		char c;

		scanf("%d %d %c", &u, &v, &c);

		grafo[u].push_back({v, c-'a'});
		grafo_r[v].push_back({u, c-'a'});
	}

	int p;
	scanf("%d", &p);

	for (int i = 1; i <= p; i++)
		scanf("%d", &lista[i]);

	bfs();

	for (int i = 2; i <= p; i++)
	{
		int a = lista[i-1], b = lista[i];

		S s = node[a][b][26];

		if (dist[a][b][26] == inf)
		{
			printf("-1\n");
			continue;
		}

		printf("%d ", dist[a][b][26]);

		string out;
		char ant;

		while (s.a != -1)
		{
			if (s.c != 26)
			{
				printf("%c", (char)(s.c+'a'));
				ant = s.c+'a';
			}
			else out.push_back(ant);

			s = node[s.a][s.b][s.c];
		}

		reverse(out.begin(), out.end());

		cout << out << "\n";
	}
}
