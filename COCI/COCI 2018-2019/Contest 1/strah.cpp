// COCI 2018/2019 - Strah
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

const int maxn = 2e3+10;

typedef pair<int, int> pii;
typedef long long ll;

int n, m;
char tab[maxn][maxn];

int h[maxn][maxn];

int l[maxn], r[maxn];

ll S[maxn];

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf(" %c", &tab[i][j]);

	for (int i = 1; i <= max(n, m); i++)
		S[i] = S[i-1] + (1ll*i*(i+1))/2ll;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (tab[i][j] == '#') h[i][j] = 0;
			else h[i][j] = h[i-1][j]+1;
		}
	}

	ll ans = 0;

	for (int i = 1; i <= n; i++)
	{
		stack<pii> stk;

		for (int j = 1; j <= m; j++)
		{
			while (stk.size() && stk.top().ff >= h[i][j])
				stk.pop();

			if (stk.size()) l[j] = stk.top().ss+1;
			else l[j] = 1;

			stk.push({h[i][j], j});
		}

		while (stk.size()) stk.pop();

		for (int j = m; j >= 1; j--)
		{
			while (stk.size() && stk.top().ff > h[i][j])
				stk.pop();

			if (stk.size()) r[j] = stk.top().ss-1;
			else r[j] = m;

			stk.push({h[i][j], j});
		}

		for (int j = 1; j <= m; j++)
		{
			int a = j-l[j], b = r[j]-j;
			int tot = r[j]-l[j]+1;

			ans += (1ll*h[i][j]*(1ll*h[i][j]+1ll)/2ll)*(S[tot] - S[a] - S[b]);
		}
	}

	printf("%lld\n", ans);
}
