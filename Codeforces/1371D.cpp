// Codeforces 1371D - Grid-00100
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

const int maxn = 310;

int a[maxn][maxn];

void solve()
{
    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            a[i][j] = 0;

    if (k%n) cout << "2\n";
    else cout << "0\n";

    for (int i = 1; i <= n; i++)
    {
        if (k == 0) break;

        int c = 1;
        for (int r = i; r <= n; r++, c++)
        {
            a[r][c] = 1;
            k--;
            if (k == 0) break;
        }

        if (k == 0) break;

        for (int r = 1; c <= n; r++, c++)
        {
            a[r][c] = 1;
            k--;
            if (k == 0) break;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            cout << a[i][j];
        cout << nl;
    }
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

