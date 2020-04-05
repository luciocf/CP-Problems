// USACO 2012/2013 - Cow Lineup
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int n, k;
int a[maxn];

int fq[maxn];

int main(void)
{
	freopen("lineup.in", "r", stdin); freopen("lineup.out", "w", stdout);

	scanf("%d %d", &n, &k);

	map<int, int> mp;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		mp[a[i]] = 0;
	}

	int aux = 0;
	for (auto &x: mp)
		x.second = ++aux;

	for (int i = 1; i <= n; i++)
		a[i] = mp[a[i]];

	int ans = 1, r = 1, tot = 1;
	fq[a[1]]++;

	for (int l = 1; l <= n; l++)
	{
		while (r < n && tot + (fq[a[r+1]] == 0) <= k+1)
			r++, tot += (fq[a[r+1]] == 0), fq[a[r]]++;
		
		ans = max(ans, fq[a[l]]);

		fq[a[l]]--;
		if (fq[a[l]] == 0) tot--;
	}

	printf("%d\n", ans);
}
