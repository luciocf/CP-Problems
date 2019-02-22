// BOI 2013 - Numbers
// Lúcio Cardoso

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll dp[30][10][10][3][3];

string a, b;

ll solve(int pos, int d1, int d2, int m1, int m2)
{
	if (pos == b.size()) return 0;
	if (dp[pos][d1][d2][m1][m2] != -1) return dp[pos][d1][d2][m1][m2];

	ll ans = 0LL;
	for (int i = 0; i <= 9; i++)
	{
		if ((!i && !pos) || (i == d1 && pos >= 2) || (i == d2 && pos >= 1)) continue;

		int n1 = 2;
		if (!m1) n1 = 0;
		else if (m1 == 1) n1 = 1;
		else if (i < (int)a[pos]-'0') n1 = 0;
		else if (i > (int)a[pos]-'0') n1 = 1;

		int n2 = 2;
		if (!m2) n2 = 0;
		else if (m2 == 1) n2 = 1;
		else if (i < (int)b[pos]-'0') n2 = 0;
		else if (i > (int)b[pos]-'0') n2 = 1;

		int add = 0;

		if (a.size() == b.size() && pos == a.size()-1)
		{
			if (n1 && n2 != 1) add = 1;
			else add = 0;
		}
		else if (pos == a.size()-1 && n1) add = 1;
		else if (pos > a.size()-1 && pos < b.size()-1) add = 1;
		else if (pos == b.size()-1 && n2 != 1) add = 1;

		ans += (ll)add+solve(pos+1, d2, i, n1, n2);
	}

	return dp[pos][d1][d2][m1][m2] = ans;
}

int main(void)
{
	memset(dp, -1, sizeof dp);

	cin >> a >> b;

	int add = (a[0] == '0' ? 1 : 0);
	cout << add+solve(0, 0, 0, 2, 2) << "\n";
}
