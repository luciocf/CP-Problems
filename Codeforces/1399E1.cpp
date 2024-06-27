// Codeforces 1399E1 - Weights Division (easy version)
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

vector<pii> grafo[maxn];
int sub[maxn], edge[maxn];

void dfs(int u, int p)
{
    for (auto pp: grafo[u])
    {
        int v = pp.ff;
        if (v == p) continue;
        dfs(v, u);

        sub[u] += sub[v];
        edge[v] = pp.ss;
    }

    if (grafo[u].size() == 1 and u != 1) sub[u] = 1;
}

void solve()
{
    int n;
    ll S;
    cin >> n >> S;

    for (int i = 1; i <= n; i++)
        grafo[i].clear(), sub[i] = 0;

    for (int i = 1; i < n; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        
        grafo[u].pb({v, w});
        grafo[v].pb({u, w});
    }

    dfs(1, 0);

    set<pair<ll, int>> st;
    ll s = 0;

    for (int i = 2; i <= n; i++)
    {
        s += 1ll*sub[i]*edge[i];
        st.ins({1ll*sub[i]*(edge[i]/2ll)-1ll*sub[i]*edge[i], i});
    }
    
    int ans = 0;
    while (s > S)
    {
        s += st.begin()->ff;
        ans++;

        int u = st.begin()->ss;
        st.erase(st.begin());

        edge[u] /= 2;
        st.ins({1ll*sub[u]*(edge[u]/2ll)-1ll*sub[u]*edge[u], u});
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
 
