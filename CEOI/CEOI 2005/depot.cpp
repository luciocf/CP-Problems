// CEOI 2005 - Depot Rearrangement
// Lúcio Cardoso

// Solution: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/CEOI/official/2005/soldepot.pdf

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 410;
const int maxe = 1e6+10;

struct Edge
{
	int v, pos, ind;
};

int n, m;

int a[maxn*maxn];

bool mark[maxe];

vector<int> pos[maxn][maxn];
vector<int> path;

vector<Edge> grafo[2*maxn];

void build_graph(void)
{
	int e = 0;

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (pos[j][i+1].size() == 0) grafo[i].push_back({j+m, -1, ++e});
			else
			{
				for (int l = 1; l < pos[j][i+1].size(); l++)
					grafo[j+m].push_back({i, pos[j][i+1][l], ++e});
			}
		}
	}
}

void dfs(int u)
{
	for (auto E: grafo[u])
	{
		int v = E.v, p = E.pos, ind = E.ind;
		if (mark[ind]) continue;

		mark[ind] = 1;
		dfs(v);

		if (p != -1) path.push_back(p);
	}
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n*m; i++)
		scanf("%d", &a[i]);

	for (int i = 0; i < n; i++)
		for (int j = i*m; j < min(n*m, (i+1)*m); j++)
			pos[i][a[j]].push_back(j+1);

	build_graph();

	vector<pii> ans;

	for (int u = 0; u < n+m; u++)
	{
		path.clear();
		dfs(u);

		if (!path.size()) continue;

		ans.push_back({path[0], n*m+1});

		for (int i = 1; i < path.size(); i++)
			ans.push_back({path[i], path[i-1]});

		ans.push_back({n*m+1, path.back()});
	}

	printf("%d\n", ans.size());
	for (auto pp: ans)
		printf("%d %d\n", pp.first, pp.second);
}
