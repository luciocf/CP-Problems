// ABC 357E - Reachability in Functional Graph
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

int f[maxn];
vector<int> grafo[maxn];
int nivel[maxn], sub[maxn];
bool mark[maxn], seen[maxn];

ll ans;
int sz;
vector<int> comp;
bool inCycle[maxn];

void dfs(int u)
{
    mark[u] = 1;
    sub[u] = 1;
    comp.pb(u);

    for (auto v: grafo[u])
    {
        if (mark[v])
        {
            sz = nivel[u]-nivel[v]+1;

            int k = u;
            inCycle[k] = 1;
            while (k != v)
            {
                k = f[k];
                inCycle[k] = 1;
            }
            continue;
        }

        nivel[v] = nivel[u]+1;
        dfs(v);
        sub[u] += sub[v];
    }
}

void solve()
{
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> f[i];
        grafo[f[i]].pb(i);
    }

    for (int i = 1; i <= n; i++)
    {
        if (mark[i]) continue;
        int u = i;
        
        seen[u] = 1;
        while (!seen[f[u]])
            seen[f[u]] = 1, u = f[u];
        
        comp.clear();
        dfs(u);
        ans += 1ll*sz*sz;
        ans += 1ll*sz*((int)comp.size()-sz);
        
        for (auto v: comp)
            if (!inCycle[v])
                ans += 1ll*sub[v];
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

