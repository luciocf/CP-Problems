// Codeforces 1407D - Discrete Centrifugal Jumps
// Lúcio Cardoso

// Solution is the same as in editorial

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 3e5+10;

int a[maxn];
int dp[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	stack<pii> stk_1, stk_2;

	for (int i = 1; i <= n; i++)
	{
		dp[i] = i-1;

		int ant = a[i];

		while (stk_1.size() && stk_1.top().ff < a[i])
		{
			if (stk_1.top().ff != ant)
				dp[i] = min(dp[i], 1+dp[stk_1.top().ss]);

			ant = stk_1.top().ff;
			stk_1.pop();
		}

		ant = a[i];

		while (stk_2.size() && stk_2.top().ff > a[i])
		{
			if (stk_2.top().ff != ant)
				dp[i] = min(dp[i], 1+dp[stk_2.top().ss]);

			ant = stk_2.top().ff;
			stk_2.pop();
		}

		if (stk_1.size()) dp[i] = min(dp[i], 1+dp[stk_1.top().ss]);

		if (stk_2.size()) dp[i] = min(dp[i], 1+dp[stk_2.top().ss]);

		stk_1.push({a[i], i}); stk_2.push({a[i], i});
	}

	printf("%d\n", dp[n]);
}
