// Codeforces 195E - Building Forest
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;
const int mod = 1e9+7;

int n;
int ans;

int pai[maxn], depth[maxn];

void init(void)
{
	for (int i = 1; i <= n; i++)
		pai[i] = i;
}

int Find(int x)
{
	if (pai[x] == x) return x;

	int P = Find(pai[x]);

	depth[x] = (depth[x] + depth[pai[x]])%mod;
	return pai[x] = P;
}

void Join(int x, int y, int w)
{
	int ant = y;
	x = Find(x), y = Find(y);

	int D = depth[ant];

	pai[y] = x, depth[y] = ((w+mod)%mod + D)%mod;

	ans = (ans+depth[y])%mod;
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
