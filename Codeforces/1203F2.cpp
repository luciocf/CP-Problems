// Codeforces 1203F2 - Complete the Projects (hard version)
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 110;
const int maxr = 6e4+10;
const int inf = 1e9+10;

pii a[maxn];
int dp[maxn][maxr];

bool comp(pii x, pii y) {return x.ff+x.ss > y.ff+y.ss;}

int main(void)
{
	int n, r;
	scanf("%d %d", &n, &r);

	vector<pii> pos, neg;

	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d", &a[i].ff, &a[i].ss);

		if (a[i].ss >= 0) pos.push_back(a[i]);
		else neg.push_back(a[i]);
	}

	sort(pos.begin(), pos.end());
	sort(neg.begin(), neg.end(), comp);

	int k = 0;

	for (auto pp: pos)
	{
		if (r >= pp.ff)
		{
			++k;
			r += pp.ss;
		}
	}

	for (int i = 0; i <= neg.size(); i++)
		for (int j = 0; j < maxr; j++)
			dp[i][j] = -inf;

	dp[0][r] = k;

	for (int i = 0; i < neg.size(); i++)
	{
		for (int j = 0; j < maxr; j++)
		{
			dp[i+1][j] = max(dp[i+1][j], dp[i][j]);

			if (j+neg[i].ss >= 0 && j >= neg[i].ff)
				dp[i+1][j+neg[i].ss] = max(dp[i+1][j+neg[i].ss], dp[i][j]+1);
		}
	}

	int mx = 0;
	for (int i = 0; i < maxr; i++)
		mx = max(mx, dp[(int)neg.size()][i]);

	printf("%d\n", mx);
}
