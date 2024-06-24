// Codeforces 1348C - Phoenix and Distribution
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

using namespace std;

#define ff first
#define ss second
#define mkp make_pair
#define pb push_back
#define sz(x) (int)(x).size()
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert

typedef pair<int, int> pii;
typedef long long ll;

const char nl = '\n';

int fq[26];

void solve()
{
	int n, k;
	cin >> n >> k;
	string s;
	cin >> s;

	sort(all(s));

	if (s[k-1] != s[0])
	{
		cout << s[k-1] << "\n";
		return;
	}

	string ans = "";
	ans += s[0];

	if (s[k] == s[n-1])
	{
		for (int j = 0; j < (n-k)/k; j++)
			ans += s[k];
		if ((n-k)%k) ans += s[k];
		cout << ans << nl;
		return;
	}

	for (int i = k; i < n; i++)
		ans += s[i];

	cout << ans << nl;
}

int main(void)
{
	int tc = 1;
	cin >> tc;
	while (tc--)
	{
		solve();
	}
}
