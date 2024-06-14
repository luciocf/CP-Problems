// ARC 177C - Routing
// Lucio Figueiredo

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <cstring>
#include <set>
#include <map>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 510;

int row[] = {-1, 1, 0, 0};
int col[] = {0, 0, -1, 1};

int n;
int dist[2][maxn][maxn];

char a[maxn][maxn];

void bfs(int q)
{
	deque<pii> dq;
	
	if (q == 0)
	{
		dq.push_front({1, 1});
		dist[0][1][1] = 0;
	}
	else
	{
		dq.push_front({1, n});
		dist[1][1][n] = 0;
	}

	while (!dq.empty())
	{
		int x = dq.front().ff, y = dq.front().ss;
		dq.pop_front();

		for (int i = 0; i < 4; i++)
		{
			int u = x+row[i], v = y+col[i];
			if (u < 1 or u > n or v < 1 or v > n) continue;
			if (dist[q][u][v] != -1) continue;

			if ((q == 0 and a[u][v] == 'B') or (q == 1 and a[u][v] == 'R'))
			{
				dist[q][u][v] = dist[q][x][y]+1;
				dq.push_back({u, v});
			}
			else
			{
				dist[q][u][v] = dist[q][x][y];
				dq.push_front({u, v});
			}
		}
	}
}

int main(void)
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> a[i][j];

	memset(dist, -1, sizeof dist);

	bfs(0); bfs(1);

	cout << dist[0][n][n]+dist[1][n][1] << "\n";
}
