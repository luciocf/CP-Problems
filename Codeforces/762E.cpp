// Codeforces 762E - Radio Stations
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 3e5+10;
const int maxf = 1e4+10;

struct Pt
{
	int x, l, r, f;
} pt[maxn];

int n;

int entra[maxn];
vector<int> sai[maxn];

unordered_map<int, int> bit[maxf];

void compress(void)
{
	map<int, int> mp;

	for (int i = 1; i <= n; i++)
		mp[pt[i].x] = mp[pt[i].l] = mp[pt[i].r] = 0;

	int aux = 0;
	for (auto &x: mp)
		x.second = ++aux;

	for (int i = 1; i <= n; i++)
	{
		pt[i].x = mp[pt[i].x];
		pt[i].l = mp[pt[i].l];
		pt[i].r = mp[pt[i].r];

		entra[pt[i].x] = i;
		sai[pt[i].r].push_back(i);
	}
}

void upd(int x, int v, int k)
{
	for (; x < maxn; x += (x&-x))
		bit[k][x] += v;
}

int soma(int x, int k)
{
	int ans = 0;
	for (; x > 0; x -= (x&-x))
		if (bit[k].find(x) != bit[k].end())
			ans += bit[k][x];

	return ans;
}

int main(void)
{
	int k;
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
	{
		int r;
		scanf("%d %d %d", &pt[i].x, &r, &pt[i].f);

		pt[i].l = pt[i].x-r, pt[i].r = pt[i].x+r;
	}

	compress();

	ll ans = 0;

	for (int i = 1; i < maxn; i++)
	{
		int j = entra[i];

		if (j)
		{
			for (int f = max(1, pt[j].f-k); f <= min(maxf-1, pt[j].f+k); f++)
				ans += 1ll*(soma(pt[j].x, f) - soma(pt[j].l-1, f));

			upd(pt[j].x, 1, pt[j].f);
		}

		for (auto j: sai[i])
			upd(pt[j].x, -1, pt[j].f);
	}

	printf("%lld\n", ans);
}
