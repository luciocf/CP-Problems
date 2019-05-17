// USACO 2016-2017 - Lasers and Mirrors
// Lúcio Cardoso

#include <bits/stdc++.h>

#define NORTH 0
#define SOUTH 1
#define WEST 2
#define EAST 3

using namespace std;

const int maxn = 1e5+10;
const int inf = 1e9+10;

typedef pair<int, int> pii;

int n, xl, yl, xb, yb;
int x[maxn], y[maxn];

vector<pii> linha[maxn], coluna[maxn];

int nxt[maxn][4];

int dist[maxn][4];

int opp[4] = {1, 0, 3, 2};

void compress_x(void)
{
	map<int, int> mp;

	mp[xl] = 0, mp[xb] = 0;
	for (int i = 1; i <= n; i++)
		mp[x[i]] = 0;

	int ind = 0;
	for (auto &x: mp)
		x.second = ++ind;

	xl = mp[xl], xb = mp[xb];
	for (int i = 1; i <= n; i++)
		x[i] = mp[x[i]];
}

void compress_y(void)
{
	map<int, int> mp;

	mp[yl] = 0, mp[yb] = 0;
	for (int i = 1; i <= n; i++)
		mp[y[i]] = 0;

	int ind = 0;
	for (auto &x: mp)
		x.second = ++ind;

	yl = mp[yl], yb = mp[yb];
	for (int i = 1; i <= n; i++)
		y[i] = mp[y[i]];
}

void bfs(int u)
{
	for (int i = 0; i <= n+1; i++)
		for (int j = 0; j < 4; j++)
			dist[i][j] = inf;

	deque<pii> dq;

	for (int i = 0; i < 4; i++)
		dq.push_front({u, i});

	dist[u][0] = dist[u][1] = dist[u][2] = dist[u][3] = 0;

	while (!dq.empty())
	{
		int u = dq.front().first, from = dq.front().second;
		dq.pop_front();

		for (int i = 0; i < 4; i++)
		{
			if (i == opp[from]) continue;

			int v = nxt[u][i];

			if (v == -1) continue;

			int w = (i == from ? 0 : 1);

			if (dist[v][i] > dist[u][from]+w)
			{
				dist[v][i] = dist[u][from]+w;

				if (w == 0) dq.push_front({v, i});
				else dq.push_back({v, i});
			}
		}
	}
}

int main(void)
{
	FILE *fin = fopen("lasers.in", "r");
	FILE *fout = fopen("lasers.out", "w");

	fscanf(fin, "%d %d %d %d %d", &n, &xl, &yl, &xb, &yb);

	for (int i = 1; i <= n; i++)
		fscanf(fin, "%d %d", &x[i], &y[i]);

	compress_x(); compress_y();

	linha[yl].push_back({xl, 0});
	coluna[xl].push_back({yl, 0});

	linha[yb].push_back({xb, n+1});
	coluna[xb].push_back({yb, n+1});

	for (int i = 1; i <= n; i++)
	{
		linha[y[i]].push_back({x[i], i});
		coluna[x[i]].push_back({y[i], i});
	}

	for (int i = 1; i <= 100000; i++)
		sort(linha[i].begin(), linha[i].end());

	for (int i = 1; i <= 100000; i++)
		sort(coluna[i].begin(), coluna[i].end());

	for (int i = 1; i <= 100000; i++)
	{
		if (linha[i].size() == 0) continue;

		nxt[linha[i][0].second][WEST] = -1;

		for (int j = 1; j < linha[i].size(); j++)
		{
			int at = linha[i][j].second, prev = linha[i][j-1].second;
			nxt[at][WEST] = prev;
		}

		nxt[linha[i].back().second][EAST] = -1;

		for (int j = linha[i].size()-2; j >= 0; j--)
		{
			int at = linha[i][j].second, prev = linha[i][j+1].second;
			nxt[at][EAST] = prev;
		}
	}

	for (int i = 1; i <= 100000; i++)
	{
		if (coluna[i].size() == 0) continue;

		nxt[coluna[i][0].second][SOUTH] = -1;

		for (int j = 1; j < coluna[i].size(); j++)
		{
			int at = coluna[i][j].second, prev = coluna[i][j-1].second;
			nxt[at][SOUTH] = prev;
		}

		nxt[coluna[i].back().second][NORTH] = -1;

		for (int j = coluna[i].size()-2; j >= 0; j--)
		{
			int at = coluna[i][j].second, prev = coluna[i][j+1].second;
			nxt[at][NORTH] = prev;
		}
	}

	bfs(0);

	int ans = inf;

	ans = min({ans, dist[n+1][0], dist[n+1][1], dist[n+1][2], dist[n+1][3]});

	if (ans == inf)
		fprintf(fout, "-1\n");
	else
		fprintf(fout, "%d\n", ans);
}
