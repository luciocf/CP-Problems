// POI 2014 - Little Bird
// Lúcio Cardoso

// Solution:

// Let dp[i] = minimum cost to go from 1 to i. If mn is the minimum dp value in the range [i-k, i], then dp[i] is
// either mn or mn+1. If the tallest tree with dp value equal to mn has height H, then dp[i] = mn iff H > a[i].
// Otherwise, dp[i] = mn+1.

// Thus, the problem becomes finding the minimum dp value in every window of size k and also finding the tallest tree
// with such dp value. To find those values, we can use a minqueue (or monotonic queue) on pairs {dp_value, height_of_tree}
// for every window of size k.

// Complexity: O(n*q)

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e6+10;

struct MinQueue
{
	int l, r;
	deque<pair<pii, int>> dq;

	void init(void) {l = r = 0; dq.clear();}

	void push(int v, int h)
	{
		while (dq.size() && (dq.back().ff.ff > v || (dq.back().ff.ff == v && dq.back().ff.ss <= h)))
			dq.pop_back();

		dq.push_back({{v, h}, r++});
	}

	void pop(void)
	{
		if (dq.size() && dq.front().ss == l)
			dq.pop_front();

		++l;
	}

	int getmin_v(void) {return dq.front().ff.ff;}

	int getmax_h(void) {return dq.front().ff.ss;}
};

int a[maxn];
int dp[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	int q;
	scanf("%d", &q);

	while (q--)
	{
		int k;
		scanf("%d", &k);

		MinQueue mq;
		mq.init();

		dp[1] = 0;

		mq.push(0, a[1]);

		for (int i = 2; i <= n; i++)
		{
			if (i >= k+2) mq.pop();

			int mn = mq.getmin_v();
			int mx = mq.getmax_h();

			if (mx > a[i]) dp[i] = mn;
			else dp[i] = mn+1;

			mq.push(dp[i], a[i]);
		}

		printf("%d\n", dp[n]);
	}
}
