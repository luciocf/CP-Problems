// Codeforces 1342D - Multiple Testcases
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

int a[maxn];
int c[maxn];

vector<int> ans[maxn];

int main(void)
{
	int n, k;
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i <= k; i++)
		scanf("%d", &c[i]);

	sort(a+1, a+n+1);

	int m = 0;
	for (int i = 1; i <= n; i++)
		m = max(m, (n-i+1 + (c[a[i]]-1))/c[a[i]]);

	int ind = 1;

	for (int i = 1; i <= n; i++)
	{
		if (ind == m+1) ind = 1;

		ans[ind++].push_back(a[i]);
	}

	printf("%d\n", m);
	for (int i = 1; i <= m; i++)
	{
		printf("%d ", ans[i].size());
		for (auto x: ans[i])
			printf("%d ", x);
		printf("\n");
	}
}
