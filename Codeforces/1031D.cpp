// Codeforces 1031D - Minimum path
// Lúcio Cardoso

// Solution is the same as in editorial.

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 2e3+10;

int n;
string s[maxn];

int mx[maxn][maxn];

string ans;
vector<pii> pos;

void get(void)
{
	char mn = 'z';

	for (auto pp: pos)
	{
		if (pp.ff < n-1) mn = min(mn, s[pp.ff+1][pp.ss]);
		if (pp.ss < n-1) mn = min(mn, s[pp.ff][pp.ss+1]);
	}

	set<pii> aux;

	ans += mn;

	for (auto pp: pos)
	{
		if (pp.ff < n-1 && s[pp.ff+1][pp.ss] == mn) aux.insert({pp.ff+1, pp.ss});
		if (pp.ss < n-1 && s[pp.ff][pp.ss+1] == mn) aux.insert({pp.ff, pp.ss+1});
	}

	pos.clear();

	for (auto pp: aux)
		pos.push_back(pp);
}

int main(void)
{
	int k;
	cin >> n >> k;

	for (int i = 0; i < n; i++)
		cin >> s[i];

	if (s[0][0] == 'a') mx[0][0] = 1;

	for (int i = 1; i < n; i++)
		mx[0][i] = mx[0][i-1] + (s[0][i] == 'a' ? 1 : 0);

	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int add = (s[i][j] == 'a' ? 1 : 0);

			if (j > 0) mx[i][j] = max(mx[i][j], mx[i][j-1] + add);
			mx[i][j] = max(mx[i][j], mx[i-1][j] + add);
		}
	}

	int x = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (mx[i][j] >= i+j+1-k)
				x = max(x, i+j+1);

	for (int i = 0; i < x; i++)
		ans += 'a';

	if (k >= 2*n-1)
	{
		cout << ans << "\n";
		return 0;	
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i+j+1 == x && mx[i][j] >= i+j+1-k)
				pos.push_back({i, j});

	if (x == 0)
	{
		pos.push_back({0, 0});
		ans += s[0][0];
	}

	while (pos[0].ff+pos[0].ss+1 != 2*n-1)
		get();

	cout << ans << "\n";
}
