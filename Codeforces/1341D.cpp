// Codeforces 1341D - Nastya and Scoreboard
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e3+10;

int n, k;

string num[10];

string a[maxn];
bool valid[maxn]; // se a[i] é valido

int cost[maxn][10]; // custo se consigo mudar a[i] para j

int dp[maxn][maxn];

void init(void)
{
	num[0] = "1110111";
	num[1] = "0010010";
	num[2] = "1011101";
	num[3] = "1011011";
	num[4] = "0111010";
	num[5] = "1101011";
	num[6] = "1101111";
	num[7] = "1010010";
	num[8] = "1111111";
	num[9] = "1111011";
}

void calc(void)
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			int tot = 0;
			bool ok = 1;

			for (int l = 0; l < 7; l++)
			{
				if (a[i][l] == '1' && num[j][l] == '0')
					ok = 0;

				if (a[i][l] == '0' && num[j][l] == '1')
					tot++;
			}

			if (ok) cost[i][j] = tot;
			else cost[i][j] = -1;
		}
	}
}

int solve(int pos, int x)
{
	if (pos == n+1 && x) return 0;
	if (pos == n+1) return 1;
	if (dp[pos][x] != -1) return dp[pos][x];

	int ans = 0;

	for (int i = 0; i <= 9; i++)
		if (cost[pos][i] != -1 && cost[pos][i] <= x)
			ans |= solve(pos+1, x-cost[pos][i]);

	return dp[pos][x] = ans;
}

int main(void)
{
	init();

	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
		cin >> a[i];

	calc();

	memset(dp, -1, sizeof dp);

	vector<int> ans;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 9; j >= 0; j--)
		{
			if (cost[i][j] != -1 && cost[i][j] <= k && solve(i+1, k-cost[i][j]))
			{
				ans.push_back(j);
				k -= cost[i][j];
				break;
			}
		}
	}

	if (ans.size() != n) printf("-1\n");
	else
	{
		for (int i = 0; i < ans.size(); i++)
			printf("%d", ans[i]);
		printf("\n");
	}
}
