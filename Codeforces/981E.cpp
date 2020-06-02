// Codeforces 981E - Addition on Segments
// Lúcio Cardoso

// Solution:

// First of all, we can fix an element i as the one that will be the maximum in the array after
// some operations. Then, we can consider only ranges (l, r, v) that cover the element i.
// Now, the problem becomes finding all possible values in [1..n] that can be formed using a subset
// of ranges that cover element i.

// To solve this, we'll iterate through the ranges in increasing order of l (left endpoint) and define the
// following dp: dp[j] = max of (smallest right endpoint from a subset of ranges with nonempty intersection and with sum equal to j).
// We'll define dp[0] = inf. Then, for every range (l, r, v), we use the transition dp[j] = max(dp[j], min(r, dp[j-v])), whenever dp[j-v] >= l.
// The condition dp[j-v] >= l guarantees that the intersection between (l, r, v) and the subset chosen in dp[j-v] is nonempty.

// The answer to the problem is every index i such that dp[i] is positive.
// Complexity: O(q*n)

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e4+10;

struct Range
{
	int l, r, v;
} range[maxn];

int dp[maxn];

bool comp(Range a, Range b)
{
	return a.l < b.l;
}

int main(void)
{
	int n, q;
	scanf("%d %d", &n, &q);

	for (int i = 1; i <= q; i++)
		scanf("%d %d %d", &range[i].l, &range[i].r, &range[i].v);

	sort(range+1, range+q+1, comp);

	dp[0] = n;

	for (int i = 1; i <= q; i++)
	{
		int l = range[i].l, r = range[i].r, v = range[i].v;

		for (int j = n; j >= 1; j--)
			if (j >= v && dp[j-v] >= l)
				dp[j] = max(dp[j], min(r, dp[j-v]));
	}

	int tot = 0;
	for (int i = 1; i <= n; i++)
		if (dp[i])
			++tot;

	printf("%d\n", tot);
	for (int i = 1; i <= n; i++)
		if (dp[i])
			printf("%d ", i);
	printf("\n");
}
