// Codeforces 1391D - 505
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

const int maxn = 1e6+10;

vector<char> b[maxn];
int a[maxn][4];

int n, m;
int dp[maxn][1<<3];

int qtdDiff(int i, int mask)
{
    int ans = 0;
    for (int j = 0; j < m; j++)
    {
        int d = 0;
        if (mask&(1<<j)) d = 1;

        if (d != a[i][j]) ans++;
    }
    return ans;
}

int qtdS(int l, int r, int mask, int mask2)
{
    int ans = 0;
    for (int j = l; j <= r; j++)
    {
        if (mask&(1<<j)) ans++;
        if (mask2&(1<<j)) ans++;
    }

    return ans;
}

int solve(int i, int mask)
{
    if (i == n) return 0;
    if (dp[i][mask] != -1) return dp[i][mask];

    int ans = maxn;

    for (int mask2 = 0; mask2 < (1<<m); mask2++)
    {
        int qtd = qtdS(0, 1, mask, mask2);
        if (qtd%2 == 0) continue;

        if (m >= 3)
        {
            qtd = qtdS(1, 2, mask, mask2);
            if (qtd%2 == 0) continue;
        }

        ans = min(ans, qtdDiff(i, mask2) + solve(i+1, mask2));
    }

    return dp[i][mask] = ans;
}

void solve()
{
    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            char x;
            cin >> x;
            b[i].pb(x);
        }
    }

    if (n >= 4 and m >= 4)
    {
        cout << "-1\n";
        return;
    }
    
    if (m >= 4)
    {
        for (int j = 0; j < m; j++)
            for (int i = 0; i < n; i++)
                a[j][i] = (b[i][j] == '1' ? 1 : 0);
        swap(n, m);
    }
    else
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                a[i][j] = (b[i][j] == '1' ? 1 : 0);
    }

    if (m == 1)
    {
        cout << "0\n";
        return;
    }

    memset(dp, -1, sizeof dp);
    
    int ans = maxn;
    for (int mask = 0; mask < (1<<m); mask++)
        ans = min(ans, qtdDiff(0, mask)+solve(1, mask));
    
    if (ans == maxn) cout << "-1\n";
    else cout << ans << nl;
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

