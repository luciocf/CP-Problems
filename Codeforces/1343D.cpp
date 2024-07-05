// Codeforces 1343D - Constant Palindrome Sum
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

int sum[maxn];

void solve()
{
    int n, k;
    cin >> n >> k;

    for (int i = 0; i <= 2*k; i++)
        sum[i] = 0;

    vector<int> a(n+1);

    for (int i = 1; i <= n; i++)
        cin >> a[i];
    
    vector<int> vMin, vMax;
    for (int i = 1; i <= n/2; i++)
    {
        vMin.pb(min(a[i], a[n-i+1]));
        vMax.pb(max(a[i], a[n-i+1]));
        sum[a[i]+a[n-i+1]]++;
    }

    sort(all(vMax)); sort(all(vMin));

    int ans = n;

    for (int i = 2; i <= 2*k; i++)
    {
        int x = (int)(vMin.end()-lower_bound(all(vMin), i));
        int y = (int)(lower_bound(all(vMax), i-k)-vMax.begin());

        int qtd = 2*(x+y) + (n/2-x-y-sum[i]);
        ans = min(ans, qtd);
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
 
