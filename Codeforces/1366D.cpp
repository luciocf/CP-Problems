// Codeforces 1366D - Two Divisors
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5+10;
const int maxv = 1e7+10;

int spf[maxv];

int ans1[maxn], ans2[maxn];

void sieve(void)
{
	for (int i = 1; i < maxv; i++)
		spf[i] = i;

	for (int i = 2; i < maxv; i++)
		if (spf[i] == i)
			for (int j = 2*i; j < maxv; j += i)
				if (spf[j] == j)
					spf[j] = i;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	sieve();

	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);

		vector<int> p;

		while (x > 1)
		{
			if (p.size() == 0 || p.back() != spf[x])
				p.push_back(spf[x]);

			x /= spf[x];
		}

		if (p.size() == 1) ans1[i] = ans2[i] = -1;
		else
		{
			ans1[i] = p[0], ans2[i] = 1;

			for (auto v: p)
				ans2[i] *= v;
			ans2[i] /= p[0];
		}
	}

	for (int i = 1; i <= n; i++)
		printf("%d ", ans1[i]);
	printf("\n");
	for (int i = 1; i <= n; i++)
		printf("%d ", ans2[i]);
	printf("\n");
}
