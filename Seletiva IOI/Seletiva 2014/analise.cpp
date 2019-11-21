// Seletiva IOI 2014 - Análise de Risco
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;

int n, L, R;

int a[maxn];

int tab[maxn][20];

int lg[maxn];

void build(void)
{
	for (int i = 1; i <= n; i++)
		tab[i][0] = a[i];

	lg[1] = 0;
	for (int i = 2; i < maxn; i++)
		lg[i] = lg[i/2]+1;

	for (int j = 1; j < 20; j++)
		for (int i = 1; i + (1<<j) - 1 <= n; i++)
			tab[i][j] = __gcd(tab[i][j-1], tab[i+(1<<(j-1))][j-1]);
}

int query(int l, int r)
{
	int j = lg[r-l+1];

	return __gcd(tab[l][j], tab[r-(1<<j)+1][j]);
}

int last(int i, int j, int g)
{
	int ini = j, fim = n, ans = i;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		if (query(i, mid) == g) ans = mid, ini = mid+1;
		else fim = mid-1;
	}

	return ans;
}

int main(void)
{
	scanf("%d %d %d", &n, &L, &R);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	build();

	ll ans = 0;

	int ptr = 1;

	for (int i = 1; i <= n; i++)
	{
		int ind = i, g = a[i];

		int tot = 0;

		while (g > L)
		{
			int ate = last(i, ind, g);
			tot++;

			if (g <= R)
			{
				ll a1 = R-g+1;
				ll a2 = ate-ind+1;

				ans += a1*a2;
			}

			if (ate == n) break;

			ind = ate+1;
			g = query(i, ind);
		}

		while (ptr < i || (ptr <= n && query(i, ptr) > L))
			ptr++;

		if (ptr <= n)
		{
			ll a1 = n-ptr+1;
			ll a2 = R-L+1;

			ans += a1*a2;
		}
	}

	printf("%lld\n", ans);
}
