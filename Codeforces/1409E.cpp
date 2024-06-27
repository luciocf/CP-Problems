// Codeforces 1409E - Two Platforms
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

int a[maxn], mx[maxn];

void solve()
{
    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        mx[i] = 0;
    }
    mx[n+1] = 0;

    for (int i = 1; i <= n; i++)
    {
        int y;
        cin >> y;
    }

    sort(a+1, a+n+1);
    
    int ptr = n;
    for (int i = n; i >= 1; i--)
    {
        while (ptr >= i and a[ptr]-a[i] > k)
            ptr--;

        mx[i] = max(mx[i+1], ptr-i+1); 
    }

    int ans = 0;
    ptr = 1;
    for (int i = 1; i <= n; i++)
    {
        while (ptr <= i and a[i]-a[ptr] > k)
            ptr++;

        ans = max(ans, mx[i+1]+i-ptr+1);
    }

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
 
