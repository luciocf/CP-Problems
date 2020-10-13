// Codeforces 1036E - Covered Points
// Lúcio Cardoso

// Solution is the same as the one in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const int maxn = 1e3+10;

pair<pii, pii> seg[maxn];

pii m[maxn], b[maxn];

void gcdify(pii &x)
{
	if (x.ff == 0 && x.ss == 0) return;

	ll g = __gcd(abs(x.ff), abs(x.ss));
	x = {x.ff/g, x.ss/g};
}

pii soma(pii x, pii y)
{
	pii ans;

	ans.ff = x.ff*y.ss + y.ff*x.ss;
	ans.ss = x.ss*y.ss;

	gcdify(ans);

	return ans;
}

pii sub(pii x, pii y)
{
	pii ans;

	ans.ff = x.ff*y.ss - y.ff*x.ss;
	ans.ss = x.ss*y.ss;

	gcdify(ans);

	return ans;
}

pii mult(pii x, pii y)
{
	pii ans = {x.ff*y.ff, x.ss*y.ss};
	gcdify(ans);

	return ans;
}

pii division(pii x, pii y)
{
	pii ans = {x.ff*y.ss, x.ss*y.ff};
	gcdify(ans);

	return ans;
}

bool inside(int i, pii pt)
{
	int x1 = min(seg[i].ff.ff, seg[i].ss.ff);
	int x2 = max(seg[i].ff.ff, seg[i].ss.ff);

	int y1 = min(seg[i].ff.ss, seg[i].ss.ss);
	int y2 = max(seg[i].ff.ss, seg[i].ss.ss);

	return (pt.ff >= x1 && pt.ff <= x2 && pt.ss >= y1 && pt.ss <= y2);
}

int main(void)
{
	int n;
	scanf("%d", &n);

	ll ans = 0;

	for (int i = 1; i <= n; i++)
	{
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

		seg[i] = {{x1, y1}, {x2, y2}};

		m[i] = {y2-y1, x2-x1};

		ans += (__gcd(abs(m[i].ff), abs(m[i].ss)) + 1);

		gcdify(m[i]);

		b[i] = {1ll*y1*m[i].ss - 1ll*x1*m[i].ff, m[i].ss};
		gcdify(b[i]);

	}

	for (int i = 1; i <= n; i++)
	{
		set<pii> st;

		for (int j = 1; j < i; j++)
		{
			if (m[i].ff == m[j].ff && m[i].ss == m[j].ss) continue;
			if (seg[i].ff.ff == seg[i].ss.ff && seg[j].ff.ff == seg[j].ss.ff) continue;

			if (seg[i].ff.ff == seg[i].ss.ff)
			{
				ll x = seg[i].ff.ff;

				pii s = soma(mult(m[j], {x, 1}), b[j]);

				if (s.ss == 1)
				{
					ll y = s.ff;

					if (inside(i, {x, y}) && inside(j, {x, y})) 
						st.insert({x, y});
				}

				continue;
			}
			else if (seg[j].ff.ff == seg[j].ss.ff)
			{
				ll x = seg[j].ff.ff;

				pii s = soma(mult(m[i], {x, 1}), b[i]);

				if (s.ss == 1 || s.ss == -1)
				{
					ll y = s.ff/s.ss;

					if (inside(i, {x, y}) && inside(j, {x, y})) 
						st.insert({x, y});
				}

				continue;
			}

			pii f1 = sub(b[j], b[i]);
			pii f2 = sub(m[i], m[j]);

			pii d = division(f1, f2);

			if (d.ss == 1 || d.ss == -1)
			{
				ll x = d.ff/d.ss;
				
				pii s = soma(mult(m[i], {x, 1}), b[i]);

				if (s.ss == 1)
				{
					ll y = s.ff;

					if (inside(i, {x, y}) && inside(j, {x, y})) 
						st.insert({x, y});
				}
			}
		}

		ans -= 1ll*st.size();
	}

	printf("%lld\n", ans);
}
