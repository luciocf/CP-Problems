// CSES 1706 - School Excursion
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int n;
int pai[maxn], peso[maxn];

bitset<maxn> dp;

void init(int n)
{
	for (int i = 1; i <= n; i++)
		pai[i] = i, peso[i] = 1;
}

int Find(int x)
{
	if (pai[x] == x) return x;
	return pai[x] = Find(pai[x]);
}

void Join(int x, int y)
{
	x = Find(x), y = Find(y);
	if (x == y) return;

	if (peso[x] < peso[y]) swap(x, y);

	pai[y] = x, peso[x] += peso[y];
}

int main(void)
{
	int m;
	scanf("%d %d", &n, &m);

	init(n);

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		Join(u, v);
	}

	vector<int> v;

	for (int i = 1; i <= n; i++)
		if (Find(i) == i)
			v.push_back(peso[i]);

	dp[0] = 1;
	for (auto c: v)
		dp |= (dp<<c);

	for (int i = 1; i <= n; i++)
	{
		if (dp[i]) printf("1");
		else printf("0");
	}
	printf("\n");
}
