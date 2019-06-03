// IOI 2014 - Friend
// Lúcio Cardoso

#include <bits/stdc++.h>
#include "friend.h"

using namespace std;

const int maxn = 1e5+10;

int dp[2][maxn];

int findSample(int n, int confidence[], int host[], int protocol[])
{
	for (int i = 0; i < n; i++)
		dp[1][i] = confidence[i];

	for (int i = n-1; i > 0; i--)
	{
		if (protocol[i] == 0)
		{
			dp[0][host[i]] += max(dp[0][i], dp[1][i]);

			dp[1][host[i]] += dp[0][i];
		}
		else if (protocol[i] == 1)
		{
			dp[1][host[i]] = max(dp[1][host[i]], dp[0][host[i]]) + max(dp[0][i], dp[1][i]);

			dp[0][host[i]] += dp[0][i];
		}
		else
		{
			dp[1][host[i]] = max(dp[0][host[i]]+dp[1][i], dp[1][host[i]]+dp[0][i]);

			dp[0][host[i]] += dp[0][i];
		}
	}

	return max(dp[0][0], dp[1][0]);
}
