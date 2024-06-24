// Codeforces 1969D - Shop Game
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

const char nl = '\n';

typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 2e5+10;

int a[maxn], b[maxn];
pii num[maxn];

void solve()
{
	int n, k;
	cin >> n >> k;

	for (int i = 1; i <= n; i++)
		cin >> a[i];

	for (int i = 1; i <= n; i++)
	{
		cin >> b[i];
		num[i] = {b[i], a[i]};
	}

	sort(num+1, num+n+1);

	ll ans = 0;

	multiset<int> st;
	ll soma = 0, sub = 0;

	for (int i = n; i >= n-k+1; i--)
	{
		st.insert(num[i].ss);
		sub += 1ll*num[i].ss;
	}
	for (int i = 1; i < n-k+1; i++)
		soma += 1ll*max(0, num[i].ff-num[i].ss);

	ans = max(ans, soma-sub);

	for (int i = n-k; i >= 1; i--)
	{
		soma -= 1ll*max(0, num[i].ff-num[i].ss);

		if (k > 0 and *st.rbegin() > num[i].ss)
		{
			sub -= 1ll*(*st.rbegin());
			sub += 1ll*num[i].ss;

			st.erase(st.find(*st.rbegin()));
			st.insert(num[i].ss);
		}

		ans = max(ans, soma-sub);
	}

	cout << ans << "\n";
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
