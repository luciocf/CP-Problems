// Codeforces 615D - Multipliers
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
const int mod = 1e9+7;

int qtd[maxn], pref[maxn], suf[maxn];

int pot(int a, int b)
{
    if (!b) return 1;
    int t = pot(a, b/2);
    if (b&1) return (1ll*a*((1ll*t*t)%mod))%mod;
    return (1ll*t*t)%mod;
}

void solve()
{
    int n;
    cin >> n;
    
    for (int i = 1; i <= n; i++)
    {
        int p;
        cin >> p;
        qtd[p]++;
    }

    pref[0] = 1;
    for (int i = 1; i < maxn; i++)
        pref[i] = (1ll*(qtd[i]+1)*pref[i-1])%(mod-1);

    suf[maxn-1] = 1;
    for (int i = maxn-2; i >= 1; i--)
        suf[i] = (1ll*(qtd[i]+1)*suf[i+1])%(mod-1);

    ll ans = 1;
    for (int p = 2; p < maxn; p++)
    {
        for (int i = 1; i <= qtd[p]; i++)
        {
            int pp = (1ll*pref[p-1]*suf[p+1])%(mod-1);

            ans = (ans*pot(pot(p, i), pp))%mod;
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
	while (tc--)
	{
		solve();
	}
}

