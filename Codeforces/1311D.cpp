// Codeforces 1311D - Three Integers
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

const int maxn = 3e4+10;

pii best[maxn];

void solve()
{
    int a, b, c;
    cin >> a >> b >> c;

    for (int x = 1; x <= 15000; x++)
    {   
        best[x] = {maxn, maxn};
        for (int i = 1; i*i <= x; i++)
        {
            if (x%i) continue;

            best[x] = min(best[x], {abs(i-a), i});
            if (x/i != i) best[x] = min(best[x], {abs(x/i-a), x/i});
        }
    }

    pair<pii, pii> ans = {{3*maxn, 0}, {0, 0}};
    for (int x = 1; x <= 30000; x++)
    {
        for (int i = 1; i*i <= x; i++)
        {
            if (x%i) continue;

            ans = min(ans, {{abs(c-x) + abs(b-i) + best[i].ff, x}, {i, best[i].ss}});
            if (x/i != i) ans = min(ans, {{abs(c-x)+abs(b-(x/i))+best[x/i].ff, x}, {x/i, best[x/i].ss}});
        }
    }
    
    vector<int> v = {ans.ff.ss, ans.ss.ff, ans.ss.ss};
    sort(all(v));
    cout << ans.ff.ff << nl;
    for (int i = 0; i < 3; i++)
        cout << v[i] << " ";
    cout << nl;
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

