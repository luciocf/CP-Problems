// IOI 2019 - Arranging Shoes
// Lúcio Cardoso

#include <bits/stdc++.h>
#include "shoes.h"

using namespace std;

typedef long long ll;

const int maxn = 2e5+10;

int a[maxn];

vector<int> pos_esq[maxn], pos_dir[maxn];

int bit[maxn];

void upd(int x, int v)
{
	for (; x < maxn; x += (x&-x))
		bit[x] += v;
}

int soma(int x)
{
	int ans = 0;
	for (; x > 0; x -= (x&-x))
		ans += bit[x];
	return ans;
}

ll count_swaps(vector<int> s)
{
	int n = (int)s.size();

	for (int i = 1; i <= n; i++)
	{
		a[i] = s[i-1];
		upd(i, 1);
	}

	for (int i = n; i >= 1; i--)
	{
		if (a[i] < 0) pos_esq[-a[i]].push_back(i);
		else pos_dir[a[i]].push_back(i);
	}

	ll ans = 0;

	for (int i = 1; i <= n; i++)
	{
		if (a[i] < 0)
		{
			a[i] = -a[i];

			if (pos_esq[a[i]].back() != i)
				continue;

			int dir = pos_dir[a[i]].back();

			ans += 1ll*(soma(dir)-soma(i)-1);

			pos_esq[a[i]].pop_back(); pos_dir[a[i]].pop_back();

			upd(dir, -1); upd(i, -1);
		}
		else
		{
			if (pos_dir[a[i]].back() != i)
				continue;

			int esq = pos_esq[a[i]].back();

			ans += 1ll*(soma(esq)-soma(i));

			pos_dir[a[i]].pop_back(); pos_esq[a[i]].pop_back();

			upd(i, -1); upd(esq, -1);
		}
	}

	return ans;
}
