// POI 2008 - Triangles
// Lúcio Cardoso

// Solution is the same as in: https://github.com/farmerboy95/CompetitiveProgramming/blob/master/POI/POI%2008-Triangles.cpp

#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;

typedef pair<int, int> pt;
typedef long long ll;

const int maxn = 3e3+10;

int n;
pt p[maxn];

ll cross(pt a, pt b)
{
	return 1ll*a.x*b.y - 1ll*a.y*b.x;
}

ll dist(pt a)
{
	return 1ll*a.x*a.x + 1ll*a.y*a.y;
}

bool comp(pt a, pt b)
{
	if (a.y >= 0 && b.y < 0) return true;
	if (a.y < 0 && b.y >= 0) return false;

	if (a.y == 0 && b.y == 0)
	{
		if (a.x >= 0 && b.x < 0) return true;
		if (a.x < 0 && b.x >= 0) return false;

		return dist(a) < dist(b);
	}

	if (cross(a, b) == 0) return dist(a) < dist(b);
	return cross(a, b) > 0;
}

ll Soma(int i, int j, vector<ll> &v)
{
	if (i <= j)
	{
		ll ans = v[j];
		if (i != 0) ans -= v[i-1];

		return ans;
	}

	return Soma(i, v.size()-1, v) + Soma(0, j, v);
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		scanf("%d %d", &p[i].x, &p[i].y);

	ll ans = 0;

	for (int r = 0; r < n; r++)
	{
		vector<pt> V;

		for (int i = 0; i < n; i++)
			if (i != r)
				V.push_back({p[i].x - p[r].x, p[i].y - p[r].y});

		int sz = V.size();

		sort(V.begin(), V.end(), comp);

		vector<ll> soma_x(sz), soma_y(sz);

		for (int i = 0; i < sz; i++)
		{
			if (i > 0)
			{
				soma_x[i] = soma_x[i-1];
				soma_y[i] = soma_y[i-1];
			}

			soma_x[i] += V[i].x;
			soma_y[i] += V[i].y;
		}

		int last = 0;

		for (int i = 0; i < sz; i++)
		{
			int ini = 0, fim = sz-1, opt = 0;

			if (i == 0 || cross(V[i], V[i-1]) != 0) last = i;

			fim = min(sz-1, sz - (i - last));

			while (ini <= fim)
			{
				int mid = (ini+fim)>>1;

				int j = (i+mid)%sz;

				if (cross(V[i], V[j]) >= 0) opt = mid, ini = mid+1;
				else fim = mid-1;
			}

			int j = (i+opt)%sz;

			ll S_x = Soma(i, j, soma_x), S_y = Soma(i, j, soma_y);

			ans += (1ll*S_y*V[i].x - 1ll*S_x*V[i].y);
			ans -= (1ll*(soma_y.back()-S_y)*V[i].x - 1ll*(soma_x.back()-S_x)*V[i].y);

		}
	}

	ans /= 6;

	if (ans%2) printf("%lld.5\n", ans/2);
	else printf("%lld.0\n", ans/2);
}
