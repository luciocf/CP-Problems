// COI 2008 - Kolekcija
// Lúcio Cardoso

// Solution: http://hsin.hr/coci/archive/2007_2008/

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 3e5+10;
const int inf = 1e9+10;

int x, n, k;
int prox[maxn];

int dp[maxn][2];

pii a[maxn];
pii ans[maxn];

int solve(int pos, int q)
{
	if (pos == n) return dp[pos][q] = 0;
	if (dp[pos][q] != -1) return dp[pos][q];

	if (!q)
	{
		if (prox[pos] == n+1) return dp[pos][q] = 0;

		int ans1 = k+solve(prox[pos], 0);

		int ans2 = min(k, a[prox[pos]].ff-(a[pos].ff+k-1))+solve(prox[pos], 1);

		return dp[pos][q] = min(ans1, ans2);
	}
	else
	{
		int ans1 = k+solve(pos+1, 0);

		int ans2 = min(k, a[pos+1].ff-a[pos].ff)+solve(pos+1, 1);

		return dp[pos][q] = min(ans1, ans2);
	}
}

int main(void)
{
	scanf("%d %d %d", &x, &k, &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i].ff);
		a[i].ss = i;
	}

	sort(a+1, a+n+1);

	int ptr = 2;
	for (int i = 1; i <= n; i++)
	{
		while (ptr < n && a[ptr].ff <= a[i].ff+k-1)
			ptr++;

		prox[i] = (a[ptr].ff > a[i].ff+k-1 ? ptr : n+1);
	}

	memset(dp, -1, sizeof dp);

	printf("%d\n", k+min(solve(1, 0), solve(1, 1)));

	int q = 0;

	ans[a[1].ss] = {a[1].ff, a[1].ff+k-1};

	for (int i = 2; i <= n; i++)
	{
		if (!q)
		{
			for (int j = i; j < prox[i-1]; j++)
				ans[a[j].ss] = ans[a[i-1].ss];

			int p = prox[i-1];
			if (p == n+1) break;
 
			if (dp[i-1][q] == k+dp[p][0])
			{
				ans[a[p].ss] = {a[p].ff, a[p].ff+k-1};
			}
			else
			{
				ans[a[p].ss] = {a[p].ff-k+1, a[p].ff};
				q = 1;
			}

			i = p;
		}
		else
		{
			if (dp[i-1][q] == k+dp[i][0])
			{
				ans[a[i].ss] = {a[i].ff, a[i].ff+k-1};
				q = 0;
			}
			else
			{
				ans[a[i].ss] = {a[i].ff-k+1, a[i].ff};
			}
		}
	}

	for (int i = 1; i <= n; i++)
	{
		if (ans[i].ss > x) printf("%d %d\n", x-k+1, x);
		else printf("%d %d\n", ans[i].ff, ans[i].ss);
	}
}
