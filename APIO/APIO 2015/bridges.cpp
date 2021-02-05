// APIO 2020 - Palembang Bridges
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 1e5+10;
const ll inf = 1e18+10;

struct Mediana
{
	multiset<int> lower, upper;
	ll cost_lower, cost_upper;

	void clear(void)
	{
		lower.clear(); upper.clear();
		cost_lower = cost_upper = 0;
	}

	void add(int x)
	{
		int tot = lower.size() + upper.size();

		if (tot%2)
		{
			if (x >= *upper.begin())
			{
				lower.insert(*upper.begin()); cost_lower += 1ll*(*upper.begin());
				cost_upper -= 1ll*(*upper.begin()); upper.erase(upper.begin());
				upper.insert(x); cost_upper += 1ll*x;
			}
			else
			{
				lower.insert(x); cost_lower += 1ll*x;
			}
		}
		else
		{
			if (x >= *upper.begin())
			{
				upper.insert(x); cost_upper += 1ll*x;
			}
			else
			{
				upper.insert(*lower.rbegin()); cost_upper += 1ll*(*lower.rbegin());
				cost_lower -= 1ll*(*lower.rbegin()); lower.erase(lower.find(*lower.rbegin()));
				lower.insert(x); cost_lower += 1ll*x;
			}
		}
	}

	ll get(void)
	{
		int med = *upper.begin();
		int sz_lower = lower.size(), sz_upper = upper.size();

		return (1ll*sz_lower*med - 1ll*sz_upper*med + cost_upper - cost_lower);
	}
} Med;

char t[2][maxn];
int pos[2][maxn];

ll pref[maxn], suf[maxn];

int main(void)
{
	int k, n;
	scanf("%d %d", &k, &n);

	for (int i = 1; i <= n; i++)
		scanf(" %c %d %c %d", &t[0][i], &pos[0][i], &t[1][i], &pos[1][i]);

	if (k == 1)
	{
		ll ans = 0;

		vector<int> v;

		for (int i = 1; i <= n; i++)
		{
			if (t[0][i] == t[1][i]) ans += 1ll*abs(pos[0][i]-pos[1][i]);
			else
			{
				v.push_back(pos[0][i]);
				v.push_back(pos[1][i]);
			}
		}

		if (v.size())
		{
			sort(v.begin(), v.end());

			int med = v[v.size()/2];

			for (auto x: v)
				ans += 1ll*abs(x-med);

			ans += 1ll*v.size()/2;
		}

		printf("%lld\n", ans);
		return 0;
	}

	ll ini = 0;
	vector<pii> v;

	for (int i = 1; i <= n; i++)
	{
		if (t[0][i] == t[1][i]) ini += 1ll*abs(pos[0][i]-pos[1][i]);
		else v.push_back({min(pos[0][i], pos[1][i]), max(pos[0][i], pos[1][i])});
	}

	if (v.size() == 0)
	{
		printf("%lld\n", ini);
		return 0;
	}

	sort(v.begin(), v.end(), [&] (pii a, pii b) {return 1ll*a.ff + 1ll*a.ss < 1ll*b.ff + 1ll*b.ss;});

	Med.clear();

	for (int i = 0; i < v.size(); i++)
	{
		Med.add(v[i].ff); Med.add(v[i].ss);

		pref[i] = Med.get();
	}

	Med.clear();

	for (int i = v.size()-1; i >= 0; i--)
	{
		Med.add(v[i].ff); Med.add(v[i].ss);

		suf[i] = Med.get();
	}

	ll ans = min(pref[v.size()-1], suf[0]) + ini;

	for (int i = 0; i < v.size()-1; i++)
		ans = min(ans, pref[i] + suf[i+1] + ini);

	printf("%lld\n", ans + v.size());
}
