// Codeforces 1156D - 0-1-Tree
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5+10;

int n;
int pai[2][maxn], peso[2][maxn];

void init(int q)
{
	for (int i = 1; i <= n; i++)
		pai[q][i] = i, peso[q][i] = 1;
}

int Find(int x, int q)
{
	if (pai[q][x] == x) return x;
	return pai[q][x] = Find(pai[q][x], q);
}

void Join(int x, int y, int q)
{
	x = Find(x, q), y = Find(y, q);
	if (x == y) return;

	if (peso[q][x] < peso[q][y]) swap(x, y);

	pai[q][y] = x, peso[q][x] += peso[q][y];
}

int main(void)
{
	scanf("%d", &n);

	init(0); init(1);

	for (int i = 1; i < n; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		Join(u, v, w);
	}

	long long ans = 0;

	for (int i = 1; i <= n; i++)
	{
		if (Find(i, 0) == i)
			ans += 1ll*peso[0][Find(i, 0)]*(peso[0][Find(i, 0)]-1);
		if (Find(i, 1) == i)
			ans += 1ll*peso[1][Find(i, 1)]*(peso[1][Find(i, 1)]-1);

		ans += 1ll*(peso[0][Find(i, 0)]-1)*(peso[1][Find(i, 1)]-1);
	}

	printf("%lld\n", ans);
}
