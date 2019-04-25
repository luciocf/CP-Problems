// IOI 2008 - Linear Garden
// Lúcio Cardoso

// Solution:

// 1. Let QL[i] be the amount of 'L' chars in the range [1..i]. Define QP[i] similarly. If the
// difference between the amount of 'L's and 'P's is greater than 2 in a range [l..r], then
// (QL[r]-QL[l-1])-(QP[r]-QP[l-1]) > 2 --> QL[r]-QP[r] > QL[l-1]-QP[l-1]+2.

// 2. We can use DP to calculate the amount of strings smaller than the given one. It will consist of 5 states:
// The current index i in the string, the current value of QL[i]-QP[i], the greatest previous value of QL[j]-QP[j] (for some j),
// the greatest previous value of QP[j]-QL[j] and a boolean which indicates if the current string being built is a prefix of the original
// or if it's alphabetically smaller.

// 3. Using the current state DP[i][j][l][p][m], we will try to build a new state in position i+1, by using a letter 'L' or 'P'. To check
// if we can use one of these letters and adjust the next state if we use them, we will use the condition on (1). That is, if the current value of
// j is non-negative, it means QL[i] > QP[i], so we need to check if by adding an L letter we break the condition on (1), and for that, we use 
// the maximum QP[]-QL[] difference. We check this similarly for the case that j is negative.

// 4. Note that with this solution, we need to use the memory trick to reduce the amount of memory used. That is, we
// only need to store the DP value for the current position and the position before, making the first state in the DP either 1 or 0.

// Complexity: O(180*N)

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6+10;
const int delta = 5;

int n, mod;

int dp[2][5][3][3][2];

char s[maxn];

bool bad(int dif, int mx)
{
	if (dif > 2 || (dif == 2 && mx > 0) || (dif == 1 && mx > 1)) return 1;
	return 0;
}

void add(int &a, int &b)
{
	a = (a+b)%mod;
}

void init(int cur)
{
	for (int j = 0; j < 5; j++)
		for (int l = 0; l < 3; l++)
			for (int p = 0; p < 3; p++)
				for (int m = 0; m < 2; m++)
					dp[cur][j][l][p][m] = 0;
}

int main(void)
{
	scanf("%d %d", &n, &mod);

	for (int i = 1; i <= n; i++)
		scanf(" %c", &s[i]);

	if (s[1] == 'L') dp[1][1][1][0][1] = 1;
	else
	{
		dp[1][-1+delta][0][1][1] = 1;
		dp[1][1][1][0][0] = 1;
	}

	for (int i = 1; i < n; i++)
	{
		int cur = (i+1)%2, ant = i%2;

		init(cur);

		for (int j = 0; j < 5; j++)
		{
			for (int l = 0; l < 3; l++)
			{
				for (int p = 0; p < 3; p++)
				{
					for (int m = 0; m < 2; m++)
					{
						int dif = (j <= 2 ? j : abs(j-delta));

						if (j <= 2 && bad(dif, p)) continue;
						if (j > 2 && bad(dif, l)) continue;

						if ((j > 2 && !bad(dif-1, l)) || !bad(dif+1, p))
						{
							int e;
							if (m == 0 || s[i+1] == 'P') e = 0;
							else e = 1;

							if (j > 2)
							{
								int newdif = (j == 3 ? 4 : 0);
								add(dp[cur][newdif][l][p][e], dp[ant][j][l][p][m]);
							}
							else
							{
								int newdif = dif+1, newmax = max(l, newdif);
								add(dp[cur][newdif][newmax][p][e], dp[ant][j][l][p][m]);
							}
						}

						if ((j > 0 && j <= 2 && !bad(dif-1, p)) || !bad(dif+1, l))
						{
							if (m && s[i+1] == 'L') continue;

							int e = m;

							if (j == 0)
							{
								int newdif = 4, newmax = max(p, 1);
								add(dp[cur][newdif][l][newmax][e], dp[ant][j][l][p][m]);
							}
							else if (j <= 2)
							{
								int newdif = dif-1;
								add(dp[cur][newdif][l][p][e], dp[ant][j][l][p][m]);
							}
							else
							{
								int newdif = 3, newmax = max(p, dif+1);
								add(dp[cur][newdif][l][newmax][e], dp[ant][j][l][p][m]);
							}
						}
					}
				}
			}
		}
	}

	int ans = 0;
	for (int j = 0; j < 5; j++)
		for (int l = 0; l < 3; l++)
			for (int p = 0; p < 3; p++)
				add(ans, dp[n%2][j][l][p][0]);

	ans = (ans+1)%mod;

	printf("%d\n", ans);
}
