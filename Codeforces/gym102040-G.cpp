// 2018-2019 ACM-ICPC, Asia Dhaka Regional Contest - G - Techland
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;
const int maxm = 1e5+10;
const int sq = 250;

int n;
vector<int> grafo[maxn];

int nivel[maxn];
int in[maxn], euler[maxn], tt;

struct SparseTable
{
	int lg[maxn], tab[maxn][20];

	void build(void)
	{
		lg[1] = 0;
		for (int i = 2; i < maxn; i++)
			lg[i] = lg[i/2]+1;

		for (int i = 0; i < maxn; i++)
			tab[i][0] = euler[i];

		for (int j = 1; j < 20; j++)
		    for (int i = 0; i + (1 << j) < maxn; i++)
		        tab[i][j] = min(tab[i][j-1], tab[i + (1<<(j-1))][j-1]);
	}

	int rmq(int l, int r)
	{
		int j = lg[r-l+1];
		return min(tab[l][j], tab[r-(1<<j)+1][j]);
	}
} ST;

void dfs(int u, int p)
{
	in[u] = tt;
	euler[tt++] = nivel[u];

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		nivel[v] = nivel[u]+1;
		dfs(v, u);
		euler[tt++] = nivel[u];
	}
}

int dist_vert(int u, int v)
{
	if (in[u] > in[v]) swap(u, v);

	return nivel[u]+nivel[v]-2*ST.rmq(in[u], in[v]);
}

struct Company
{
	vector<int> block;
	pii range_1, range_2;

	void init(void)
	{
		block.clear();
		range_1 = range_2 = {-1, -1};
	}
} company[maxm];

int dist[maxn][sq];

void bfs(int b)
{
	queue<int> fila;

	for (int i = b*sq; i < min(n, (b+1)*sq); i++)
	{
		fila.push(i+1);
		dist[i+1][b] = 0;
	}

	while (!fila.empty())
	{
		int u = fila.front(); fila.pop();

		for (auto v: grafo[u])
		{
			if (dist[v][b] != -1) continue;

			dist[v][b] = dist[u][b]+1;
			fila.push(v);
		}
	}
}

void add(int c, int l, int r)
{
	--l, --r;

	for (int i = l/sq+1; i < r/sq; i++)
		company[c].block.push_back(i);

	if (l/sq == r/sq)
	{
		company[c].range_1 = {l+1, r+1};
		return;
	}

	company[c].range_1 = {l+1, (l/sq+1)*sq};
	company[c].range_2 = {(r/sq)*sq+1, r+1};
}

void solve(int tc)
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		grafo[i].clear();
	for (int i = 1; i < maxm; i++)
		company[i].init();

	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	tt = 0;
	dfs(1, 0); ST.build();

	for (int i = 0; i < sq; i++)
	{
		for (int j = 1; j <= n; j++)
			dist[j][i] = -1;

		bfs(i);
	}

	int q;
	cin >> q;

	cout << "Case " << tc << ":\n";
	while (q--)
	{
		int op;
		cin >> op;

		if (op == 1)
		{
			int c, l, r;
			cin >> c >> l >> r;

			company[c].init();
			add(c, l, r);
		}
		else if (op == 2)
		{
			int c;
			cin >> c;

			company[c].init();
		}
		else
		{
			int u, m;
			cin >> u >> m;

			int ans = 1e9+10;

			for (int i = 1; i <= m; i++)
			{
				int c;
				cin >> c;

				for (auto b: company[c].block)
					ans = min(ans, dist[u][b]);

				if (company[c].range_1.ff != -1)
				{
					for (int v = company[c].range_1.ff; v <= company[c].range_1.ss; v++)
						ans = min(ans, dist_vert(u, v));
				}

				if (company[c].range_2.ff != -1)
				{
					for (int v = company[c].range_2.ff; v <= company[c].range_2.ss; v++)
						ans = min(ans, dist_vert(u, v));
				}
			}

			if (ans == 1e9+10) cout << "-1\n";
			else cout << ans << "\n";
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0);

	int tc;
	cin >> tc;

	for (int i = 1; i <= tc; i++) 
		solve(i);
}
