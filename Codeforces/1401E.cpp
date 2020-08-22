// Codeforces 1401E - Divide Square
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e6+10;

struct FenwickTree
{
	int bit[maxn];

	void upd(int x, int v)
	{
		for (; x < maxn; x += (x&-x))
			bit[x] += v;
	}

	int soma(int x)
	{
		int ans = 0;
		for (; x > 0; x -= (x&-x))
			ans += bit[x];
		return ans;
	}

	int get(int l, int r)
	{
		return soma(r)-soma(l-1);
	}
} BIT;

struct Event
{
	int x, l, r;
	int tipo;
} event[maxn];

bool comp(Event a, Event b)
{
	if (a.x == b.x) return a.tipo < b.tipo;
	return a.x < b.x;
}

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	int aux = 0;
	ll ans = 1;

	for (int i = 1; i <= n; i++)
	{
		int y, l, r;
		scanf("%d %d %d", &y, &l, &r);

		event[++aux] = {l, y, y, 0};
		event[++aux] = {r, y, y, 2};

		if (l <= 0 && r >= 1000000) ans++;
	}

	for (int i = 1; i <= m; i++)
	{
		int x, l, r;
		scanf("%d %d %d", &x, &l, &r);

		event[++aux] = {x, l, r, 1};

		if (l <= 0 && r >= 1000000) ans++;
	}

	sort(event+1, event+aux+1, comp);

	for (int i = 1; i <= aux; i++)
	{
		auto e = event[i];

		if (e.tipo == 0) BIT.upd(e.l, 1);
		else if (e.tipo == 2) BIT.upd(e.l, -1);
		else ans += 1ll*BIT.get(e.l, e.r);
	}

	printf("%lld\n", ans);
}
