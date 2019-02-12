// IOI 2004 - Hermes
// Lúcio Cardoso

#include <bits/stdc++.h>
#define X first
#define Y second

using namespace std;

const int maxn = 2e4+10;
const int maxc = 2e3+10;
const int inf = 1e9+10;
const int add = 1e3;

typedef pair<int, int> pii;

int n;
int dp[2][maxc][2];

pii pt[maxn];

int main(void)
{
	cin >> n;
	
	for (int i = 1; i <= n; i++)
	{
		cin >> pt[i].X >> pt[i].Y;
		pt[i].X += add, pt[i].Y += add;
	}

	pt[0] = {add, add};

	for (int i = n-1; i >= 0; i--)
	{
		int a = (i+1)%2, b = i%2;

		for (int y = 0; y < maxc; y++)
			dp[b][y][1] = min(abs(pt[i+1].X-pt[i].X) + dp[a][y][1], abs(pt[i+1].Y-y) + dp[a][pt[i].X][0]);

		for (int x = 0; x < maxc; x++)
			dp[b][x][0] = min(abs(pt[i+1].Y-pt[i].Y) + dp[a][x][0], abs(pt[i+1].X-x) + dp[a][pt[i].Y][1]);
	}

	cout << dp[0][add][0] << "\n";
}
