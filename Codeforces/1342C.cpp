// Codeforces 1342C - Yet Another Counting Problem
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

int gcd(int a, int b)
{
    if (!b) return a;
    return gcd(b, a%b);
}

int pref[200*200+10];

void solve()
{
    int a, b, q;
    cin >> a >> b >> q;

    int lcm = a*b/gcd(a, b);
    
    for (int i = 1; i < lcm; i++)
        pref[i] = pref[i-1] + ((i%a)%b != (i%b)%a ? 1 : 0); 

    while (q--)
    {
        ll l, r;
        cin >> l >> r;

        ll L = (l-1)/lcm, lm = (l-1)%lcm;
        ll R = r/lcm, rm = r%lcm;
        
        ll ans = 1ll*pref[lcm-1]*R + 1ll*pref[rm] - 1ll*pref[lcm-1]*L - 1ll*pref[lm];
        cout << ans << " ";
    }
    cout << nl;
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
 
