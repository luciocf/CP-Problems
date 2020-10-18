// Codeforces 1428E - Carrots for Rabbits
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 1e5+10;

int a[maxn];

ll f(int l, int p)
{
	int x = l/p;

	if (l%p == 0) return 1ll*x*x*p;

	return 1ll*x*x*(p - l%p) + 1ll*(x + 1)*(x + 1)*(l%p);
}

int main(void)
{
	int n, k;
	scanf("%d %d", &n, &k);

	priority_queue<pair<ll, pii>> pq;

	ll ans = 0;

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);

		ans += f(a[i], 1);

		pq.push({f(a[i], 1) - f(a[i], 2), {a[i], 2}});
	}	

	k = k-n;

	while (k--)
	{
		auto pp = pq.top(); pq.pop();

		ans -= 1ll*pp.ff;

		int l = pp.ss.ff, p = pp.ss.ss;

		if (p < l)
			pq.push({f(l, p) - f(l, p+1), {l, p+1}});
	}

	printf("%lld\n", ans);
}
