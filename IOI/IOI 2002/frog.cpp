// IOI 2002 - The Troublesome Frog
// Lúcio Cardoso

// Solution:

// 1. Use a dp[i][j] to know the greatest amount of positions in a line starting at i and passing through j.

// 2. dp[i][j] = 1+dp[j][l], where l is the next position with same spacing to j as i.

// 3. Also, be careful to check if the line leaves the board.

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

const int maxn = 5001;

typedef pair<short, short> pii;

short h, w, n;

pii pt[maxn];

short dp[maxn][maxn];

map<pii, short> existe;

bool comp(pii a, pii b)
{
	if (a.ff != b.ff) return a.ff > b.ff;
	return a.ss > b.ss;
}

int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0);

	cin >> h >> w >> n;

	for (short i = 1; i <= n; i++)
		cin >> pt[i].ff >> pt[i].ss;

	sort(pt+1, pt+n+1, comp);

	for (short i = 1; i <= n; i++)
		existe[pt[i]] = i;

	short ans = 0;

	for (short i = 1; i <= n; i++)
	{
		for (short j = i-1; j >= 1; j--)
		{
			short a = pt[j].ff-pt[i].ff, b = pt[j].ss-pt[i].ss;
			short l;

			short x = 0;

			if (existe.find({pt[j].ff+a, pt[j].ss+b}) == existe.end())
			{
				if (pt[j].ff+a > h || pt[j].ff+a < 1 || pt[j].ss+b > w || pt[j].ss+b < 1)
					x = 1;
			}
			else
			{
				l = existe[{pt[j].ff+a, pt[j].ss+b}];
				x = dp[j][l];
			}

			if (x != 0)
			{
				dp[i][j] = x+1;
				if (pt[i].ff-a > h || pt[i].ff-a < 1 || pt[i].ss-b > w || pt[i].ss-b < 1)
					ans = max(ans, dp[i][j]);
			}
		}
	}

	if (ans >= 3)
		cout << ans << "\n";
	else
		cout << "0\n";
}
