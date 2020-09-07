// BOI 2012 - Brackets
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e4+10;
const int mod = 1e9+9;

char a[maxn];
int dp[2][maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf(" %c", &a[i]);

	dp[0][0] = 1;

	for (int i = 1; i <= n; i++)
	{
		int at = i%2;

		for (int j = 0; j <= i; j++)
		{
			dp[at][j] = dp[!at][j+1];

			if (j && a[i] == '(') dp[at][j] = (dp[at][j] + dp[!at][j-1])%mod;
		}
	}

	printf("%d\n", dp[n%2][0]);
}
