// Codeforces 627C - Package Delivery
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 2e5+10;

int r[maxn];
pii a[maxn];

int main(void)
{
	int d, n, m;
	scanf("%d %d %d", &d, &n, &m);

	for (int i = 1; i <= m; i++)
		scanf("%d %d", &a[i].ff, &a[i].ss);
	a[++m] = {d, 0};

	sort(a+1, a+m+1);

	stack<pii> stk;

	for (int i = m; i >= 0; i--)
	{
		while (!stk.empty() && stk.top().ff > a[i].ss)
			stk.pop();

		if (stk.size()) r[i] = stk.top().ss;
		else r[i] = m+1;

		stk.push({a[i].ss, i});
	}

	int cap = n;
	ll ans = 0;

	for (int at = 0; at < m; at++)
	{
		if (a[at+1].ff-a[at].ff > n)
		{
			printf("-1\n");
			return 0;
		}

		int opt = r[at];

		if (opt == m+1 || a[opt].ff-a[at].ff > n)
		{
			int k = min(d-a[at].ff, n);

			if (cap < k)
				ans += 1ll*(k-cap)*a[at].ss;

			cap = k;
		}
		else
		{
			int k = a[opt].ff-a[at].ff;

			if (cap < k)
				ans += 1ll*(k-cap)*a[at].ss;

			cap = max(k, cap);
		}

		cap -= (a[at+1].ff-a[at].ff);
	}

	printf("%lld\n", ans);
}
