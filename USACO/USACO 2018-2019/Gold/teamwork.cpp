// USACO 2018-2019 - Teamwork
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e4+10;

int n, k;
int a[maxn];

int dp[maxn];

int main(void)
{
	FILE *fin = fopen("teamwork.in", "r");
	FILE *fout = fopen("teamwork.out", "w");

	fscanf(fin, "%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
		fscanf(fin, "%d", &a[i]);

	for (int i = 1; i <= n; i++)
	{
		int mx = a[i];

		for (int j = i; j >= max(1, i-k+1); j--)
		{
			mx = max(mx, a[j]);

			dp[i] = max(dp[i], mx*(i-j+1) + dp[j-1]);
		}
	}

	fprintf(fout, "%d\n", dp[n]);
}
