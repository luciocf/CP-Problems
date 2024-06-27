// Codeforces 1396A - Multiples of Length
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

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n+1);
    
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    if (n == 1)
    {
        cout << "1 1\n";
        cout << -a[1] << nl;
        cout << "1 1\n";
        cout << 0 << nl;
        cout << "1 1\n";
        cout << 0 << nl;
        return;
    }

    cout << "1 " << n << nl;
    for (int i = 1; i <= n; i++)
        cout << -1ll*a[i]*n << " ";
    cout << nl;
    
    cout << "1 " << n-1 << nl;
    for (int i = 1; i < n; i++)
        cout << 1ll*a[i]*(n-1) << " ";
    cout << nl;

    cout << "2 " << n << nl;
    for (int i = 2; i < n; i++)
        cout << "0 ";
    cout << 1ll*a[n]*(n-1) << nl;
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
 
