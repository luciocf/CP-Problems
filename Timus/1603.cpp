// Timus 1603 - Erudite
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

char a[6][6];
bool mark[6][6];

int linha[4] = {-1, 1, 0, 0};
int coluna[4] = {0, 0, 1, -1};

string s;

bool found(int i, int j, int k)
{
	if (a[i][j] != s[k]) return 0;
	if (k == s.size()-1) return 1;

	mark[i][j] = 1;

	bool ok = 0;
	for (int p = 0; p < 4; p++)
	{
		int x = i+linha[p], y = j+coluna[p];

		if (x >= 1 and x <= 4 and y >= 1 and y <= 4 and !mark[x][y] and a[x][y] == s[k+1])
			ok |= found(x, y, k+1);
	}

	mark[i][j] = 0;

	return ok;
}

int main(void)
{
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			cin >> a[i][j];

	int n;
	cin >> n;
	while (n--)
	{
		cin >> s;

		bool ok = 0;
		for (int i = 1; i <= 4; i++)
			for (int j = 1; j <= 4; j++)
				ok |= found(i, j, 0);

		if (ok) cout << s << ": YES\n";
		else cout << s << ": NO\n";
	}
}
