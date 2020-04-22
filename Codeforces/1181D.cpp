// Codeforces 1181D - Irrigation
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, int> pii;

const int maxn = 5e5+10;

int a[maxn];

int qtd[maxn];
int pref[maxn];
ll tot[maxn];

int bit[maxn];

int ans[maxn];

pii query[maxn];

vector<int> ind[maxn];

void upd(int x, int v)
{
	for (; x < maxn; x += (x&-x))
		bit[x] += v;
}

int kth(int x)
{
	int soma = 0, pos = 0;

	for (int i = 20; i >=0; i--)
		if (pos + (1<<i) < maxn && soma + bit[pos+(1<<i)] < x)
			soma += bit[pos+(1<<i)], pos += (1<<i);

	return pos+1;
}

int main(void)
{
	int n, m, q;
	scanf("%d %d %d", &n, &m, &q);

	for (int i = 1; i <= n; i++)
	{
		int c;
		scanf("%d", &c);

		a[c]++;
	}

	for (int i = 1; i <= m; i++)
	{
		ind[a[i]].push_back(i);
		qtd[a[i]]++;
	}

	pref[0] = tot[0] = qtd[0];
	for (int i = 1; i <= n; i++)
	{
		pref[i] = pref[i-1] + qtd[i];
		tot[i] = tot[i-1] + 1ll*pref[i];
	}

	for (int i = 1; i <= q; i++)
	{
		scanf("%lld", &query[i].first);

		query[i].first -= n, query[i].second = i;
	}

	sort(query+1, query+q+1);

	for (auto i: ind[0])
		upd(i, 1);

	int ptr = 0;
	for (int i = 1; i <= q; i++)
	{
		ll k = query[i].first;

		while (ptr < n && tot[ptr] < k)
		{
			++ptr;

			for (auto i: ind[ptr])
				upd(i, 1);
		}

		k -= tot[ptr-1];
		k %= m;

		if (k == 0) k = m;

		ans[query[i].second] = kth(k); 
	}

	for (int i = 1; i <= q; i++)
		printf("%d\n", ans[i]);
}
