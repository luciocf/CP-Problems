// Timus 1574 - Mathematicians and brackets
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

const int maxn = 1e5+10;

int pref[maxn];
int mn[2][maxn];

int main(void)
{
	string s;
	cin >> s;
	int n = s.size();

	for (int i = 1; i <= n; i++)
		pref[i] = pref[i-1] + (s[i-1] == ')' ? -1 : 1);

	if (pref[n] != 0)
	{
		cout << "0\n";
		return 0;
	}

	mn[0][1] = pref[1];
	for (int i = 2; i <= n; i++)
		mn[0][i] = min(mn[0][i-1], pref[i]);

	mn[1][n] = pref[n];
	for (int i = n-1; i >= 1; i--)
		mn[1][i] = min(mn[1][i+1], pref[i]);

	int ans = (mn[0][n] >= 0 ? 1 : 0);
	int suf = 0;
	for (int i = n; i >= 2; i--)
	{
		suf += (s[i-1] == ')' ? -1 : 1);
		if (mn[0][i-1] >= -suf and mn[1][i] >= pref[i-1])
			ans++;
	}

	cout << ans << "\n";
}
