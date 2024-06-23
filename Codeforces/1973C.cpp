// Codeforces 1973C - Cat, Fox and Double Maximum
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

void solve()
{
	int n;
	cin >> n;

	vector<int> a(n), b(n);

	bool rev = 0;
	for (int i = 0; i < n; i++)
		cin >> a[i];

	for (int i = 0; i < n; i++)
	{
		if (i%2 == 1 and a[i] == 1)
		{
			rev = 1;
			reverse(all(a));
		}
	}

	vector<pii> m1, m2;

	for (int i = 0; i < n; i++)
	{
		if (i%2 == 0) m1.push_back({a[i], i});
		else m2.push_back({a[i], i});
	}

	sort(all(m1), greater<pii>());
	sort(all(m2), greater<pii>());

	for (auto x: m2)
		m1.pb(x);

	for (int i = 0; i < m1.size(); i++)
		b[m1[i].ss] = i+1;

	if (rev) reverse(all(b));

	for (int i = 0; i < n; i++)
		cout << b[i] << " ";
	cout << "\n";
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
