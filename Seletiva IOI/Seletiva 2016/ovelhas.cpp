// Seletiva IOI 2016 - Ovelhas
// Lúcio Cardoso

#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;

typedef pair<int, int> pt;
typedef long long ll;

const int maxn = 2e5+10;

int n, q;

pt a[maxn], b[maxn];

pt sub(pt a, pt b)
{
	return {a.x-b.x, a.y-b.y};
}

int sign(ll x)
{
	return (x > 0 ? 1 : -1);
}

ll cross(pt a, pt b)
{
	return 1ll*a.x*b.y - 1ll*a.y*b.x;
}

bool cw(pt a, pt b, pt c)
{
	return cross(sub(b, a), sub(c, a)) < 0;
}

bool ccw(pt a, pt b, pt c)
{
	return cross(sub(b, a), sub(c, a)) > 0;
}

bool in_segment(pt a, pt b, pt p)
{
	return (p.x >= min(a.x, b.x) && p.x <= max(a.x, b.x)
		&& p.y >= min(a.y, b.y) && p.y <= max(a.y, b.y));
}

bool inside(pt a, pt b, pt c, pt p)
{
	ll area = cross(sub(b, a), sub(c, a));

	ll a1 = cross(sub(a, p), sub(b, p));
	ll a2 = cross(sub(a, p), sub(c, p));
	ll a3 = cross(sub(b, p), sub(c, p));

	return (abs(a1)+abs(a2)+abs(a3) == abs(area));
}

int sub_reta(void)
{
	int ans = 0;

	int mn_x = 1e9+10, mx_x = -1e9-10;
	int mn_y = 1e9+10, mx_y = -1e9-10;

	for (int i = 1; i <= n; i++)
	{
		mn_x = min(mn_x, a[i].x), mx_x = max(mx_x, a[i].x);

		mn_y = min(mn_y, a[i].y), mx_y = max(mx_y, a[i].y);
	}

	for (int i = 1; i <= q; i++)
		if (cross(sub(a[1], b[i]), sub(a[2], b[i])) == 0ll &&
			b[i].x >= mn_x && b[i].x <= mx_x && b[i].y >= mn_y && b[i].y <= mx_y)
			ans++;

	return ans;
}

int solve(void)
{
	sort(a+1, a+n+1);

	vector<pt> upper, lower;

	upper.push_back(a[1]), lower.push_back(a[1]);

	for (int i = 2; i <= n; i++)
	{
		if (i == n || ccw(a[1], a[n], a[i]))
		{
			while (upper.size() >= 2 && !cw(upper[upper.size()-2], upper.back(), a[i]))
				upper.pop_back();

			upper.push_back(a[i]);
		}

		if (i == n || cw(a[1], a[n], a[i]))
		{
			while (lower.size() >= 2 && !ccw(lower[lower.size()-2], lower.back(), a[i]))
				lower.pop_back();

			lower.push_back(a[i]);
		}
	}

	vector<pt> env;

	for (auto p: upper)
		env.push_back(p);

	for (int i = (int)lower.size()-2; i > 0; i--)
		env.push_back(lower[i]);

	int tot = 0;

	for (int i = 1; i <= q; i++)
	{
		int ini = 1, fim = env.size()-2, ans = -1;
		pt p = b[i];

		while (ini <= fim)
		{
			int mid = (ini+fim)>>1;

			if (cross(sub(env[0], p), sub(env[mid], p)) == 0)
			{
				if (in_segment(env[0], env[mid], p))
					tot++;

				ans = -1;
				break;
			}

			if (cross(sub(env[0], p), sub(env[mid+1], p)) == 0)
			{
				if (in_segment(env[0], env[mid+1], p))
					tot++;

				ans = -1;
				break;
			}

			int sign1 = sign(cross(sub(p, env[mid]), sub(env[0], env[mid])));
			int sign2 = sign(cross(sub(p, env[mid+1]), sub(env[0], env[mid+1])));

			if (sign1 != sign2)
			{
				ans = mid;
				break;
			}

			if (sign1 == -1) ini = mid+1;
			else fim = mid-1;
		}

		if (ans == -1) continue;

		if (inside(env[0], env[ans], env[ans+1], p))
			tot++;
	}

	return tot;
}	

int main(void)
{
	scanf("%d %d", &n, &q);

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &a[i].x, &a[i].y);

	for (int i = 1; i <= q; i++)
		scanf("%d %d", &b[i].x, &b[i].y);

	bool ok = 1;
	for (int i = 3; i <= n; i++)
		if (cross(sub(a[1], a[i]), sub(a[2], a[i])) != 0)
			ok = 0;

	if (ok)
	{
		printf("%d\n", sub_reta());
		return 0;
	}

	printf("%d\n", solve());
}
