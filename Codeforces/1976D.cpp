// Codeforces 1976D - Invertible Bracket Sequences
// Lucio Figueiredo

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <cstring>
#include <set>
#include <map>
#include <cmath>

#define ff first
#define ss second
#define mkp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 2e5+10;

void solve(void)
{
	string s;
	cin >> s;
	int n = s.size();

	map<int, int> mp;
	vector<int> pref(n+1);

	pref[0] = 0;

	mp[0] = 1;
	ll ans = 0;

	for (int r = 1; r <= n; r++)
	{
		pref[r] = pref[r-1] + (s[r-1] == '(' ? 1 : -1);

		while (mp.size() and 2*mp.begin()->ff < pref[r])
			mp.erase(mp.begin());

		ans += 1ll*mp[pref[r]];
		mp[pref[r]]++;
	}

	cout << ans << "\n";
}

int main(void)
{
	int tc;
	cin >> tc;

	while (tc--)
	{
		solve();
	}
}
