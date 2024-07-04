// Codeforces 1349B - Orac and Medians
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
    int n, k;
    cin >> n >> k;

    vector<int> a(n+1);
    bool ok = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        if (a[i] == k) ok = 1;
    }

    if (!ok)
    {
        cout << "no\n";
        return;
    }

    if (n == 1)
    {
        cout << "yes\n";
        return;
    }

    ok = 0;
    for (int i = 1; i < n; i++)
        if (min(a[i], a[i+1]) >= k)
            ok = 1;

    for (int i = 1; i < n-1; i++)
    {
        vector<int> b;
        b.pb(a[i]); b.pb(a[i+1]); b.pb(a[i+2]);
        sort(all(b));

        if (b[1] >= k) ok = 1;
    }

    if (ok) cout << "yes\n";
    else cout << "no\n";
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

