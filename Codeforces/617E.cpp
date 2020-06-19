// Codeforces 617E - XOR and Favorite Number
// Lúcio Cardoso

// Same solution as in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;
const int maxv = 2e6+10;
const int block = 320;

struct Query
{
	int l, r, bloco, id;
} qry[maxn];

int n, m, k;
ll tot;

int pref[maxn];
ll ans[maxn];

int freq_l[maxv], freq_r[maxv];

bool comp(Query a, Query b)
{
	if (a.bloco == b.bloco) return a.r < b.r;
	return a.bloco < b.bloco;
}

void add(int i, bool q)
{
	freq_r[pref[i]]++;
	freq_l[pref[i-1]]++;

	if (q == 0)
		tot += 1ll*freq_r[pref[i-1]^k];
	else
		tot += 1ll*freq_l[pref[i]^k];
}

void rem(int i, int q)
{
	if (q == 0)
		tot -= 1ll*freq_r[pref[i-1]^k];
	else
		tot -= 1ll*freq_l[pref[i]^k];

	freq_r[pref[i]]--;
	freq_l[pref[i-1]]--;
}

int main(void)
{
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);

		pref[i] = pref[i-1]^x;
	}

	for (int i = 1; i <= m; i++)
	{
		int l, r;
		scanf("%d %d", &l, &r);

		qry[i] = {l, r, l/block, i};
	}

	sort(qry+1, qry+m+1, comp);

	int l = 1, r = 1;
	tot = (pref[1] == k ? 1 : 0);
	freq_l[0] = 1, freq_r[pref[1]] = 1;

	for (int i = 1; i <= m; i++)
	{
		while (r < qry[i].r) add(++r, 1);
		while (r > qry[i].r) rem(r--, 1);

		while (l < qry[i].l) rem(l++, 0);
		while (l > qry[i].l) add(--l, 0);

		ans[qry[i].id] = tot;
	}

	for (int i = 1; i <= m; i++)
		printf("%lld\n", ans[i]);
}
