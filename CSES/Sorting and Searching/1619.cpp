// CSES 1619 - Restaurant Customers
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 4e5+10;

int a[maxn], b[maxn];

int in[maxn], out[maxn];

void compress(int n)
{
	map<int, int> mp;

	for (int i = 1; i <= n; i++)
		mp[a[i]] = mp[b[i]] = 0;

	int aux = 0;
	for (auto &x: mp)
		x.second = ++aux;

	for (int i = 1; i <= n; i++)
		a[i] = mp[a[i]], b[i] = mp[b[i]];
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &a[i], &b[i]);

	compress(n);

	for (int i = 1; i <= n; i++)
		in[a[i]]++, out[b[i]]++;

	int ans = 0, at = 0;

	for (int i = 1; i <= 2*n; i++)
	{
		at += in[i];

		ans = max(ans, at);

		at -= out[i];
	}

	printf("%d\n", ans);
}
