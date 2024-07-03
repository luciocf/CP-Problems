// Codeforces 1426F - Number of Subsequences
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

int pref[3][maxn], pot[maxn];

int get(int q, int l, int r)
{
    if (r < l) return 0;
    return pref[q][r]-pref[q][l-1];
}

void solve()
{
    int n;
    string s;
    cin >> n >> s;

    pot[0] = 1;
    for (int i = 1; i <= n; i++)
        pot[i] = (3ll*pot[i-1])%mod;
    
    char ca[3] = {'a', 'c', '?'};

    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 3; j++)
            pref[j][i] = pref[j][i-1] + (s[i-1] == ca[j] ? 1 : 0);

    int ans = 0;
    int k = get(2, 1, n);

    for (int i = 1; i <= n; i++)
    {
        if (s[i-1] != 'b') continue;

        int x = 1ll*pot[k]*((1ll*get(0, 1, i-1)*get(1, i+1, n))%mod)%mod;
        ans = (ans + x)%mod;

        if (k >= 1) x = 1ll*pot[k-1]*((1ll*get(0, 1, i-1)*get(2, i+1, n))%mod)%mod;
        else x = 0;
        ans = (ans + x)%mod;

        if (k >= 1) x = 1ll*pot[k-1]*((1ll*get(2, 1, i-1)*get(1, i+1, n))%mod)%mod;
        else x = 0;
        ans = (ans + x)%mod;
        
        if (k >= 2) x = 1ll*pot[k-2]*((1ll*get(2, 1, i-1)*get(2, i+1, n))%mod)%mod;
        else x = 0;
        ans = (ans + x)%mod;
    }

    for (int i = 1; i <= n; i++)
    {
        if (s[i-1] != '?') continue;
        int x = 0;

        if (k >= 1) x = 1ll*pot[k-1]*((1ll*get(0, 1, i-1)*get(1, i+1, n))%mod)%mod;
        else x = 0;
        ans = (ans + x)%mod;

        if (k >= 2) x = 1ll*pot[k-2]*((1ll*get(0, 1, i-1)*get(2, i+1, n))%mod)%mod;
        else x = 0;
        ans = (ans + x)%mod;

        if (k >= 2) x = 1ll*pot[k-2]*((1ll*get(2, 1, i-1)*get(1, i+1, n))%mod)%mod;
        else x = 0;
        ans = (ans + x)%mod;
        
        if (k >= 3) x = 1ll*pot[k-3]*((1ll*get(2, 1, i-1)*get(2, i+1, n))%mod)%mod;
        else x = 0;
        ans = (ans + x)%mod;
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

