// Codeforces 1191F - Tokitsukaze and Strange Rectangle
// Lúcio Cardoso

#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 2e5+10;

int n;

pii pt[maxn];

ll bit[2][maxn];

void upd(int x, int v, int q)
{
	for (; x < maxn; x += (x&-x))
		bit[q][x] += 1ll*v;
}

ll soma(int x, int q)
{
	ll ans = 0;
	for (; x > 0; x -= (x&-x))
		ans += bit[q][x];
	return ans;
}

void compress(void)
{
	map<int, int> mp;

	for (int i = 1; i <= n; i++)
		mp[pt[i].y] = 0;

	int aux = 0;
	for (auto &x: mp)
		x.second = ++aux;

	for (int i = 1; i <= n; i++)
		pt[i].y = mp[pt[i].y];
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &pt[i].x, &pt[i].y);

	sort(pt+1, pt+n+1);

	compress();

	ll ans = 0;
	for (int i = 1; i <= n; i++)
	{
		int j;

		for (j = i; j <= n; j++)
			if (pt[j].x != pt[i].x)
				break;
		j--;

		upd(pt[j].y, 1, 0);

		for (j = i; j <= n; j++)
		{
			if (pt[j].x != pt[i].x)
				break;

			ll tot = soma(maxn-1, 0)-soma(pt[j].y-1, 0);

			upd(pt[j].y, tot-(soma(pt[j].y, 1)-soma(pt[j].y-1, 1)), 1);
		}

		j--;
		ans += soma(pt[j].y, 1);

		i = j;
	}

	printf("%lld\n", ans);
}
