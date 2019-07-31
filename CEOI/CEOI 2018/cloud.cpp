// CEOI 2018 - Cloud Computing
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 2e3+10;
const int maxc = 51;
const ll inf = 2e18+10;

struct Obj
{
	int c, f, v;
} a[maxn], b[maxn];

int n, m;

ll dp[2][maxn][2*maxc];

void upd(ll &a, ll b)
{
	a = max(a, b);
}

bool comp(Obj a, Obj b)
{
	return a.f > b.f;
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d %d %d", &a[i].c, &a[i].f, &a[i].v);

	scanf("%d", &m);

	for (int i = 1; i <= m; i++)
		scanf("%d %d %d", &b[i].c, &b[i].f, &b[i].v);

	sort(a+1, a+n+1, comp);
	sort(b+1, b+m+1, comp);

	for (int i = n; i >= 0; i--)
	{
		int at = i%2, pre = (i+1)%2;

		for (int j = m; j >= 1; j--)
		{
			for (int c = 2*maxc-1; c >= 0; c--)
			{
				if (a[i+1].f < b[j].f && c > 0 && c < b[j].c)
				{
					upd(dp[at][j][c], dp[at][j+1][c]);
					continue;
				}

				upd(dp[at][j][c], dp[pre][j][c]);
				upd(dp[at][j][c], dp[at][j+1][c]);

				if (c >= b[j].c)
					upd(dp[at][j][c], 1ll*b[j].v + dp[at][j+1][c-b[j].c]);

				if (i < n && c < maxc && a[i+1].f >= b[j].f)
					upd(dp[at][j][c], dp[pre][j][c+a[i+1].c] - 1ll*a[i+1].v);

			}
		}
	}

	printf("%lld\n", max(0ll, dp[0][1][0]));
}
