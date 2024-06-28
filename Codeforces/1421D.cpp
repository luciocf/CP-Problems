// Codeforces 1421D - Hexagons
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

const ll inf = 1e18+10;

void solve()
{
    int x, y;
    cin >> x >> y;

    int c[7];
    for (int i = 1; i <= 6; i++)
        cin >> c[i];

    ll ans = inf;

    // not using c1, c4
    ll at = 0;
    if (x >= 0) at += 1ll*c[6]*x;
    else at += 1ll*c[3]*abs(x);

    if (y >= 0) at += 1ll*c[2]*y;
    else at += 1ll*c[5]*abs(y);

    ans = at;

    // fulfilling x
    at = 0;
    if (x >= 0)
    {
        at += 1ll*x*c[1];
        int y2 = y-x;
        if (y2 >= 0) at += 1ll*y2*c[2];
        else at += 1ll*abs(y2)*c[5];
    }
    else
    {
        at += 1ll*abs(x)*c[4];
        int y2 = y-x;
        if (y2 >= 0) at += 1ll*y2*c[2];
        else at += 1ll*abs(y2)*c[5];
    }

    ans = min(ans, at);

    // fulfilling y
    at = 0;
    if (y >= 0)
    {
        at += 1ll*y*c[1];
        int x2 = x-y;
        if (x2 >= 0) at += 1ll*x2*c[6];
        else at += 1ll*abs(x2)*c[3];
    }
    else
    {
        at += 1ll*abs(y)*c[4];
        int x2 = x-y;
        if (x2 >= 0) at += 1ll*x2*c[6];
        else at += 1ll*abs(x2)*c[3];
    }

    ans = min(ans, at);

    cout << ans << nl;
}

int main(void)
{
	cin.tie(0)->sync_with_stdio(0); 
    cin.exceptions(cin.failbit);
    // xor ^ 
    
	int tc = 1;
	cin >> tc;
	while (tc--)
	{
		solve();
	}
}

