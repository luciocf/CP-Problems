// Codeforces 1408D - Searchlights
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

const int maxn = 2e3+10;
const int maxv = 1e6+10;
const int inf = 1e9+10;

pii a[maxn], b[maxn];
int yMin[maxv];

void solve()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i].ff >> a[i].ss;
    for (int i = 1; i <= m; i++)
        cin >> b[i].ff >> b[i].ss;
    
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i].ff <= b[j].ff)
                yMin[b[j].ff-a[i].ff] = max(yMin[b[j].ff-a[i].ff], b[j].ss-a[i].ss+1);

    int ans = inf, mnY = 0;
    for (int x = maxv-1; x >= 0; x--)
    {
        mnY = max(mnY, yMin[x]);
        ans = min(ans, x+mnY);
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
 
