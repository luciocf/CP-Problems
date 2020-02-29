// Codeforces 1282B2 - K for the Price of One (Hard Version)
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

int n, p, k;
int a[maxn];

map<int, int> soma[maxn];

int main(void)
{
	int t;
	scanf("%d", &t);

	while (t--)
	{
		scanf("%d %d %d", &n, &p, &k);

		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);

		sort(a+1, a+n+1);

		int ans = 0, pref = 0;

		for (int i = 0; i < k; i++)
		{
			pref += a[i];
			if (pref > p) break;

			int tot = i, soma = pref;

			for (int j = i+k; j <= n; j += k)
			{
				if (soma+a[j] > p) break;

				tot += k, soma += a[j];
			}

			ans = max(ans, tot);
		}

		printf("%d\n", ans);
	}
}
