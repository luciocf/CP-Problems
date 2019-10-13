// USACO 2016/2017 - Why Did the Cow Cross the Road
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int n;
int a[maxn], b[maxn], c[maxn];
int pos[maxn];

int bit[maxn];

void upd(int x, int v)
{
	for (; x < maxn; x += (x&-x))
		bit[x] += v;
}

long long soma(int x)
{
	long long ans = 0;

	for (; x > 0; x -= (x&-x))
		ans += 1ll*bit[x];

	return ans;
}

long long try1(void)
{
	for (int i = 1; i <= n; i++)
		pos[a[i]] = i;

	for (int i = 1; i <= n; i++)
		c[i] = pos[b[i]];

	long long at = 0;

	for (int i = n; i >= 1; i--)
	{
		at += soma(c[i]-1);
		upd(c[i], 1);
	}

	long long ans = at;

	for (int i = 1; i <= n; i++)
	{
		at -= (1ll*c[i]-1ll);
		at += (1ll*n-1ll*c[i]);

		ans = min(ans, at);
	}

	return ans;
}

long long try2(void)
{
	for (int i = 1; i <= n; i++)
		pos[b[i]] = i;

	for (int i = 1; i <= n; i++)
		c[i] = pos[a[i]];

	long long at = 0;

	for (int i = n; i >= 1; i--)
	{
		at += soma(c[i]-1);
		upd(c[i], 1);
	}

	long long ans = at;

	for (int i = 1; i <= n; i++)
	{
		at -= (1ll*c[i]-1ll);
		at += (1ll*n-1ll*c[i]);

		ans = min(ans, at);
	}

	return ans;
}

int main(void)
{
	freopen("mincross.in", "r", stdin);
	freopen("mincross.out", "w", stdout);

	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i <= n; i++)
		scanf("%d", &b[i]);

	long long ans = try1();

	memset(bit, 0, sizeof bit);

	ans = min(ans, try2());
	
	printf("%lld\n", ans);
}
