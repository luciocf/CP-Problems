// Codeforces 1336B - Xenia and Colorful Gems
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
const ll inf = 2e18+10;

int a[3][maxn];

ll sq(int x)
{
    return 1ll*x*x;
}

void solve()
{
    int n[3];
    for (int i = 0; i < 3; i++)
        cin >> n[i];

    for (int i = 0; i < 3; i++)
        for (int j = 1; j <= n[i]; j++)
            cin >> a[i][j];

    for (int i = 0; i < 3; i++)
        sort(a[i]+1, a[i]+n[i]+1);

    int p[3] = {0, 1, 2};
    
    ll ans = inf;
    do
    {
        int ptr[3] = {1, 1, 1};
        int x = p[0], y = p[1], z = p[2];

        for (int i = 1; i <= n[y]; i++)
        {
            while (ptr[0]+1 <= n[x] and a[x][ptr[0]+1] <= a[y][i])
                ptr[0]++;

            while (ptr[2] <= n[z] and a[z][ptr[2]] < a[y][i])
                ptr[2]++;

            if (ptr[2] > n[z] or a[x][ptr[0]] > a[y][i]) continue;

            ans = min(ans, sq(a[x][ptr[0]]-a[y][i]) + sq(a[x][ptr[0]]-a[z][ptr[2]]) + sq(a[y][i]-a[z][ptr[2]]));
        }
    } while (next_permutation(p, p+3));

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
 
