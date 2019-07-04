// POI 2006 - Teddies
// Lúcio Cardoso

// Solution:

// 1. Build the sequence with a dp using the following states:
//	* Amount of objects a1 being used
//	* Amount of objects a2 being used
//	* (...) b1 being used
//	* (...) b2 being used
//	* Last two types of objects being used

// 2. For the dp transitions, just choose the type of object
// before the 2 types of current objects. Be careful to check if they can be
// consecutive.

// 3. To reduce memory, just use mod 2 in the first argument. Also, since we do that,
// there's an edge case with the dp table when the sum of all amounts of objects being <= 2.
// Store this DP separately.

// Complexity is O(38^4 * 4^3).

#include <bits/stdc++.h>

using namespace std;

const int maxn = 39;
const int mod = 1e6;

int dp[2][maxn][maxn][maxn][4][4];
int aux[3][3][3][3][4][4];

int t1[4] = {1, 2, 1, 2};
int t2[4] = {0, 0, 1, 1};

bool ok(int a, int b, int c)
{
	if (t1[a] == t1[b] && t1[b] == t1[c]) return false;
	if (t2[a] == t2[b] && t2[b] == t2[c]) return false;
	return true;
}

void add(int &a, int b) {a = (a+b)%mod;}

int main(void)
{
	int n_a1, n_a2, n_b1, n_b2;
	scanf("%d %d %d %d", &n_a1, &n_a2, &n_b1, &n_b2);

	if (n_a1+n_a2+n_b1+n_b2 == 1)
	{
		printf("1\n");
		return 0;
	}

	if (n_a1 >= 2) aux[2][0][0][0][0][0] = 1;
	if (n_a2 >= 2) aux[0][2][0][0][1][1] = 1;
	if (n_b1 >= 2) aux[0][0][2][0][2][2] = 1;
	if (n_b2 >= 2) aux[0][0][0][2][3][3] = 1;

	if (n_a1 >= 1 && n_a2 >= 1)
	{
		aux[1][1][0][0][0][1] = 1;
		aux[1][1][0][0][1][0] = 1;
	}
	if (n_a1 >= 1 && n_b1 >= 1)
	{
		aux[1][0][1][0][0][2] = 1;
		aux[1][0][1][0][2][0] = 1;
	}
	if (n_a1 >= 1 && n_b2 >= 1)
	{
		aux[1][0][0][1][0][3] = 1;
		aux[1][0][0][1][3][0] = 1;
	}
	if (n_a2 >= 1 && n_b1 >= 1)
	{
		aux[0][1][1][0][1][2] = 1;
		aux[0][1][1][0][2][1] = 1;
	}
	if (n_a2 >= 1 && n_b2 >= 1)
	{
		aux[0][1][0][1][1][3] = 1;
		aux[0][1][0][1][3][1] = 1;
	}
	if (n_b1 >= 1 && n_b2 >= 1)
	{
		aux[0][0][1][1][2][3] = 1;
		aux[0][0][1][1][3][2] = 1;
	}

	if (n_a1+n_a2+n_b1+n_b2 <= 2)
	{
		int ans = 0;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				ans += aux[n_a1][n_a2][n_b1][n_b2][i][j];

		printf("%d\n", ans);
		return 0;
	}

	for (int a1 = 0; a1 <= n_a1; a1++)
	{	
		for (int a2 = 0; a2 <= n_a2; a2++)
		{			
			for (int b1 = 0; b1 <= n_b1; b1++)
			{
				for (int b2 = 0; b2 <= n_b2; b2++)
				{
					for (int A = 0; A < 4; A++)
					{
						for (int B = 0; B < 4; B++)
						{
							dp[a1%2][a2][b1][b2][A][B] = 0;

							if (a1+a2+b1+b2 <= 2) continue;
							if ((A == 0 || B == 0) && !a1) continue;
							if ((A == 1 || B == 1) && !a2) continue;
							if ((A == 2 || B == 2) && !b1) continue;
							if ((A == 3 || B == 3) && !b2) continue;

							for (int C = 0; C < 4; C++)
							{
								if (!ok(A, B, C)) continue;

								int prev = (a1-1)%2, at = a1%2;
								
								if (B == 0)
								{
									int x = dp[prev][a2][b1][b2][C][A];
									if (a1+a2+b1+b2-1 <= 2) x = aux[a1-1][a2][b1][b2][C][A];

									add(dp[at][a2][b1][b2][A][B], x);
								}
								if (B == 1)
								{
									int x = dp[at][a2-1][b1][b2][C][A];
									if (a1+a2+b1+b2-1 <= 2) x = aux[a1][a2-1][b1][b2][C][A];

									add(dp[at][a2][b1][b2][A][B], x);
								}
								if (B == 2)
								{
									int x = dp[at][a2][b1-1][b2][C][A];
									if (a1+a2+b1+b2-1 <= 2) x = aux[a1][a2][b1-1][b2][C][A];

									add(dp[at][a2][b1][b2][A][B], x);
								}
								if (B == 3)
								{
									int x = dp[at][a2][b1][b2-1][C][A];
									if (a1+a2+b1+b2-1 <= 2) x = aux[a1][a2][b1][b2-1][C][A];

									add(dp[at][a2][b1][b2][A][B], x);
								}
							}
						}
					}
				}
			}
		}
	}

	int ans = 0;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			add(ans, dp[n_a1%2][n_a2][n_b1][n_b2][i][j]);

	printf("%d\n", ans);
}
