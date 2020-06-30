// NWERC 2017 - F - Factor-Free Tree
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6+10;
const int maxv = 1e7+10;

int a[maxn];

int ind_l[maxn], ind_r[maxn];

int last[maxv];

int spf[maxv];

int pai[maxn];

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

bool valid(int k, int l, int r)
{
	return (ind_l[k] < l && ind_r[k] > r);
}

int solve(int l, int r)
{
	if (l > r) return 1;

	for (int ptr_l = l, ptr_r = r; ptr_l <= ptr_r; ptr_l++, ptr_r--)
	{
		if (valid(ptr_l, l, r))
		{
			int f1 = solve(l, ptr_l-1);
			int f2 = solve(ptr_l+1, r);

			if (!f1 || !f2) return 0;

			if (l <= ptr_l-1) pai[f1] = ptr_l;
			if (ptr_l+1 <= r) pai[f2] = ptr_l;
			
			return ptr_l;
		}

		if (valid(ptr_r, l, r))
		{
			int f1 = solve(l, ptr_r-1);
			int f2 = solve(ptr_r+1, r);

			if (!f1 || !f2) return 0;

			if (l <= ptr_r-1) pai[f1] = ptr_r;
			if (ptr_r+1 <= r) pai[f2] = ptr_r;

			return ptr_r;
		}
	}

	return 0;
}

int main(void)
{
	sieve();

	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i <= n; i++)
	{
		int x = a[i];
		vector<int> prime;

		while (x > 1)
		{
			int p = spf[x];

			if (last[p])
				ind_l[i] = max(ind_l[i], last[p]);

			prime.push_back(p);
			x /= p;
		}

		for (auto p: prime)
			last[p] = i;
	}

	memset(last, 0, sizeof last);

	for (int i = n; i >= 1; i--)
	{
		ind_r[i] = n+1;

		int x = a[i];
		vector<int> prime;

		while (x > 1)
		{
			int p = spf[x];

			if (last[p])
				ind_r[i] = min(ind_r[i], last[p]);

			prime.push_back(p);
			x /= p;
		}

		for (auto p: prime)
			last[p] = i;
	}


	int ans = solve(1, n);

	if (!ans) printf("impossible\n");
	else
	{
		for (int i = 1; i <= n; i++)
			printf("%d ", pai[i]);
		printf("\n");
	}
}
