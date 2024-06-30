// Codeforces 1364C - Ehab and Prefix MEXs
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

bool mark[maxn];

void solve()
{
    int n;
    cin >> n;

    vector<int> a(n+1), vv;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        mark[a[i]] = 1;
    }
    
    for (int i = 0; i <= n+1; i++)
        if (!mark[i])
            vv.pb(i);
    
    int ptr = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i > 1 and a[i] > a[i-1]) cout << a[i-1] << " ";
        else cout << vv[ptr++] << " ";
    }
    cout << nl;
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

