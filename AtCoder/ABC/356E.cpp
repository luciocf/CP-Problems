// ABC 356E - Max/Min
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

const int maxn = 2e6+10;

int a[maxn];
int pref[maxn];

void solve()
{
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        pref[a[i]]++;
    }

    for (int i = 1; i < maxn; i++)
        pref[i] += pref[i-1];
    
    ll ans = 0;
    for (int i = 1; i < maxn; i++)
        for (int j = 2*i; j < maxn; j += i)
           ans += 1ll*(pref[i]-pref[i-1])*(j/i-1)*(pref[j-1]-pref[j-i-(j/i == 2 ? 0 : 1)]);
    
    for (int i = 1; i < maxn; i++)
    {
        int x = pref[i]-pref[i-1];
        ans += 1ll*x*(x-1)/2ll;
    }

    cout << ans << nl;
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

