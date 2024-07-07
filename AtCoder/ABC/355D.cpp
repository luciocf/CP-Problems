// ABC 355D - Intersecting Intervals
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

const int maxn = 1e6+10;

pii a[maxn];
pii event[maxn];

void solve()
{
    int n;
    cin >> n;
    
    int m = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].ff >> a[i].ss;
        event[++m] = {a[i].ff, 0};
        event[++m] = {a[i].ss, 1};
    }

    sort(event+1, event+m+1);

    ll ans = 0;
    int qtd = 0;
    for (int i = 1; i <= m; i++)
    {
        if (event[i].ss == 0) ans += 1ll*qtd, ++qtd;
        else --qtd;
    }

    cout << ans << nl;
}

int main(void)
{
	cin.tie(0)->sync_with_stdio(0); 
    cin.exceptions(cin.failbit);
    // xor ^ 
    
	int tc = 1;
	while (tc--)
	{
		solve();
	}
}

