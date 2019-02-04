// APIO 2010 - Commando
// Lúcio Cardoso

#include <bits/stdc++.h>
#define ff first
#define ss second

using namespace std;

const int maxn = 1e6+10;

const long long inf = 1e18+10;

typedef long long ll;

typedef pair<ll, ll> pii;

ll dp[maxn];

vector<pii> v;

bool bad(pii a, pii b, pii c)
{
    return (a.ss-c.ss)*(c.ff-b.ff) >= (b.ss-c.ss)*(c.ff-a.ff);
}

void add(pii line)
{
	while (v.size() > 1 && bad(v[v.size()-2], v.back(), line))
		v.pop_back();
	v.push_back(line);
}

ll get(int pos, ll x)
{
	return ((ll)v[pos].ff*x+(ll)v[pos].second);
}

ll busca(ll x)
{
	if (v.size() == 1) return get(0, x);

	int ini = 0, fim = v.size()-2;
	ll ans = get(v.size()-1, x);

	while (ini <= fim)
	{
		int mid = (ini+fim)>>1;
		if (get(mid, x) >= get(mid+1, x)) fim = mid-1, ans = get(mid, x);
		else ini = mid+1;
	}

	return ans;
}

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0);
    
	int n;
	ll a, b, c;
	cin >> n >> a >> b >> c;

	ll ans = -inf, soma = 0LL;
	add({0, 0});

	for (int i = 1; i <= n; i++)
	{
		ll x;
		cin >> x;

		soma += x;

		dp[i] = busca(soma)+a*soma*soma+b*soma+c;
		ans = max(ans, dp[i]);

		add({-2LL*a*soma, a*soma*soma - b*soma + dp[i]});
	}

	cout << ans << "\n";
}
