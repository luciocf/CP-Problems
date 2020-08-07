// Codeforces 547C - Mike and Foam
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 5e5+10;

int a[maxn];
int spf[maxn];

int fq[maxn];

bool mark[maxn];

vector<int> D[maxn];

void sieve(void)
{
	for (int i = 1; i < maxn; i++)
		spf[i] = i;

	for (int i = 2; i < maxn; i++)
		if (spf[i] == i)
			for (int j = 2*i; j < maxn; j += i)
				if (spf[j] == j)
					spf[j] = i;
}

int get(int x)
{
	vector<int> p;

	while (x > 1)
	{
		int v = spf[x];

		if (p.size() == 0 || p.back() != v)
			p.push_back(v);

		x /= v;
	}

	int ans = 0;

	for (int mask = 1; mask < (1<<p.size()); mask++)
	{
		int prod = 1;
		int qtd = 0;

		for (int i = 0; i < p.size(); i++)
		{
			if (mask&(1<<i))
			{
				prod *= p[i];
				++qtd;
			}
		}

		if (qtd%2) ans += fq[prod];
		else ans -= fq[prod];
	}

	return ans;
}

int main(void)
{
	sieve();

	int n, q;
	scanf("%d %d", &n, &q);

	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);

		a[i] = x;

		for (int j = 1; j*j <= x; j++)
		{
			if (x%j) continue;

			D[i].push_back(j);
			if (x/j != j) D[i].push_back(x/j);
		}
	}

	int sz = 0;
	ll ans = 0;

	while (q--)
	{
		int i;
		scanf("%d", &i);

		int tot = sz-get(a[i]);
		if (a[i] == 1 && mark[i]) --tot;

		int sign = 1;
		if (mark[i]) sign = -1;
		
		ans += 1ll*sign*tot;
		for (auto d: D[i])
			fq[d] += sign;

		sz += sign;
		mark[i] = !mark[i];

		printf("%lld\n", ans);
	}
}
