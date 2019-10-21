// infoarena - Desc
// Lúcio Cardoso

#include <bits/stdc++.h>

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

using namespace std;

typedef long long ll;

ll n;
int k, aux = -1;

int dp[4001][4001];

map<ll, int> ord;

ll dd[7000];

void get(void)
{
	for (int i = 1; 1ll*i*i <= n; i++)
	{
		if (n%i) continue;

		dd[++aux] = i;
		if (n/i != i) dd[++aux] = n/i;
	}

	++aux;

	sort(dd, dd+aux);

	for (int i = 0; i < aux; i++)
		ord[dd[i]] = i;
}

int solve(int a, int b)
{
	if (a == aux && b != 0) return 0;
	if (b == 0) return 1;
	if (dp[a][b] != -1) return dp[a][b];

	int ans = solve(a+1, b);

	if (dd[b]%dd[a] == 0)
		ans += solve(a, ord[dd[b]/dd[a]]);

	return dp[a][b] = ans;
}

int main(void)
{
	freopen("desc.in", "r", stdin);
	freopen("desc.out", "w", stdout);

	scanf("%lld %d", &n, &k);

	get();

	for (int i = 1; i < aux; i++)
		dp[i][0] = 1;

	for (int a = aux-1; a >= 1; a--)
	{
		for (int b = 1; b < aux; b++)
		{
			dp[a][b] = dp[a+1][b];

			if (dd[b]%dd[a] == 0)
				dp[a][b] += dp[a][ord[dd[b]/dd[a]]];
		}
	}

	printf("%d\n", dp[1][aux-1]);

	ll prod = 1;
	int ant = 1;

	while (prod != n)
	{
		for (int i = ant; i < aux; i++)
		{
			if (prod*dd[i] > n || (n%(prod*dd[i]) != 0)) continue;

			int x = dp[i][ord[n/(prod*dd[i])]];

			if (x >= k)
			{
				printf("%lld ", dd[i]);
				prod *= dd[i];
				ant = i;
				break;
			}
			else k -= x;
		}
	}

	printf("\n");
}
