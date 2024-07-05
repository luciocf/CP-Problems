// Codeforces 1972D2 - Reverse Card (Hard Version)
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

int gcd(int a, int b)
{
    if (!b) return a;
    return gcd(b, a%b);
}

void solve()
{
    int n, m;
    cin >> n >> m;
    
    ll ans = 0;

    for (int b = 1; b*b <= m; b++)
    {
        for (int a = 1; a*a <= n; a++)
        {
            if (gcd(a, b) != 1) continue;

            int s = a+b;
            int mx = min(n/a, m/b);

            ans += 1ll*(mx/s);
        }
    }

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

