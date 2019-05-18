// JOI Final Round 2018 - Stove
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int a[maxn], d[maxn];

int main(void)
{
	int n, k;
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 2; i <= n; i++)
		d[i-1] = a[i]-a[i-1];

	sort(d+1, d+n);

	int ans = k;
	for (int i = 1; i <= n-k; i++)
		ans += d[i];

	printf("%d\n", ans);
}
