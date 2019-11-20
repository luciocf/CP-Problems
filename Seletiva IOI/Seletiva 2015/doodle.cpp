// Seletiva IOI 2015 - Doodle
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 3e5+10;

struct Line
{
	bool tipo;
	int mn, mx, pt;
} line[maxn];

struct Event
{
	int tipo;
	int ind;
};

vector<Event> event[maxn];

int n, k;

ll bit[maxn];

void upd(int x, ll v)
{
	for (; x < maxn; x += (x&-x))
		bit[x] += v;
}

ll soma(int x)
{
	ll ans = 0;
	for (; x > 0; x -= (x&-x))
		ans += bit[x];
	return ans;
}

bool comp(Event a, Event b)
{
	return (a.tipo < b.tipo);
}

ll Qtd(int ind)
{
	memset(bit, 0, sizeof bit);

	for (int i = 1; i < maxn; i++)
		event[i].clear();

	ll inter = 0;

	for (int i = 1; i <= ind; i++)
	{
		if (line[i].tipo == 0)
			event[line[i].pt].push_back({2, i});
		else
		{
			event[line[i].mn].push_back({0, i});
			event[line[i].mx+1].push_back({1, i});
		}
	}

	for (int i = 1; i < maxn; i++)
	{
		sort(event[i].begin(), event[i].end(), comp);

		for (auto E: event[i])
		{
			if (E.tipo == 0) upd(line[E.ind].pt, 1);
			else if (E.tipo == 1) upd(line[E.ind].pt, -1);
			else inter += (soma(line[E.ind].mx)-soma(line[E.ind].mn-1));
		}
	}

	if (ind == n) return (inter-1ll*n);
	return (inter-1ll*(ind-1));
}

int busca(void)
{	
	int ini = 1, fim = n, ans = n;

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;

		if (Qtd(mid) > 1ll*k) ans = mid, fim = mid-1;
		else ini = mid+1;
	}

	return ans;
}

int main(void)
{
	scanf("%d %d", &n, &k);

	bool tipo = 0;
	int x = 0, y = 0;

	map<int, int> mp_x, mp_y;

	for (int i = 1; i <= n; i++)
	{
		int delta;
		scanf("%d", &delta);

		if (tipo == 0)
		{
			mp_x[x] = 0;

			int mn = min(x, x+delta), mx = max(x, x+delta);
			x += delta;

			line[i] = {0, mn, mx, y};
		}
		else
		{
			mp_y[y] = 0;

			int mn = min(y, y+delta), mx = max(y, y+delta);
			y += delta;

			line[i] = {1, mn, mx, x};
		}

		tipo = !tipo;
	}

	mp_x[x] = 0, mp_y[y] = 0;

	int aux = 0;
	for (auto &ptr: mp_x)
		ptr.second = ++aux;

	aux = 0;
	for (auto &ptr: mp_y)
		ptr.second = ++aux;

	for (int i = 1; i <= n; i++)
	{
		if (line[i].tipo == 0)
			line[i] = {0, mp_x[line[i].mn], mp_x[line[i].mx], mp_y[line[i].pt]};
		else
			line[i] = {1, mp_y[line[i].mn], mp_y[line[i].mx], mp_x[line[i].pt]};
	}

	int ans = busca();

	printf("%d %lld\n", ans, Qtd(ans));
}
