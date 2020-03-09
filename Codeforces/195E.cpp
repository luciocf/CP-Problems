// Codeforces 195E - Building Forest
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;
const int mod = 1e9+7;

int n;
int ans;

int pai[maxn], depth[maxn], edge[maxn];

void init(void)
{
	for (int i = 1; i <= n; i++)
		pai[i] = i;
}

pii Find(int x)
{
	if (pai[x] == x) return {x, 0};

	pii P = Find(pai[x]);

	depth[x] = (P.second + (edge[x]+mod)%mod)%mod;
	pai[x] = P.first, edge[x] = depth[x];

	return {pai[x], depth[x]};
}

void Join(int x, int y, int w)
{
	pii p1 = Find(x), p2 = Find(y);
	x = p1.first, y = p2.first;

	pai[y] = x, edge[y] = ((w+mod)%mod + p2.second)%mod; 

	ans = (ans+((edge[y]+mod)%mod))%mod;
}

int main(void)
{
	scanf("%d", &n);

	init();

	for (int i = 1; i <= n; i++)
	{
		int m;
		scanf("%d", &m);

		for (int j = 1; j <= m; j++)
		{
			int u, w;
			scanf("%d %d", &u, &w);

			Join(i, u, w);
		}
	}

	printf("%d\n", ans);
}
