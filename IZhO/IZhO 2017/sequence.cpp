// IZhO 2017 - Longest beautiful sequence
// Lúcio Cardoso

/* Solution:

Let dp[i] be the size of the largest beautiful sequence ending at i. Then, 

	- dp[i] = 1 + max(dp[j]) where bitcount(a[i] & a[j]) = k[i].

Using this recurrence, it's easy to get 40 points. To optimize it, we can use a meet in the middle
approach, splitting each number in two masks: the first half and the second half, each with 10 bits.

Suppose we've already calculated every dp until i-1. Let best[mask_1][mask_2][x] be the index j
such that:

	 - the first half of a[j] equals mask_1
	 - bitcount(mask_2 & (second_half_of_a[j])) = x

Using this table, it's easy to find dp[i] iterating through every mask smaller than 2^10. After finding dp[i],
all that's left is to update the table 'best'. We can also easily do this by iterating through every possible mask in the
second position of the table (mask_2), since mask_1 is fixed (it's the first half of a[i]).

The complexity of this solution is O(n * 2^10).
*/

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 1e5+10;

int n;
int a[maxn], b[maxn];

int dp[maxn], ant[maxn];
pii best[1<<10][1<<10][11];

void print(int ans)
{
	printf("%d\n", ans);

	int at;
	for (int i = 1; i <= n; i++)
		if (dp[i] == ans)
			at = i;

	vector<int> out;

	while (at)
	{
		out.push_back(at);
		at = ant[at];
	}

	reverse(out.begin(), out.end());

	for (auto x: out)
		printf("%d ", x);
	printf("\n");
}

int main(void)
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for (int i = 1; i <= n; i++)
		scanf("%d", &b[i]);

	int ans = 0;

	for (int i = 1; i <= n; i++)
	{
		dp[i] = 1, ant[i] = 0;

		int half1 = 0, half2 = 0;

		for (int j = 0; j < 10; j++)
		{
			if (a[i]&(1<<j))
				half1 += (1<<j);

			if (a[i]&(1<<(j+10)))
				half2 += (1<<j);
		}

		for (int mask = 0; mask < (1<<10); mask++)
		{
			int x = __builtin_popcount(half1&mask);

			if (b[i] >= x && b[i]-x <= 10)
			{
				if (1 + best[mask][half2][b[i]-x].ff > dp[i])
				{
					dp[i] = 1 + best[mask][half2][b[i]-x].ff;

					ant[i] = best[mask][half2][b[i]-x].ss;
				}
			}
		}

		for (int mask = 0; mask < (1<<10); mask++)
		{
			int x = __builtin_popcount(half2&mask);

			if (dp[i] > best[half1][mask][x].ff)
				best[half1][mask][x] = {dp[i], i};
		}

		ans = max(ans, dp[i]);
	}

	print(ans);
}
