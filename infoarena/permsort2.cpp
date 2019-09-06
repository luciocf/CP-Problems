// infoarena - Permsort2
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int pos[maxn], a[maxn];

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

int main(void)
{
	freopen("permsort2.in", "r", stdin);
	freopen("permsort2.out", "w", stdout);

	int n, posn;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		if (a[i] == n) posn = i;

		if (i != n)
			upd(i, 1);
	}

	for (int i = 1; i < posn; i++)
		pos[a[i]] = i;
	for (int i = posn; i <= n; i++)
		pos[a[i]] = n-i+posn; 

	vector<int> ans;

	if (posn != n)
		ans.push_back(posn);

	for (int i = n-1; i >= 1; i--)
	{
		int p = soma(pos[i]);

		upd(pos[i], -1);

		if (p+1 != n) ans.push_back(p+1);
		if (p != n) ans.push_back(p);
	}

	if (n > 1) ans.push_back(1);

	printf("%d\n", ans.size());
	for (auto x: ans)
		printf("S %d\n", x);
}
