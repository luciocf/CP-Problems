// Codeforces 1401D - Maximum Distributed Tree
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
const int mod = 1e9+7;

int sub[maxn], pai[maxn];
vector<int> grafo[maxn];

void dfs(int u, int p)
{
    sub[u] = 1;
    for (auto v: grafo[u])
    {
        if (v == p) continue;

        dfs(v, u);
        sub[u] += sub[v], pai[v] = u;
    }
}

void solve()
{
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
        grafo[i].clear();

    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;

        grafo[u].pb(v); grafo[v].pb(u);
    }

    dfs(1, 0);

    vector<ll> vv;
    for (int i = 1; i <= n; i++)
    {
        for (auto j: grafo[i])
        {
            if (pai[i] == j) continue;
            vv.pb(1ll*sub[j]*(n-sub[j]));
        }
    }

    sort(all(vv));

    int m;
    cin >> m;

    vector<int> primes;
    for (int i = 1; i <= m; i++)
    {
        int x;
        cin >> x;
        primes.pb(x);
    }

    sort(all(primes));
    int ans = 0;
    if (m < n)
    {
        for (int i = 0; i < (n-1)-m; i++)
            ans = (ans + vv[i])%mod;
        
        int ptr = 0;
        for (int i = (n-1)-m; i < n-1; i++)
            ans = (1ll*ans + 1ll*vv[i]*primes[ptr++])%mod;
    }
    else
    {
        int ptr = 0;
        for (int i = 0; i < n-2; i++)
            ans = (1ll*ans + 1ll*vv[i]*primes[ptr++])%mod;

        int mult = 1;
        for (int i = ptr; i < m; i++)
            mult = (1ll*mult*primes[i])%mod;

        ans = (1ll*ans + 1ll*vv.back()*mult)%mod;
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
 
