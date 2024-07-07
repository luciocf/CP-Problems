// ABC 354E - Remove Pairs
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

const int maxn = 19;

int n;
int dp[1<<maxn];
pii a[maxn];

int solve(int mask)
{
    if (mask == 0) return 0;
    if (dp[mask] != -1) return dp[mask];
    
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (!(mask&(1<<i))) continue;

        for (int j = 0; j < n; j++)
        {
            if (j == i) continue;

            if ((mask&(1<<j)) and (a[i].ff == a[j].ff or a[i].ss == a[j].ss))
            {
                int x = solve(mask^(1<<i)^(1<<j));
                if (!x)
                {
                    ans = 1;
                    break;
                }
            }
        }
    }

    return dp[mask] = ans;
}

void solve()
{
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> a[i].ff >> a[i].ss;

    memset(dp, -1, sizeof dp);

   if (solve((1<<n)-1) == 1) cout << "Takahashi\n";
   else cout << "Aoki\n";
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

