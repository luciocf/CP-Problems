// 2020-2021 ACM-ICPC, Asia Seoul Regional Contest - I - Stock Analysis
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 2e3+10;
const int maxm = 2e5+10;
const ll inf = 1e18;

int n;
int a[maxn];

struct BIT2D
{
	ll bit[maxn][maxn];

	void upd(int x, int y, ll v)
	{
		for (int i = x; i < maxn; i += (i&-i))
			for (int j = y; j < maxn; j += (j&-j))
				bit[i][j] = max(bit[i][j], v);
	}

	ll get(int x, int y)
	{
		ll ans = -inf;

		for (int i = x; i > 0; i -= (i&-i))
			for (int j = y; j > 0; j -= (j&-j))
				ans = max(ans, bit[i][j]);

		return ans;
	}
} BIT;

struct Query
{
	int l, r, ind;
	ll u;

	bool operator<(const Query &o) const
	{
		return u < o.u;
	}
} query[maxm];

struct Range
{
	int l, r;
	ll soma;

	bool operator<(const Range &o) const
	{
		return soma < o.soma;
	}
};

ll ans[maxm];

vector<Range> V;

int main(void)
{
	int m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i < maxn; i++)
		for (int j = 1; j < maxn; j++)
			BIT.bit[i][j] = -inf;

	for (int l = 1; l <= n; l++)
	{
		ll soma = 0;

		for (int r = l; r <= n; r++)
		{
			soma += 1ll*a[r];
			V.push_back({l, r, soma});
		}
	}

	for (int i = 1; i <= m; i++)
	{
		scanf("%d %d %lld", &query[i].l, &query[i].r, &query[i].u);
		query[i].ind = i;
	}

	sort(query+1, query+m+1);
	sort(V.begin(), V.end());

	int ptr = 0;

	for (int i = 1; i <= m; i++)
	{
		while (ptr < V.size() && V[ptr].soma <= query[i].u)
		{
			BIT.upd(n-V[ptr].l+1, V[ptr].r, V[ptr].soma);
			ptr++;
		}

		ans[query[i].ind] = BIT.get(n-query[i].l+1, query[i].r);
	}

	for (int i = 1; i <= m; i++)
	{
		if (ans[i] == -inf) printf("NONE\n");
		else printf("%lld\n", ans[i]);
	}
}
