// Codeforces 877F - Ann and Books
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 3e5+10;
const int bucket = 320;

struct Query
{
	int l, r, bloco, id;
} qry[maxn];

int n, k;

int a[maxn], t[maxn];

ll pref[maxn];
int need_l[maxn], need_r[maxn];

int fq_l[maxn], fq_r[maxn];
ll ans[maxn], tot;

bool comp(Query a, Query b)
{
	if (a.bloco == b.bloco) return a.r < b.r;
	return a.bloco < b.bloco;
}

void compress(void)
{
	map<ll, int> mp;

	for (int i = 0; i <= n; i++)
	{
		mp[pref[i]] = 0;
		mp[pref[i]+1ll*k] = 0;
		mp[pref[i]-1ll*k] = 0;
	}

	int aux = 0;

	for (auto &x: mp)
		x.second = ++aux;

	for (int i = 0; i <= n; i++)
	{
		need_l[mp[pref[i]]] = mp[pref[i]+1ll*k];
		need_r[mp[pref[i]]] = mp[pref[i]-1ll*k];

		pref[i] = mp[pref[i]];
	}
}

void add(int i, int q)
{
	fq_l[pref[i-1]]++;
	fq_r[pref[i]]++;

	if (q == 0) tot += 1ll*fq_r[need_l[pref[i-1]]];
	else tot += 1ll*fq_l[need_r[pref[i]]];
}

void rem(int i, int q)
{
	if (q == 0) tot -= 1ll*fq_r[need_l[pref[i-1]]];
	else tot -= 1ll*fq_l[need_r[pref[i]]];

	fq_l[pref[i-1]]--;
	fq_r[pref[i]]--;
}

int main(void)
{
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
		scanf("%d", &t[i]);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		pref[i] = pref[i-1];

		if (t[i] == 1) pref[i] += 1ll*a[i];
		else pref[i] -= 1ll*a[i];
	}

	compress();

	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++)
	{
		scanf("%d %d", &qry[i].l, &qry[i].r);

		qry[i].id = i, qry[i].bloco = qry[i].l/bucket;
	}

	sort(qry+1, qry+q+1, comp);

	int l = 1, r = 1;
	tot = (pref[1] == need_l[pref[0]] ? 1 : 0);

	fq_r[pref[1]]++, fq_l[pref[0]]++;

	for (int i = 1; i <= q; i++)
	{
		while (r > qry[i].r) rem(r--, 1);
		while (r < qry[i].r) add(++r, 1);

		while (l > qry[i].l) add(--l, 0);
		while (l < qry[i].l) rem(l++, 0);

		ans[qry[i].id] = tot;
	}

	for (int i = 1; i <= q; i++)
		printf("%lld\n", ans[i]);
}
