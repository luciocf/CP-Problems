// CSES 1084 - Apartments
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

int a[maxn], b[maxn];

int main(void)
{
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i <= m; i++)
		scanf("%d", &b[i]);

	sort(a+1, a+n+1); sort(b+1, b+m+1);

	int ans = 0, ptr = 1;

	for (int i = 1; i <= n; i++)
	{
		while (ptr <= m && b[ptr] < a[i]-k)
			ptr++;

		if (ptr == m+1) break;

		if (b[ptr] <= a[i]+k) ans++, ptr++;
	}

	printf("%d\n", ans); 
}
