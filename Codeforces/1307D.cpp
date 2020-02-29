// Codeforces 1307D - Cow and Fields
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

const int maxn = 2e5+10;

typedef pair<int, int> pii;

int n;
int dist[maxn][2];

bool mark[maxn];

pii vert[maxn];

vector<int> grafo[maxn];

void bfs(bool q)
{
	queue<int> fila;

	if (q == 0) fila.push(1), dist[1][q] = 0;
	else fila.push(n), dist[n][q] = 0;

	while (!fila.empty())
	{
		int u = fila.front(); fila.pop();

		for (auto v: grafo[u])
		{
			if (dist[v][q] == -1)
			{
				dist[v][q] = dist[u][q]+1;
				fila.push(v);
			}
		}
	}
}

int main(void)
{
	int m, k;
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 1; i <= k; i++)
	{
		int u;
		scanf("%d", &u);

		mark[u] = 1;
	}

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	memset(dist, -1, sizeof dist);
	bfs(0); bfs(1);

	int l = 0;

	for (int i = 1; i <= n; i++)
		if (mark[i])
			vert[++l] = {dist[i][1], dist[i][0]};

	sort(vert+1, vert+l+1);

	multiset<int> st;
	for (int i = 1; i <= l; i++)
		st.insert(-vert[i].ss);

	int ans = -m-1;

	for (int i = 1; i < l; i++)
	{
		auto it = st.find(-vert[i].ss);
		st.erase(it);

		ans = max(ans, vert[i].ff - *st.begin() + 1);
	}

	printf("%d\n", min(ans, dist[n][0]));
}
