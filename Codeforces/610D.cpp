// Codeforces 610D - Vika and Segments
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 3e5+10;

struct Vertical
{
	int x, y1, y2;
};

struct Horizontal
{
	int y, x1, x2;
};

struct Event
{
	int t, x, ind;
};

struct FenwickTree
{
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

	int get(int l, int r)
	{
		return soma(r) - soma(l-1);
	}
} BIT;

vector<Vertical> all_v, good_v;
vector<Horizontal> all_h, good_h;

bool comp1(Vertical a, Vertical b)
{
	if (a.x == b.x) return a.y1 < b.y1;
	return a.x < b.x;
}

bool comp2(Horizontal a, Horizontal b)
{
	if (a.y == b.y) return a.x1 < b.x1;
	return a.y < b.y;
}

bool comp3(Event a, Event b)
{
	if (a.x == b.x) return a.t < b.t;
	return a.x < b.x;
}

void compress(void)
{
	map<int, int> mp;

	for (auto v: good_v)
		mp[v.y1] = 0, mp[v.y2] = 0;
	for (auto h: good_h)
		mp[h.y] = 0;

	int aux = 0;
	for (auto &x: mp)
		x.second = ++aux;

	for (auto &v: good_v)
		v.y1 = mp[v.y1], v.y2 = mp[v.y2];
	for (auto &h: good_h)
		h.y = mp[h.y];
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

		if (x1 == x2) all_v.push_back({x1, min(y1, y2), max(y1, y2)});
		else all_h.push_back({y1, min(x1, x2), max(x1, x2)});
	}

	sort(all_v.begin(), all_v.end(), comp1);
	sort(all_h.begin(), all_h.end(), comp2);

	ll ans = 0;

	for (int i = 0; i < all_v.size(); i++)
	{
		Vertical at = all_v[i];

		int j;
		for (j = i+1; j < all_v.size() && all_v[j].x == all_v[i].x; j++)
		{
			Vertical novo = all_v[j];

			if (novo.y2 <= at.y2) continue;

			if (novo.y1 > at.y2)
			{
				good_v.push_back(at);
				at = novo;
			}
			else at.y2 = novo.y2;
		}

		good_v.push_back(at);
		i = j-1;
	}

	for (int i = 0; i < all_h.size(); i++)
	{
		Horizontal at = all_h[i];

		int j;
		for (j = i+1; j < all_h.size() && all_h[j].y == all_h[i].y; j++)
		{
			Horizontal novo = all_h[j];

			if (novo.x2 <= at.x2) continue;

			if (novo.x1 > at.x2)
			{
				good_h.push_back(at);
				at = novo;
			}
			else at.x2 = novo.x2;
		}

		good_h.push_back(at);
		i = j-1;
	}

	for (auto v: good_v)
		ans += 1ll*(v.y2-v.y1+1);

	for (auto h: good_h)
		ans += 1ll*(h.x2-h.x1+1);

	compress();

	vector<Event> event;

	for (int i = 0; i < good_v.size(); i++)
		event.push_back({1, good_v[i].x, i});

	for (int i = 0; i < good_h.size(); i++)
	{
		event.push_back({0, good_h[i].x1, i});
		event.push_back({2, good_h[i].x2, i});
	}

	sort(event.begin(), event.end(), comp3);

	for (auto e: event)
	{
		if (e.t == 0) BIT.upd(good_h[e.ind].y, 1);
		else if (e.t == 1) ans -= 1ll*BIT.get(good_v[e.ind].y1, good_v[e.ind].y2);
		else BIT.upd(good_h[e.ind].y, -1);
	}

	printf("%lld\n", ans);
}
