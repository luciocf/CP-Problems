// Timus 1403 - Courier
// Lucio Figueiredo

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <cstring>
#include <set>
#include <map>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 1e3+10;

struct S
{
	int t, w, ind;

	bool operator<(const S &o) const
	{
		return t < o.t;
	}
} a[maxn];

int dp[maxn][maxn];

int main(void)
{
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++)
	{
		cin >> a[i].t >> a[i].w;
		a[i].ind = i;
	}	

	sort(a+1, a+n+1);

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			dp[i][j] = dp[i-1][j];

		for (int j = min(n, a[i].t); j >= 1; j--)
			dp[i][j] = max(dp[i][j], a[i].w + dp[i-1][j-1]);
	}

	int ans = 0;
	int tot = 0;
	for (int i = 1; i <= n; i++)
	{
		if (dp[n][i] >= ans)
		{
			ans = dp[n][i];
			tot = i;
		}
	}

	vector<int> ind;
	for (int i = n; i >= 1; i--)
	{
		for (int j = 1; j <= n; j++)
		{
			if (a[i].w + dp[i-1][tot-1] == ans)
			{
				ind.push_back(a[i].ind);
				tot--;
				ans -= a[i].w;
				break;
			}
		} 
	}

	reverse(ind.begin(), ind.end());
	cout << ind.size() << "\n";
	for (auto i: ind)
		cout << i << " ";
	cout << "\n";
}
