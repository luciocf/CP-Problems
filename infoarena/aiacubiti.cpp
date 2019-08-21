// infoarena - Aiacubiti
// Lúcio Cardoso

// Solution is the same as this one:
// https://github.com/zoooma13/Competitive-Programming/blob/master/aiacubiti.cpp

#include <bits/stdc++.h>

#pragma GCC optimize ("unroll-loops")

using namespace std;

const int maxn = 1e5+1;
const int maxv = 1048576;

int a[maxn];

int pre[1<<10];

int dp[5][maxv];

int main(void)
{
	freopen("aiacubiti.in", "r", stdin);
	freopen("aiacubiti.out", "w", stdout);

	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 0; i < (1<<10); i++)
		pre[i] = __builtin_popcount(i);

	long long ans = 0;

	for (int i = 1; i <= n; i++)
	{
		int A = (a[i]>>10), B = (a[i] ^ (A<<10));

		for (int mask = 0; mask < (1<<10); mask++)
			if (pre[B^mask] <= 4)
				ans += 1ll*dp[4-pre[B^mask]][(A<<10) | mask];

		for (int mask = 0; mask < (1<<10); mask++)
			if (pre[A^mask] <= 4)
				dp[pre[A^mask]][(mask<<10) | B]++;
	}

	printf("%lld\n", ans);
}
