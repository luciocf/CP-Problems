// Codeforces 1311F - Moving Points
// Lucio Figueiredo

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

const int maxn = 2e5+10;

pii a[maxn];
ll bit[2][maxn];

void upd(int q, int x, int v)
{
    for (; x < maxn; x += (x&-x))
            bit[q][x] += v;
}

ll soma(int q, int x)
{
    ll ans = 0;
    for (; x > 0; x -= (x&-x))
        ans += bit[q][x];
    return ans;
}

void solve()
{
    int n;
    cin >> n;
    
    for (int i = 1; i <= n; i++)
        cin >> a[i].ff;
    
    map<int, int> mp;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].ss;
        mp[a[i].ss];
    }

    int cnt = 0;
    for (auto &x: mp)
        x.ss = ++cnt;

    for (int i = 1; i <= n; i++)
        a[i].ss = mp[a[i].ss];

    sort(a+1, a+n+1);
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int qtd = soma(0, a[i].ss);
        ll pref = soma(1, a[i].ss);

        ans += 1ll*qtd*a[i].ff - pref;

        upd(0, a[i].ss, 1);
        upd(1, a[i].ss, a[i].ff);
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

