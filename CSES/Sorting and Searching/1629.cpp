// CSES 1629 - Movie Festival
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 4e5+10;

int a[maxn], b[maxn];

int dp[maxn];

vector<int> in[maxn];

void compress(int n)
{
	map<int, int> mp;

	for (int i = 1; i <= n; i++)
		mp[a[i]] = mp[b[i]] = 0;

	int aux = 0;
	for (auto &x: mp)
		x.second = ++aux;

	for (int i = 1; i <= n; i++)
		a[i] = mp[a[i]], b[i] = mp[b[i]];
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &a[i], &b[i]);

	compress(n);

	for (int i = 1; i <= n; i++)
		in[b[i]].push_back(a[i]);

	for (int i = 1; i <= 2*n; i++)
	{
		dp[i] = dp[i-1];

		for (int pos: in[i])
			dp[i] = max(dp[i], 1 + dp[pos]);
	}

	printf("%d\n", dp[2*n]);
}
