#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
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

const int maxn = 1e6+10;

int a[maxn], b[maxn], c[maxn];
ll dp[maxn];
pii diff[maxn];
int best[maxn];

void solve()
{
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    for (int i = 1; i <= m; i++)
        cin >> c[i];

    for (int i = 1; i <= n; i++)
        diff[i] = {a[i]-b[i], a[i]};

    sort(diff+1, diff+n+1);

    int ptr = 1;
    for (int i = maxn-1; i >= 1; i--)
    {
        while (ptr < n and diff[ptr].ss > i)
            ptr++;

        if (diff[ptr].ss <= i)
            best[i] = ptr;
    }

    for (int i = 1; i < maxn; i++)
        if (best[i] != 0)
            dp[i] = 2ll+dp[i-diff[best[i]].ff];

    sort(c+1, c+m+1, greater<int>());

    ll ans = 0;
    ptr = 1;
    for (int i = 1; i <= m; i++)
    {
        while (ptr < n and diff[ptr].ss > c[i])
            ptr++;

        if (diff[ptr].ss > c[i]) continue;

        int k = (c[i]-diff[ptr].ss)/diff[ptr].ff;
        k++;

        c[i] -= k*diff[ptr].ff;
        ans += 2ll*k + dp[c[i]];
    }

    cout << ans << nl;
}

int main(void)
{
	cin.tie(0)->sync_with_stdio(0); 
    cin.exceptions(cin.failbit);
    // xor ^ 
    
	int tc = 1;
//	cin >> tc;
	while (tc--)
	{
		solve();
	}
}

