// CSES 1090 - Ferris Wheel
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

int a[maxn];

int main(void)
{
	int n, x;
	scanf("%d %d", &n, &x);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	sort(a+1, a+n+1);

	int ans = 0;
	int l = 1, r = n;

	while (l <= r)
	{
		if (l != r && a[l]+a[r] <= x)
			ans++, l++, r--;
		else
			ans++, r--;
	} 

	printf("%d\n", ans); 
}
