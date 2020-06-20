// Codeforces 903D - Almost Difference
// Lúcio Cardoso

// Solution is the same as in editorial

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

	map<int, int> fq;

	long double ans = 0.00;
	long long pref = 0;

	for (int i = n; i >= 1; i--)
	{
		ans += pref;
		ans -= (long double)(1ll*a[i]*(n-i));
		ans += fq[a[i]-1];
		ans -= fq[a[i]+1];

		fq[a[i]]++, pref += 1ll*a[i];
	}

	if (ans < 0)
	{
		ans = -ans;
		printf("-");
	}

	printf("%llu\n", (unsigned long long) ans);
}
