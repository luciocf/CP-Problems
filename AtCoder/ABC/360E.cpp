// ABC 360E - Random Swaps of Balls
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

const int maxn = 1e5+10;
const int mod = 998244353;

int dp[maxn][2];

int pot(int a, int b)
{
    if (!b) return 1;
    int t = pot(a, b/2);
    if (b&1) return (1ll*a*((1ll*t*t)%mod))%mod;
    return (1ll*t*t)%mod;
}

int frac(int x, int y)
{
    return (1ll*x*pot(y, mod-2))%mod;
}

void solve()
{
    int n, k;
    cin >> n >> k;
    
    dp[0][0] = 1;
    for (int i = 1; i <= k; i++)
    {
        dp[i][0] = (1ll*dp[i-1][0]*frac((1ll*(n-1)*(n-1)+1ll)%mod, (1ll*n*n)%mod))%mod;
        dp[i][0] = (1ll*dp[i][0] + 1ll*dp[i-1][1]*frac(2, (1ll*n*n)%mod))%mod;

        dp[i][1] = (1ll*dp[i-1][0]*frac((2*(n-1))%mod, (1ll*n*n)%mod))%mod;
        dp[i][1] = (1ll*dp[i][1] + 1ll*dp[i-1][1]*frac((1ll*n*n-2+mod)%mod, (1ll*n*n)%mod))%mod;
    }

    int ans = dp[k][0];
    int s = (1ll*n*(n+1)/2ll - 1 + mod)%mod;
    ans = (1ll*ans + 1ll*dp[k][1]*frac(s, n-1))%mod;

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

