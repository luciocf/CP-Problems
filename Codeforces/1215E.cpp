// Codeforces 1215E - Marbles
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 4e5+10;
const ll inf = 1e18+10;

int n;
int a[maxn];

vector<int> pos[maxn];

ll qtd[22][22];
ll dp[1<<21];

void calc(int a, int b)
{
	if (pos[a].size() == 0 || pos[b].size() == 0) return;

	int j = 0;

	for (int i = 0; i < pos[b].size(); i++)
	{
		while (j < (int)pos[a].size()-1 && pos[a][j] < pos[b][i])
			j++;

		if (pos[a][j] < pos[b][i]) return;

		qtd[a][b] += 1ll*((int)pos[a].size()-j);
	}
}

ll solve(int mask)
{
	if (mask == (1<<20)-1) return 0;
	if (dp[mask] != -1) return dp[mask];

	ll ans = inf;

	for (int i = 0; i < 20; i++)
	{
		ll tot = 0;

		if (!(mask&(1<<i)))
		{
			for (int j = 0; j < 20; j++)
				if (mask&(1<<j))
					tot += qtd[j+1][i+1];

			ans = min(ans, tot + solve(mask|(1<<i)));
		}
	}

	return dp[mask] = ans;
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		pos[a[i]].push_back(i);
	}

	for (int i = 1; i <= 20; i++)
	{
		for (int j = i+1; j <= 20; j++)
		{
			calc(i, j);
			calc(j, i);
		}
	}

	memset(dp, -1, sizeof dp);
	printf("%lld\n", solve(0));
}
