// Codeforces 1st Marathon - Yan and Leo - H - Max and Min
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6+10;

int a[maxn];

int ans[maxn];

int main(void)
{
	int n, q;
	scanf("%d %d", &n, &q);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		ans[a[i]]++;
	}

	for (int i = 2; i <= n; i++)
		if (a[i] == a[i-1])
			ans[a[i]]--;

	while (q--)
	{
		int op;
		scanf("%d", &op);

		if (op == 1)
		{
			int p, c;
			scanf("%d %d", &p, &c);

			if (a[p] == c) continue;

			if (a[p-1] == a[p] && a[p+1] == a[p]) ans[a[p]]++;
			else if (a[p-1] != a[p] && a[p+1] != a[p]) ans[a[p]]--;

			a[p] = c;

			if (a[p-1] == a[p] && a[p+1] == a[p]) ans[a[p]]--;
			else if (a[p-1] != a[p] && a[p+1] != a[p]) ans[a[p]]++;
		}
		else
		{
			int c;
			scanf("%d", &c);

			printf("%d\n", ans[c]);
		}
	}
}
