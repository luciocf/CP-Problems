// 2017 Chinese Multi-University Training, BeihangU Contest - I - I Curse Myself
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;


const ll mod = (1LL<<32);
const int maxn = 2e3+10;

vector<pii> grafo[maxn];

int pai[maxn], nivel[maxn], edge[maxn];
bool mark[maxn];

int M, K;
int delta[maxn];
vector<int> V[maxn];
vector<ll> ans;

void get_cycle(int u, int v, int w)
{
	V[++M].push_back(w);

	while (u != v)
	{
		V[M].push_back(edge[u]);
		u = pai[u];
	}
}

void dfs(int u, int p)
{
	mark[u] = 1;

	for (auto pp: grafo[u])
	{
		int v = pp.ff, w = pp.ss;

		if (mark[v])
		{
			if (v != p && nivel[u] > nivel[v]) get_cycle(u, v, w);
			continue;
		}

		pai[v] = u, nivel[v] = nivel[u]+1, edge[v] = w;

		dfs(v, u);
	}
}

bool comp(int a, int b) {return delta[a] < delta[b];}

void solve(void)
{
	ll soma = 0;
	vector<int> ind;

	for (int i = 1; i <= M; i++)
	{
		ind.push_back(i);

		sort(V[i].begin(), V[i].end(), greater<int>());

		soma += 1ll*V[i][0];
		delta[i] = -(V[i][1]-V[i][0]);
	}

	sort(ind.begin(), ind.end(), comp);

	ans.push_back(soma);

	priority_queue<pair<ll, pii>> pq;
	if (ind.size()) pq.push({soma - delta[ind[0]], {0, 1}});

	while (ans.size() < K)
	{
		auto pp = pq.top(); pq.pop();

		ll s = pp.ff;
		int i = pp.ss.ff, j = pp.ss.ss;

		ans.push_back(s);

		if (j < V[ind[i]].size()-1)
			pq.push({s + 1ll*V[ind[i]][j+1] - 1ll*V[ind[i]][j], {i, j+1}});

		if (i < M-1)
			pq.push({s - 1ll*delta[ind[i+1]], {i+1, 1}});

		if (i < M-1 && j == 1)
			pq.push({s + 1ll*delta[ind[i]] - 1ll*delta[ind[i+1]], {i+1, 1}});
	}
}

int main(void)
{
	int n, m;
	int tt = 0;

	while (cin >> n >> m)
	{
		ll S = 0;
		M = 0;
		ans.clear();

		for (int i = 1; i <= n; i++)
			grafo[i].clear(), mark[i] = 0;
		for (int i = 1; i <= m; i++)
			V[i].clear();

		for (int i = 1; i <= m; i++)
		{
			int u, v, w;
			cin >> u >> v >> w;

			grafo[u].push_back({v, w});
			grafo[v].push_back({u, w});

			S += 1ll*w;
		}

		dfs(1, 0);

		scanf("%d", &K);

		int prod = 1;
		for (int i = 1; i <= M; i++)
		{
			if (1ll*prod*V[i].size() > K)
			{
				prod = K;
				break;
			}
			prod *= V[i].size();
		}

		K = min(K, prod);

		solve();

		ll resp = 0;

		for (int i = 0; i < K; i++)
			resp = (resp + 1ll*(i+1)*(S-ans[i]))%mod;

		cout << "Case #" << ++tt << ": " << resp << "\n";
	}
}
