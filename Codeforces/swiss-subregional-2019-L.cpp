// ICPC Swiss Subregional 2019 - L - Tree Queries
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 1e9+7;

int fat[61];

int soma[31];

int choose[31][31];

int pot(int a, int b)
{
	if (!b) return 1;

	int t = pot(a, b/2);

	if (b%2) return (1ll*a*((1ll*t*t)%mod))%mod;

	return (1ll*t*t)%mod;
}

void calc(void)
{
	for (int i = 0; i <= 30; i++)
		for (int j = 0; j <= i; j++)
			choose[i][j] = (1ll*fat[i]*pot((1ll*fat[j]*fat[i-j])%mod, mod-2))%mod;
}

void upd(ll l, ll r, ll a, ll b, int depth, int L, int v)
{
	if (l > b || r < a) return;
	if (l >= a && r <= b)
	{
		int d = 30-depth;

		for (int x = 0; x <= d; x++)
			soma[L+x] = (soma[L+x] + (1ll*v*choose[d][x])%mod)%mod;

		return;
	}

	ll mid = (l+r)/2ll;

	upd(l, mid, a, b, depth+1, L+1, v); upd(mid+1, r, a, b, depth+1, L, v);
}

int main(void)
{
	int q;
	scanf("%d", &q);

	fat[0] = 1;
	for (int i = 1; i <= 30; i++)
		fat[i] = (1ll*i*fat[i-1])%mod;

	calc();

	while (q--)
	{
		int op;
		scanf("%d", &op);

		if (op == 0)
		{
			ll l, r;
			int x;

			scanf("%lld %lld %d", &l, &r, &x);

			--r;

			upd(0, (1ll<<30ll)-1, l, r, 0, 0, x);
		}
		else
		{
			int l, r;
			scanf("%d %d", &l, &r);

			--r;

			int ans = 0;
			for (int i = l; i <= r; i++)
				ans = (ans + soma[i])%mod;

			printf("%d\n", ans);
		}
	}
}
