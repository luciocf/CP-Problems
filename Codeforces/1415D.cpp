// Codeforces 1415D - XOR-gun
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

int a[maxn];
int pref[maxn];

void solve()
{
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        pref[i] = pref[i-1] ^ a[i]; 
    }

    if (n > 90)
    {
        cout << "1\n";
        return;
    }

    int ans = maxn;
    for (int l = 1; l <= n; l++)
        for (int r = l+1; r <= n; r++)
            for (int k = l+1; k <= r; k++)
                if ((pref[r]^pref[k-1]) < (pref[k-1]^pref[l-1]))
                    ans = min(ans, r-l-1);

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
 
