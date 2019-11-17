// Seletiva IOI 2015 - Pedras
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;
const int bucket = 320;

struct Q
{
	int l, r, bloco, id;
} q[maxn];

int a[maxn];

int freq[maxn], qtd[maxn], ans[maxn];

bool comp(Q a, Q b)
{
	if (a.bloco == b.bloco) return a.r < b.r;
	return a.bloco < b.bloco;
}

void add(int i, int &mx)
{
	qtd[freq[a[i]]]--;

	++freq[a[i]];

	qtd[freq[a[i]]]++;

	mx = max(mx, freq[a[i]]);
}

void rem(int i, int &mx)
{
	qtd[freq[a[i]]]--;

	--freq[a[i]];

	qtd[freq[a[i]]]++;

	if (freq[a[i]]+1 == mx && qtd[freq[a[i]]+1] == 0)
		mx--;
}

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

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
		a[i] = mp[a[i]];

	for (int i = 1; i <= m; i++)
	{
		int l, r;
		scanf("%d %d", &l, &r);

		q[i] = {l, r, l/bucket, i};
	}

	sort(q+1, q+m+1, comp);

	int l = 1, r = 1, mx = 1;
	freq[a[1]]++, qtd[1]++;

	for (int i = 1; i <= m; i++)
	{
		while (r > q[i].r) rem(r--, mx);
		while (r < q[i].r) add(++r, mx);

		while (l > q[i].l) add(--l, mx);
		while (l < q[i].l) rem(l++, mx);

		ans[q[i].id] = mx;
	}

	for (int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
}
