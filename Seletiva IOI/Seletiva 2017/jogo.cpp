// Seletiva IOI 2017 - Jogo
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;

const int maxn = 3e3+10;
const ll inf = 1e18+10;

struct Pt
{
	int x, y, val;
} pt[maxn];

bool comp(Pt a, Pt b)
{
	return a.x < b.x;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d %d %d", &pt[i].x, &pt[i].y, &pt[i].val);

	ll ans = -inf;

	sort(pt+1, pt+n+1, comp);

	for (int p = 1; p <= n; p++)
	{
		unordered_map<double, ll> mp;

		for (int i = 1; i <= n; i++)
		{
			if (pt[i].x < pt[p].x || i == p) continue;

			double a1 = pt[p].x-pt[i].x;
			double a2 = pt[p].y-pt[i].y;

			if (a2 == 0.00) mp[inf] += 1ll*pt[i].val;
			else mp[a1/a2] += 1ll*pt[i].val;

			if (i < n && pt[i+1].x == pt[i].x && pt[i+1].y == pt[i].y)
				continue;

			if (a2 == 0.00) ans = max(ans, mp[inf] + 1ll*pt[p].val);
			else ans = max(ans, mp[a1/a2] + 1ll*pt[p].val);
		}
	}

	printf("%lld\n", ans);
}
