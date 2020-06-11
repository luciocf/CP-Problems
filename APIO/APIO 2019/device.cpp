// APIO 2019 - Strange Device
// Lúcio Cardoso

// Solution is the same as: https://github.com/SpeedOfMagic/CompetitiveProgramming/blob/master/APIO/19-strange_device.cpp

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<ll, int> pii;

const int maxn = 3e6+10;
const ll inf = 1e18;

int n;
ll A, B, p;

vector<pii> event;

void add_event(ll l, ll r)
{
	if (p <= inf/B)
		l %= (p*B), r %= (p*B);

	if (l <= r)
	{
		event.push_back({l, 0});
		event.push_back({r, 1});
	}
	else
	{
		event.push_back({l, 0});
		event.push_back({p*B-1ll, 1});

		event.push_back({0, 0});
		event.push_back({r, 1});
	}
}

int main(void)
{
	scanf("%d %lld %lld", &n, &A, &B);

	ll g = __gcd(A, B+1);
	p = A/g;

	bool flag = 0;

	for (int i = 1; i <= n; i++)
	{
		ll l, r;
		scanf("%lld %lld", &l, &r);

		if ((r-l+1)/p >= B)
			flag = 1;

		add_event(l, r);
	}

	if (flag)
	{
		printf("%lld\n", p*B);
		return 0;
	}

	ll prev, ans = 0;
	int open = 0;

	sort(event.begin(), event.end());

	for (auto E: event)
	{
		ll x = E.ff, type = E.ss;

		if (open == 0) prev = x;

		if (type == 0) open++;
		else open--;

		if (open == 0) ans += (x-prev+1ll);
	}

	printf("%lld\n", ans);
}
