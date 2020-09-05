// Seletiva IOI 2019 - Comida
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 2e5+10;
const int inf = 1e9+10;

int n;

pii sub(pii a, pii b)
{
	return {a.ff-b.ff, a.ss-b.ss};
}

ll cross(pii a, pii b)
{
	return 1ll*a.ff*b.ss - 1ll*a.ss*b.ff;
}

bool cw(pii a, pii b, pii c)
{
	return cross(sub(b, a), sub(c, a)) < 0;
}

bool menor(pii a, pii b)
{
	return 1ll*a.ff*b.ss < 1ll*a.ss*b.ff;
}

struct ConvexHull
{
	vector<pii> pt, env;

	pii m;
	ll ganho, gasto;

	int at;

	void get_hull(void)
	{
		pii p1 = pt[0], p2 = pt.back();

		env.push_back(p1);

		for (int i = 1; i < pt.size(); i++)
		{
			if (i == pt.size()-1 || cw(p1, pt[i], p2))
			{
				while (env.size() >= 2 && !cw(env[env.size()-2], env.back(), pt[i]))
					env.pop_back();

				env.push_back(pt[i]);
			}
		}

		while (env.size() >= 2 && env.back().ss < env[env.size()-2].ss)
			env.pop_back();

		if (env.size() == 1) m = {-inf, 1};
		else
		{
			ll g = __gcd(env[1].ss-env[0].ss, env[1].ff-env[0].ff);

			m = {(env[1].ss-env[0].ss)/g, (env[1].ff-env[0].ff)/g};
		}

		ganho = env[0].ss, gasto = env[0].ff;
		at = 0;
	}

	bool operator<(const ConvexHull &o) const
	{
		return menor(m, o.m);
	}
} CH[maxn];

int main(void)
{
	ll r;
	scanf("%d %lld", &n, &r);

	ll ans = 0;

	for (int i = 1; i <= n; i++)
	{
		int k;
		scanf("%d", &k);

		map<int, int> mp;

		while (k--)
		{
			int x, y;
			scanf("%d %d", &x, &y);

			mp[x] = max(mp[x], y);
		}

		for (auto pp: mp)
			CH[i].pt.push_back(pp);

		sort(CH[i].pt.begin(), CH[i].pt.end());

		CH[i].get_hull();

		r -= 1ll*CH[i].gasto;
		ans += 1ll*CH[i].ganho;
	}

	if (r < 0)
	{
		cout << "-1\n";
		return 0;
	}

	priority_queue<ConvexHull> pq;

	for (int i = 1; i <= n; i++)
		pq.push(CH[i]);

	while (pq.size())
	{
		auto e = pq.top(); pq.pop();
		if (e.m.ff == -inf) break;

		if (r + e.gasto >= e.env[e.at+1].ff)
		{
			r += e.gasto;
			ans -= e.ganho;

			e.gasto = e.env[e.at+1].ff, e.ganho = e.env[e.at+1].ss;

			r -= e.gasto;
			ans += e.ganho;

			e.at++;

			if (e.at == e.env.size()-1) continue;

			ll g = __gcd(e.env[e.at+1].ss-e.env[e.at].ss, e.env[e.at+1].ff-e.env[e.at].ff);
			e.m = {(e.env[e.at+1].ss-e.env[e.at].ss)/g, (e.env[e.at+1].ff-e.env[e.at].ff)/g};

			pq.push(e);
		}
		else
		{
			r += e.gasto;
			ans -= e.ganho;

			pii a = e.env[e.at];
			pii b = e.env[e.at+1];
 	
			ans += 1ll*b.ss + (1ll*r-b.ff)*(a.ss-b.ss)/(a.ff-b.ff);
			break;
		}
	}

	printf("%lld\n", ans);
}
