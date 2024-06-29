// Codeforces 1379C - Choosing flowers
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

pii a[maxn];

void solve()
{
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; i++)
        cin >> a[i].ss >> a[i].ff;

    sort(a+1, a+m+1);

    ll sum = 0, ans = 0;
    set<pii> st;

    for (int i = 1; i <= m; i++)
    {
        while (st.size() and (st.size()+1 > n or st.begin()->ff < a[i].ff))
        {
            sum -= 1ll*st.begin()->ff;
            st.erase(st.begin());
        }

        int x = n-st.size()-1;
        ans = max(ans, 1ll*a[i].ss+1ll*a[i].ff*x+sum);
        
        st.insert({a[i].ss, i});
        sum += 1ll*a[i].ss;
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

