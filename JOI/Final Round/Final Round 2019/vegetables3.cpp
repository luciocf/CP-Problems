// JOI Final Round 2019 - Growing Vegetables is Fun 3
// Lúcio Cardoso

// 1. Let's use a DP with the following states to construct any valid string with the least possible cost: 
// DP[last used color][amount of Rs used][amount of Gs used][amount of Ys used].

// 2. Notice that if we currently used a certain color K times, then it's always optimal to use the first K positions that such a color appears.

// 3. Suppose the previous color used was A, the new color we want to use is B and the other color is C. Let the original position in the string
// of A, B and C be posA, posB and posC respectively. Then, the number of swaps needed to insert B in the current position is equal to the amount
// of colors A in the range (posA, posB) plus the amount of colors C in the range (posC, posB). We can keep track of the position in the string for the 
// i-th occurence of a certain color by using an array. After that, it's simple to find these values using a prefix sum on the amount of 
// appearances of a certain color until a position 'i'.

// Overall complexity is O(n^3).

#include <bits/stdc++.h>

using namespace std;

const int maxn = 410;
const int inf = 1e9+10;

int n;
int a[maxn];

int qtd[3], pos[3][maxn];
int pref[3][maxn];

int dp[3][maxn][maxn][maxn];

int main(void)
{
	scanf("%d", &n);

	string s;
	cin >> s;

	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == 'R')
		{
			a[i+1] = 0, ++qtd[0];
			pos[0][qtd[0]] = i+1;
		}
		else if (s[i] == 'G')
		{
			a[i+1] = 1, ++qtd[1];
			pos[1][qtd[1]] = i+1;
		}
		else
		{
			a[i+1] = 2, ++qtd[2];
			pos[2][qtd[2]] = i+1;
		}
	}

	for (int t = 0; t < 3; t++)
	{
		for (int i = 1; i <= n; i++)
		{
			pref[t][i] = pref[t][i-1];

			if (a[i] == t) ++pref[t][i];
		}
	}

	for (int i = 0; i < 3; i++)
		for (int r = 0; r <= qtd[0]; r++)
			for (int g = 0; g <= qtd[1]; g++)
				for (int y = 0; y <= qtd[2]; y++)
					dp[i][r][g][y] = inf;

	dp[0][0][0][0] = 0;
	dp[1][0][0][0] = 0;
	dp[2][0][0][0] = 0;

	for (int r = 0; r <= qtd[0]; r++)
	{
		for (int g = 0; g <= qtd[1]; g++)
		{
			for (int y = 0; y <= qtd[2]; y++)
			{
				for (int pre = 0; pre < 3; pre++)
				{
					for (int at = 0; at < 3; at++)
					{
						if (at == pre) continue;
						if ((at == 0 && r == qtd[0]) || (at == 1 && g == qtd[1]) || (at == 2 && y == qtd[2])) continue;

						int ans = 0;

						// pos. of color 'pre', pos. of color 'at' and pos. of other color 'dif'
						int p1, p2, p3, dif;

						// These ifs are used only to find the correct values for p1, p2 and p3
						if (pre == 0)
						{
							p1 = pos[0][r];

							if (at == 1) p2 = pos[1][g+1], p3 = pos[2][y], dif = 2;
							else p2 = pos[2][y+1], p3 = pos[1][g], dif = 1;
						}
						else if (pre == 1)
						{
							p1 = pos[1][g];

							if (at == 0) p2 = pos[0][r+1], p3 = pos[2][y], dif = 2;
							else p2 = pos[2][y+1], p3 = pos[0][r], dif = 0;
						}
						else
						{
							p1 = pos[2][y];

							if (at == 0) p2 = pos[0][r+1], p3 = pos[1][g], dif = 1;
							else p2 = pos[1][g+1], p3 = pos[0][r], dif = 0;
						}

						ans += max(0, pref[pre][p2]-pref[pre][p1]);
						ans += max(0, pref[dif][p2]-pref[dif][p3]);

						ans += dp[pre][r][g][y];

						if (at == 0)
							dp[at][r+1][g][y] = min(dp[at][r+1][g][y], ans);
						else if (at == 1)
							dp[at][r][g+1][y] = min(dp[at][r][g+1][y], ans);
						else
							dp[at][r][g][y+1] = min(dp[at][r][g][y+1], ans);
					}
				}
			}
		}
	}

	int ans = inf;
	for (int i = 0; i < 3; i++)
		ans = min(ans, dp[i][qtd[0]][qtd[1]][qtd[2]]);

	if (ans == inf)
		printf("-1\n");
	else
		printf("%d\n", ans);
}
