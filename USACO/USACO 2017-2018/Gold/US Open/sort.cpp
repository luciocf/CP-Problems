// USACO Gold US Open 2018 - Out of Sorts
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int n;
int a[maxn], b[maxn];

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

void compress(void)
{
	map<int, int> mp;

	for (int i = 1; i <= n; i++)
		mp[a[i]] = 0;

	int ind = 0;
	for (auto &x: mp)
		x.second = ++ind;

	for (int i = 1; i <= n; i++)
		a[i] = mp[a[i]], b[i] = mp[b[i]];
}

int main(void)
{
	freopen("sort.in", "r", stdin); freopen("sort.out", "w", stdout);

	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		b[i] = a[i];
	}

	compress();

	sort(b+1, b+n+1);

	int ans = 1;
	for (int i = 1; i < n; i++)
	{
		upd(a[i], 1);
		ans = max(ans, i-soma(b[i]));
	}

	printf("%d\n", ans);
}
