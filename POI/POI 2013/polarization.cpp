// POI 2013 - Polarization
// Lúcio Cardoso

// Solution uses the same main idea as in: https://github.com/stefdasca/CompetitiveProgramming/blob/master/POI/POI%2013-Polarization.cpp.

// However, my code solves the bounded knapsack part in O(N * sqrt(N)), removing the log factor. The approach is explained in
// Algorithms Live, in this link: https://www.youtube.com/watch?v=U4O3SwDamA4&t=2953s

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 3e5+10;

int n;

int sub[maxn], pai[maxn], nivel[maxn];
ll calc[maxn];

int cnt_window[maxn];

bool dp[maxn], ant[maxn];

vector<int> grafo[maxn];

void dfs_sub(int u, int p)
{
	sub[u] = 1;

	for (auto v: grafo[u])
	{
		if (v != p)
		{
			nivel[v] = nivel[u]+1;
			pai[v] = u;

			dfs_sub(v, u);

			sub[u] += sub[v];
		}
	}
}

void dfs_calc(int u, int p)
{
	for (auto v: grafo[u])
	{
		if (v != p)
		{
			calc[v] = calc[u] + 1ll*n - 2ll*sub[v];
			dfs_calc(v, u);
		}
	}
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	dfs_sub(1, 0);

	for (int i = 1; i <= n; i++)
		calc[1] += 1ll*nivel[i];

	dfs_calc(1, 0);

	ll ans = 0;

	for (int u = 1; u <= n; u++)
	{
		int mx = n-sub[u];
		for (auto v: grafo[u])
			if (v != pai[u])
				mx = max(mx, sub[v]);

		if (mx > n/2)
		{
			int s1 = mx;
			int s2 = n-mx-1;

			ans = max(ans, calc[u]+1ll*s1*s2);
			continue;
		}

		map<int, int> fq;
		vector<pii> num;

		fq[n-sub[u]]++;
		for (auto v: grafo[u])
			if (v != pai[u])
				fq[sub[v]]++;

		for (auto x: fq)
			num.push_back({x.ff, x.ss});

		memset(dp, 0, sizeof dp); memset(ant, 0, sizeof ant);
		dp[0] = 1, ant[0] = 1;

		for (auto pp: num)
		{
			for (int i = 0; i <= n; i++)
				cnt_window[i] = 0;

			int v = pp.ff, k = pp.ss;
			if (!v) continue;

			for (int i = 0; i <= n; i++)
			{
				int md = i%v;

				dp[i] |= (cnt_window[md] > 0);

				if (i-v*k >= 0 && ant[i-v*k]) cnt_window[md]--;
				if (ant[i]) cnt_window[md]++;
			}

			for (int i = 0; i <= n; i++)
				ant[i] = dp[i];
		}

		mx = 0;
		for (int i = 1; i <= (n-1)/2; i++)
			if (dp[i])
				mx = i;

		ans = max(ans, calc[u] + 1ll*mx*(n-1-mx));
	}

	printf("%d %lld\n", n-1, ans);
}
