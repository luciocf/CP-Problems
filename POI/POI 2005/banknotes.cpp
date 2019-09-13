// POI 2005 - Bank Notes
// Lúcio Cardoso

// Solution:

// The algorithm used is the solution to Bounded Knapsack problem, with complexity
// O(n*m). It's explained here: http://www.algonotes.com/en/knapsacks/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 210;
const int maxm = 2e4+10;
const int inf = 1e9+10;

struct MinQueue
{
	deque<pair<int, int>> dq;
	int l, r, soma;

	void init(void) {dq.clear(); l=r=soma=0;}

	void add(int x) {soma += x;}

	void push(int x)
	{
		while (!dq.empty() && x < dq.back().first+soma) dq.pop_back();

		dq.push_back({x-soma, r});
		r++;
	}

	void pop(void)
	{
		if (!dq.empty() && dq.front().second == l) dq.pop_front();
		++l;
	}

	int getmin(void) {return (dq.size() ? dq[0].first+soma : inf);}

	int size(void) {return r-l;}
} mq[maxm];

int w[maxn], b[maxn];

int dp[maxn][maxm];

int ans[maxn];

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &w[i]);

	for (int i = 1; i <= n; i++)
		scanf("%d", &b[i]);

	int k;
	scanf("%d", &k);

	for (int i = 0; i <= n; i++)
		for (int j = 1; j <= k; j++)
			dp[i][j] = inf;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < w[i]; j++)
			mq[j].init();

		for (int j = 0; j <= k; j++)
		{
			int m = j%w[i];

			if (mq[m].size() > b[i]) mq[m].pop();

			mq[m].add(1ll);
			mq[m].push(dp[i-1][j]);

			dp[i][j] = mq[m].getmin();
		}
	}

	printf("%d\n", dp[n][k]);

	int r = k, qtd = 0;

	for (int i = n; i >= 1; i--)
	{
		for (int j = 1; j <= b[i]; j++)
		{
			if (r >= j*w[i] && dp[i-1][r-j*w[i]] + j+qtd == dp[n][k])
			{
				r -= j*w[i], qtd += j;
				ans[i] = j;
				break;
			}
		}
	}

	printf("%d", ans[1]);
	for (int i = 2; i <= n; i++)
		printf(" %d", ans[i]);
	printf("\n");
}
