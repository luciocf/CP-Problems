// Codeforces 1373F - Network Coverage
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e6+10;

int n;
int a[maxn], b[maxn], c[maxn];

bool ok(int x)
{
	c[1] = x;

	int it = 1;

	for (int i = 2; i < 2*n; i += 2)
	{
		c[i] = b[it]-c[i-1];

		++it;

		c[i+1] = max(0, a[it]-c[i]);
	}

	c[2*n] = b[it]-c[2*n-1];

	return (c[1]+c[2*n] >= a[1]);
}

int busca(void)
{
	int ini = 0, fim = b[1], ans = -1;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		if (ok(mid)) ans = mid, fim = mid-1;
		else ini = mid+1; 
	}

	return ans;
}

int main(void)
{
	int t;
	scanf("%d", &t);

	while (t--)
	{
		scanf("%d", &n);

		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		for (int i = 1; i <= n; i++)
			scanf("%d", &b[i]);

		int ans = busca();

		if (ans == -1)
		{
			printf("NO\n");
			continue;
		}

		ok(ans);

		bool ok = (c[2*n] >= 0 && c[1] >= 0 && c[2*n]+c[1] >= a[1]);

		for (int i = 1; i < n; i++)
			if (c[2*i] < 0 || c[2*i+1] < 0 || c[2*i]+c[2*i+1] < a[i+1])
				ok = false;

		if (!ok) printf("NO\n");
		else printf("YES\n");
	}
}
