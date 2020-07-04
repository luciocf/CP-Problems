// infoarena - sormin
// Lúcio Cardoso

// Solution is the same as in: https://github.com/zoooma13/Competitive-Programming/blob/master/sormin.cpp

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;
const int maxs = 5e4+10;

int a[maxn];
pii b[maxn];

pii dp[maxn];

int main(void)
{
	freopen("sormin.in", "r", stdin); freopen("sormin.out", "w", stdout);
	int n, s;
	scanf("%d %d", &n, &s);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	sort(a+1, a+n+1);

	int m = 0, qtd = 0;
	for (int i = 1; i <= n; i++)
	{
		++qtd;
		if (i != n && a[i] == a[i+1]) continue;

		int k = 0;
		while ((1<<(k+2))-1 <= qtd)
			++k;

		for (int j = 0; j <= k; j++)
			b[++m] = {a[i]*(1<<j), a[i]};

		b[++m] = {a[i]*(qtd - (1<<(k+1)) + 1), a[i]};

		qtd = 0;
	}

	int mask = 0;

	for (int i = 12; i >= 0; i--)
	{
		bitset<maxs> bs;
		bs[0] = 1;

		int mask2 = mask|(1<<i);

		for (int j = 1; j <= m; j++)
			if (!(b[j].ss&mask2))
				bs |= (bs<<b[j].ff);

		if (bs[s]) mask |= (1<<i);
	}

	memset(dp, -1, sizeof dp);
	dp[0] = {0, 0};

	for (int i = 1; i <= m; i++)
		if (!(b[i].ss&mask))
			for (int j = s; j >= b[i].ff; j--)
				if (dp[j].ff == -1 && dp[j-b[i].ff].ff != -1)
					dp[j] = b[i];

	vector<int> V;

	int at = s;
	while (at)
	{
		for (int i = 1; i <= dp[at].ff/dp[at].ss; i++)
			V.push_back(dp[at].ss);

		at -= dp[at].ff;
	}

	printf("%d %d\n", ((1<<13)-1)^mask, V.size());
	for (auto x: V)
		printf("%d ", x);
 	printf("\n");
}
