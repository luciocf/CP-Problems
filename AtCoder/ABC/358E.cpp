// ABC 358E - Alphabet Tiles
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

const int maxn = 1e3+10;
const int mod = 998244353;

int dp[26][maxn];
int a[maxn], fat[maxn], inv[maxn];

int pot(int a, int b)
{
    if (!b) return 1;
    int t = pot(a, b/2);
    if (b&1) return (1ll*a*((1ll*t*t)%mod))%mod;
    return (1ll*t*t)%mod;
}

int solve(int i, int qtd)
{
    if (qtd == 0) return 1;
    if (i == 26) return 0;
    if (dp[i][qtd] != -1) return dp[i][qtd];

    int ans = 0;
    for (int x = 0; x <= min(a[i], qtd); x++)
        ans = (ans + (1ll*inv[x]*solve(i+1, qtd-x)%mod))%mod;
    return dp[i][qtd] = ans;
}

void solve()
{
    fat[0] = 1;
    inv[0] = 1;
    for (int i = 1; i < maxn; i++)
    {
        fat[i] = (1ll*fat[i-1]*i)%mod;
        inv[i] = pot(fat[i], mod-2);
    }

    int k;
    cin >> k;
    
    for (int i = 0; i < 26; i++)
        cin >> a[i];

    memset(dp, -1, sizeof dp);

    int ans = 0;
    for (int i = 1; i <= k; i++)
        ans = (ans + (1ll*fat[i]*solve(0, i))%mod)%mod;

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

