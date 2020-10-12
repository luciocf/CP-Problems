// CSES 1621 - Distinct Numbers
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

int a[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	sort(a+1, a+n+1);

	int ans = 1;
	for (int i = 2; i <= n; i++)
		if (a[i] != a[i-1])
			ans++;

	printf("%d\n", ans);
}
