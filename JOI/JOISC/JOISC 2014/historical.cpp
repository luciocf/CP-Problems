// JOISC 2014 - Historical Research
// Lúcio Figueiredo

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;
const int sq = 320;

int n;
int a[maxn], b[maxn];

int fq[maxn][sq], fq_aux[maxn];
ll best[sq][sq];

int soma(int l, int r, int v)
{
	if (l == 0) return fq[v][r];
	return fq[v][r] - fq[v][l-1];
}

int main(void)
{
	int q;
	scanf("%d %d", &n, &q);

	map<int, int> mp;

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		mp[a[i]] = 0;
	}

	int aux = 0;
	for (auto &x: mp)
		x.second = ++aux;

	for (int i = 1; i <= n; i++)
		b[i] = mp[a[i]];

	for (int i = 0; i*sq <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			fq[b[j]][i] = fq[b[j]][max(0, i-1)];

		for (int j = max(1, i*sq); j <= min(n, (i+1)*sq-1); j++)
			fq[b[j]][i]++;
	}

	for (int i = 0; i*sq <= n; i++)
	{
		for (int j = i; j*sq <= n; j++)
		{
			best[i][j] = best[i][max(0, j-1)];

			for (int k = max(1, j*sq); k <= min(n, (j+1)*sq-1); k++)
			{
				fq_aux[b[k]]++;

				best[i][j] = max(best[i][j], 1ll*a[k]*fq_aux[b[k]]);
			}
		}

		for (int j = 1; j <= n; j++)
			fq_aux[b[j]] = 0;
	}

	while (q--)
	{
		int l, r;
		scanf("%d %d", &l, &r);

		int b_l = l/sq, b_r = r/sq;
		ll ans = 0;

		if (b_l == b_r)
		{
			for (int i = l; i <= r; i++)
			{
				fq_aux[b[i]]++;

				ans = max(ans, 1ll*a[i]*fq_aux[b[i]]);
			}

			printf("%lld\n", ans);

			for (int i = l; i <= r; i++)
				fq_aux[b[i]] = 0;

			continue;
		}

		if (b_l < b_r-1) ans = best[b_l+1][b_r-1];

		for (int i = l; i <= (b_l+1)*sq-1; i++)
			fq_aux[b[i]]++;

		for (int i = b_r*sq; i <= r; i++)
			fq_aux[b[i]]++;

		for (int i = l; i <= (b_l+1)*sq-1; i++)
			ans = max(ans, 1ll*a[i]*(fq_aux[b[i]] + (b_l < b_r-1 ? soma(b_l+1, b_r-1, b[i]) : 0)));

		for (int i = b_r*sq; i <= r; i++)
			ans = max(ans, 1ll*a[i]*(fq_aux[b[i]] + (b_l < b_r-1 ? soma(b_l+1, b_r-1, b[i]) : 0)));

		printf("%lld\n", ans);

		for (int i = l; i <= (b_l+1)*sq-1; i++)
			fq_aux[b[i]]--;

		for (int i = b_r*sq; i <= r; i++)
			fq_aux[b[i]]--;
	}
}
