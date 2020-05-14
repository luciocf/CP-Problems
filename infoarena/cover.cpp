// infoarena - Cover
// Lúcio Cardoso

// Solution: https://github.com/stefdasca/CompetitiveProgramming/blob/master/Infoarena/cover.cpp

#include <bits/stdc++.h>

#define gc getchar_unlocked

#pragma GCC target ("avx2")
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")

#define ff first
#define ss second

using namespace std;

const int maxn = 1e6+10;

typedef pair<int, int> pii;

struct MinQueue
{
	int l, r;
	deque<pii> dq;

	void init(void) {l = r = 1; dq.clear();}

	void push(int x)
	{
		while (dq.size() && dq.back().ff >= x)
			dq.pop_back();

		dq.push_back({x, r++});
	}

	void pop(void)
	{
		if (dq.size() && dq.front().ss == l)
			dq.pop_front();

		l++;
	}

	int getmin(void) {return (dq.size() ? dq.front().ff : 0);}
};

pii range[60010];
int cost[maxn];

int mx_l[maxn];

int dp[maxn];

void scan(int &x)
{
    int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}

int main(void)
{
	freopen("cover.in", "r", stdin); freopen("cover.out", "w", stdout);

	int n, m;
	scan(n); scan(m);

	for (int i = 1; i <= m; i++)
		scan(cost[i]);

	for (int i = 1; i <= n; i++)
	{
		scan(range[i].ff); scan(range[i].ss);

		mx_l[range[i].ss] = max(mx_l[range[i].ss], range[i].ff);
	}

	sort(range+1, range+n+1);

	for (int i = 1; i <= m; i++)
		mx_l[i] = max(mx_l[i], mx_l[i-1]);

	int ptr = 0;
	MinQueue mq; mq.init();

	mq.push(0);

	int ans = 2e9+10;
	for (int i = 1; i <= range[n].ss; i++)
	{
		while (ptr < mx_l[i-1])
			mq.pop(), ++ptr;

		dp[i] = cost[i] + mq.getmin();

		if (i >= range[n].ff && i <= range[n].ss)
			ans = min(ans, dp[i]);

		mq.push(dp[i]);
	}

	printf("%d\n", ans);
}
