// Codeforces 1978F - Large Graph
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

const int maxn = 2e6+10;

int a[maxn];
int comp[2][maxn];

struct DSU
{
    int pai[maxn], peso[maxn];

    void init(int n)
    {
        for (int i = 1; i <= n; i++)
            pai[i] = i, peso[i] = 1;
    }

    int Find(int x)
    {
        if (pai[x] == x) return x;
        return pai[x] = Find(pai[x]);
    }

    void Join(int x, int y)
    {
        x = Find(x), y = Find(y);
        if (x == y) return;
        
        if (peso[x] < peso[y]) swap(x, y);

        pai[y] = x, peso[x] += peso[y];
    }
} dsu;

int n, k;
int spf[maxn];

void sieve(void)
{
    for (int i = 2; i < maxn; i++)
        spf[i] = i;

    for (int i = 2; i < maxn; i++)
        if (spf[i] == i)
            for (int j = 2*i; j < maxn; j+=i)
                if (spf[j] == j)
                    spf[j] = i;
}

vector<int> multiples[maxn];

void doIt(void)
{
    vector<int> primes;
    for (int i = 1; i <= n; i++)
    {
        int x = a[i];
        while (x > 1)
        {
            multiples[spf[x]].pb(i);
            primes.pb(spf[x]);
            x /= spf[x];
        }
    }

    sort(all(primes));
    primes.erase(unique(all(primes)), primes.end());
    
    for (auto p: primes)
    {
        vector<int> ind;
        for (int j = (int)multiples[p].size()-1; j >= 0; j--)
            ind.pb(comp[0][multiples[p][j]]);
        for (int j = (int)multiples[p].size()-1; j >= 0; j--)
            if (multiples[p][j] != 1)
                ind.pb(comp[1][multiples[p][j]]);

        for (int j = 0; j+1 < ind.size(); j++)
            if (ind[j+1]-ind[j] <= k)
                dsu.Join(ind[j], ind[j+1]);
    }

    for (int i = 1; i <= n; i++)
    {
        int x = a[i];
        while (x > 1)
        {
            multiples[spf[x]].clear();
            x /= spf[x];
        }
    }
}

void solve()
{
    cin >> n >> k;

    for (int i = 1; i <= n; i++)
        cin >> a[i];
    
    int cc = 1;
    for (int i = n; i >= 1; i--)
        comp[0][i] = cc++;
    comp[1][1] = n;
    for (int i = n; i > 1; i--)
        comp[1][i] = cc++;

    dsu.init(cc);
    doIt();
    
    ll ans = 0;
    for (int i = 1; i < cc; i++)
        if (dsu.Find(i) == i)
            ans++;
    
    if (a[1] == 1) ans += 1ll*(n-1);
    for (int i = 2; i <= n; i++)
        if (a[i] == 1)
            ans += 1ll*(n-2);

    cout << ans << nl;
}

int main(void)
{
	cin.tie(0)->sync_with_stdio(0); 
    cin.exceptions(cin.failbit);
    // xor ^ 
    
	int tc = 1;
	cin >> tc;
    sieve();
	while (tc--)
	{
		solve();
	}
}

