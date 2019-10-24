// BOI 2011 - Plagiarism
// Lúcio Cardoso

// wtf?

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int a[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	sort(a+1, a+n+1);

	int l = 1;
	long long ans = 0;

	for (int r = 1; r <= n; r++)
	{
		while (l < r && 10*a[l] < 9*a[r])
			l++;

		if (l != r)
			ans += 1ll*(r-l);
	}

	printf("%lld\n", ans);
}
