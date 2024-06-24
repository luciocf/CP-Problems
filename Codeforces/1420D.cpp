// Codeforces 1420D - Rescue Nibel!
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

const int maxn = 6e5+10;
const int mod = 998244353;

struct Event
{
    int p, t;

    bool operator<(const Event &o) const
    {
        if (p == o.p) return t < o.t;
        return p < o.p;
    }
} event[2*maxn];

int pot(int a, int b)
{
    if (!b) return 1;
    int t = pot(a, b/2);

    if (b%2) return (1ll*a*((1ll*t*t)%mod))%mod;
    return (1ll*t*t)%mod;
}

int fat[maxn];

int choose(int n, int k)
{
    return (1ll*fat[n]*pot((1ll*fat[k]*fat[n-k])%mod, mod-2))%mod;
}

void solve()
{
    int n, k;
    cin >> n >> k;

    fat[0] = 1;
    for (int i = 1; i <= n; i++)
        fat[i] = (1ll*fat[i-1]*i)%mod;

    int m = 0;

    for (int i = 1; i <= n; i++)
    {
        int l, r;
        cin >> l >> r;

        event[++m] = {l, 0};
        event[++m] = {r, 1};
    }
    
    sort(event+1, event+m+1);

    int ans = 0, qtd = 0;
    for (int i = 1; i <= m; i++)
    {
        if (event[i].t == 1) qtd--;
        else
        {
            if (qtd >= k-1) ans = (ans + choose(qtd, k-1))%mod;
            qtd++;
        }
    }

    cout << ans << nl;
}

int main(void)
{
	int tc = 1;
//	cin >> tc;
	while (tc--)
	{
		solve();
	}
}
