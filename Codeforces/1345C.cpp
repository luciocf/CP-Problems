// Codeforces 1345C - Hilbert's Hotel
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

	set<int> st;

	bool ok = 1;
	for (int i = 0; i < n; i++)
	{
		int a;
		cin >> a;

		a = ((a+i)%n + n)%n;

		if (st.find(a) != st.end())
			ok = 0;

		st.ins(a);
	}

	if (st.size() != n) ok = 0;

	if (ok) cout << "YES\n";
	else cout << "NO\n";
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
