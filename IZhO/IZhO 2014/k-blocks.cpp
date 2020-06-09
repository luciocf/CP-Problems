// IZhO 2014 - K Blocks
// Lúcio Cardoso

// Solution: 

// We can solve the problem using dp. Let dp[i][j] be the minimum cost to divide the first i elements into j blocks.
// Then, we have that dp[i][j] = min(min(i > l > p) (dp[l-1][j-1] + a[i]), dp[p][j-1]), where  p is the first position
// such that p < i and a[p] > a[i].

// We can find p for every i with a monotonic stack in O(1). While calculating p in the stack for an index i with j blocks, 
// let mn[i] = min(l > p) dp[l-1][j-1]. We can find mn[i] by taking the minimum of mn[i] and mn[l] for every index l that's popped from the
// stack.

// Now, dp[i][j] = min(dp[p][l], a[i] + mn[i]). Hence, the solution is O(nk).

// If the part about calculating mn[i] was a bit confusing, take a look at the code.

#include <bits/stdc++.h>
 
#define ff first
#define ss second
 
using namespace std;
 
typedef pair<int, int> pii;
 
const int maxn = 1e5+10;
const int maxk = 110;
const int inf = 1e9+10;
 
int n, k;
int a[maxn];
 
int mn[maxn];
 
int dp[maxn][maxk];
 
int main(void)
{
	scanf("%d %d", &n, &k);
 
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
 
	dp[0][1] = inf, dp[1][1] = a[1];
	for (int i = 2; i <= n; i++)
		dp[i][1] = max(a[i], dp[i-1][1]);
 
	for (int j = 2; j <= k; j++)
	{
		stack<pii> stk;
 
		for (int i = 0; i < j; i++)
			dp[i][j] = inf;
 
		for (int i = j; i <= n; i++)
		{
			mn[i] = dp[i-1][j-1];
			dp[i][j] = inf;
 
			while (stk.size() && stk.top().ff <= a[i])
			{
				mn[i] = min(mn[i], mn[stk.top().ss]);
				stk.pop();
			}
 
			if (!stk.empty())
				dp[i][j] = dp[stk.top().ss][j];

			dp[i][j] = min(dp[i][j], a[i]+mn[i]); 

			stk.push({a[i], i});
		}
	}
 
	printf("%d\n", dp[n][k]);
}
