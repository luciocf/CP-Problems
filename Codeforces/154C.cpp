// Codeforces 154C - Double Profiles
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e6+10;
const int mod = 100003621;
const int mod2 = 1e8+7;

int P = 1007359;
int pot[maxn];
int h[2][maxn];

vector<int> grafo[maxn];

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	pot[0] = 1;
	for (int i = 1; i <= m; i++)
		pot[i] = (1ll*pot[i-1]*P)%mod;

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	for (int i = 1; i <= n; i++)
		sort(grafo[i].begin(), grafo[i].end());

	ll ans = 0;

	ans = (1ll*ans*(ans-1)/2ll);

	map<pair<int, int>, int> mp;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < grafo[i].size(); j++)
		{
			h[0][i] = (1ll*h[0][i] + 1ll*pot[j]*grafo[i][j])%mod;
			h[1][i] = (1ll*h[1][i] + 1ll*pot[j]*grafo[i][j])%mod2;
		}

		mp[{h[0][i], h[1][i]}]++;
	}

	for (auto pp: mp)
		ans += 1ll*pp.second*(pp.second-1)/2ll;

	for (int i = 1; i <= n; i++)
	{
		grafo[i].push_back(i);
		sort(grafo[i].begin(), grafo[i].end());
	}

	mp.clear();

	for (int i = 1; i <= n; i++)
	{
		h[0][i] = h[1][i] = 0;

		for (int j = 0; j < grafo[i].size(); j++)
		{
			h[0][i] = (1ll*h[0][i] + 1ll*pot[j]*grafo[i][j])%mod;
			h[1][i] = (1ll*h[1][i] + 1ll*pot[j]*grafo[i][j])%mod2;
		}

		mp[{h[0][i], h[1][i]}]++;
	}

	for (auto pp: mp)
		ans += 1ll*pp.second*(pp.second-1)/2ll;

	printf("%lld\n", ans);
}
