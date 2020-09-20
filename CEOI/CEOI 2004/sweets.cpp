// CEOI 2004 - Sweets
// Lúcio Cardoso

// Solution is the same as in: https://github.com/MetalBall887/Competitive-Programming/blob/master/Olympiad/CEOI/CEOI%2004-Sweets.cpp

// Very similar to CF 451E - Devu and Flowers

#include <bits/stdc++.h>

using namespace std;

const int maxn = 11;
const int mod = 2004;

int n;
int a[maxn];

int choose(int a, int b)
{
	if (a < b) return 0;
	if (a == 0) return 1;
	if (b == 0) return 1;

	vector<int> primo, num;

	for (int i = a; i > a-b; i--)
		num.push_back(i);

	for (int i = 1; i <= b; i++)
	{
		int x = i;

		for (int j = 2; j*j <= x; j++)
		{
			while (x%j == 0)
			{
				primo.push_back(j);
				x /= j;
			}
		}

		if (x > 1) primo.push_back(x);
	}

	for (auto p: primo)
	{
		for (auto &x: num)
		{
			if (x%p == 0)
			{
				x /= p;
				break;
			}
		}
	}

	int ans = 1;
	for (auto x: num)
		ans = (1ll*ans*x)%mod;

	return ans;
}

int main(void)
{
	int l, r;
	scanf("%d %d %d", &n, &l, &r);

	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);

	int ans = 0;

	for (int mask = 0; mask < (1<<n); mask++)
	{
		int c_l, c_r;
		int sz = __builtin_popcount(mask);

		int soma = l-1;

		for (int i = 0; i < n; i++)
			if (mask&(1<<i))
				soma -= (a[i]+1);

		if (soma < 0) c_l = 0;
		else c_l = choose(soma+n, n);

		soma = r;

		for (int i = 0; i < n; i++)
			if (mask&(1<<i))
				soma -= (a[i]+1);

		if (soma < 0) c_r = 0;
		else c_r = choose(soma+n, n);

		if (sz&1) ans = (ans - (c_r-c_l+mod) + mod)%mod;
		else ans = (ans + (c_r-c_l+mod))%mod;
	}

	printf("%d\n", ans);
}
