// Codeforces 1974E - Money Buys Happiness
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

const int maxn = 55;
const int maxh = 1e5+10;
const ll inf = 1e18+10;

int n, x, c[maxn], h[maxn];
ll  dp[maxn][maxh];

void solve()
{
   cin >> n >> x;
   for (int i = 1; i <= n; i++)
       cin >> c[i] >> h[i];
    
   ll s = 0;
   for (int i = 1; i <= n; i++)
       s += 1ll*h[i];

   for (int i = 1; i <= n; i++)
       for (int j = 0; j <= s; j++)
           dp[i][j] = inf;

   for (int j = 1; j <= s; j++)
       dp[0][j] = inf;

   for (int i = 1; i <= n; i++)
   {
       for (int j = s; j >= 0; j--)
       {
           dp[i][j] = dp[i-1][j];

           if (j >= h[i] and dp[i-1][j-h[i]] != inf and dp[i-1][j-h[i]]+1ll*c[i] <= 1ll*x*(i-1))
               dp[i][j] = min(dp[i][j], dp[i-1][j-h[i]]+1ll*c[i]);
       }
   }

   ll ans = 0;
   for (int i = 0; i <= s; i++)
       if (dp[n][i] != inf)
           ans = i;

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
 
