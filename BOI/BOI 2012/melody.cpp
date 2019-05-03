// BOI 2012 - Melody
// Lúcio Cardoso

// Same solution as this one: http://www.boi2012.lv/data/day2/spoilers/melody.pdf

#include <bits/stdc++.h>

using namespace std;

const int maxn = 110;

const int maxl = 1e5+10;

const int inf = 1e9+10;

int n, s, g, l;

int seq[maxl], first[maxn][maxl];

int dist[maxn][maxn];
int dif[maxn][maxn];

int dp[maxl];

char a[maxn][maxn];

void calc_dif(void)
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= s; k++)
				if (a[i][k] != a[j][k])
					dif[i][j]++;
}

int main(void)
{
	scanf("%d %d %d", &n, &s, &g);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= s; j++)
			scanf(" %c", &a[i][j]);

	scanf("%d", &l);

	for (int i = 1; i <= l; i++)
		scanf("%d", &seq[i]);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= l; j++)
			first[i][j] = (seq[j] == i ? j : first[i][j-1]);

	calc_dif();

	for (int i = 1; i <= n; i++)
	{
		dist[i][i] = 0;

		for (int j = 1; j <= n; j++)
		{
			if (i == j) continue;

			dist[i][j] = inf;

			if (dif[i][j] <= g) dist[i][j] = 1;
		}
	}

	// Floyd Warshall
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);

	int ans = 0;

	// Calculate DP
	for (int i = 1; i <= l; i++)
	{
		dp[i] = 1;

		for (int j = 1; j <= n; j++)
		{
			int d = dist[seq[i]][j];
			int pos = (d == -1 ? 0 : first[j][max(0, i-d)]);

			if (seq[i] == j) pos = first[j][i-1];

			dp[i] = max(dp[i], 1+dp[pos]);
		}

		ans = max(ans, dp[i]);
	}

	// This is a (real messy) way to print the solution
	vector<int> Place;

	int aux = 0, cur_pos = l;
	while (aux != ans)
	{
		bool ok = 0;

		for (int j = 1; j <= n; j++)
		{
			int d = dist[seq[cur_pos]][j];
			int pos = (d == -1 ? 0 : first[j][max(0, cur_pos-d)]);

			if (seq[cur_pos] == j) pos = first[j][cur_pos-1];

			if (aux+dp[pos]+1 == ans)
			{
				Place.push_back(cur_pos);
				aux++, cur_pos = pos, ok = 1;
				break;
			}
		}

		if (!ok) cur_pos--;
	}

	reverse(Place.begin(), Place.end());

	printf("%d\n", l-ans);

	int nxt = Place[0], at = seq[Place[0]], ind = 0;
	for (int i = 1; i <= l; i++)
	{
		int x;
		for (int j = 1; j <= n; j++)
			if (dif[j][at] <= g && (j == seq[nxt] || dist[j][seq[nxt]] == dist[at][seq[nxt]]-1))
				x = j;

		at = x;
		printf("%d ", at);

		if (i == nxt)
		{
			if (ind == Place.size()-1)
			{
				for (int j = i+1; j <= l; j++)
					printf("%d ", seq[nxt]);
				printf("\n");

				return 0;
			}

			nxt = Place[++ind];
		}
	}

	printf("\n");
}
