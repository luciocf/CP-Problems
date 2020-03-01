// Codeforces 1282C - Petya and Exam
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e5+10;

pii v[maxn];

int main(void)
{
	int tc;
	scanf("%d", &tc);

	while (tc--)
	{
		int n, T, a, b;
		scanf("%d %d %d %d", &n, &T, &a, &b);

		int qtd_a = 0, qtd_b = 0;

		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &v[i].ss);

			if (v[i].ss == 0) qtd_a++;
			else qtd_b++; 
		}

		for (int i = 1; i <= n; i++)
			scanf("%d", &v[i].ff);

		sort(v+1, v+n+1);

		int ans = 0, tot = 0;
		int q1 = 0, q2 = 0;

		for (int i = 1; i <= n; i++)
		{
			int lim = v[i].ff-1;

			if (tot > T) break;

			if (tot > lim)
			{
				if (v[i].ss == 0)
					q1++, tot += a;
				else
					q2++, tot += b;

				continue;
			}

			int aux = i-1;

			int r = lim-tot;

			int r_a = qtd_a-q1;
			int r_b = qtd_b-q2;

			if (r/a > r_a)
			{
				aux += r_a;
				r -= r_a*a;

				aux += r/b;
			}
			else aux += r/a;

			ans = max(ans, aux);

			if (v[i].ss == 0)
				q1++, tot += a;
			else
				q2++, tot += b;
		}

		if (tot <= T) ans = n;

		printf("%d\n", ans);
	}
}
