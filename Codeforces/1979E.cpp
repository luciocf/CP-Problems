// Codeforces 1979E - Manhattan Triangle
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
    int n, d;
    cin >> n >> d;

    map<pii, int> mp;
    set<pii> st;
    for (int i = 1; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;

        a[i] = {x, y};
        mp[a[i]] = i;
        st.ins({x+y, x});
    }
    
    int ans[3] = {0, 0, 0};
    // first case
    for (int i = 1; i <= n; i++)
    {
        auto [x, y] = a[i];
        if (mp.find(mkp(x+d/2, y-d/2)) == mp.end()) continue;
        
        bool ok = 1;
        auto it = st.lower_bound({x+y+d, x+d/2});
        if (it == st.end() or it->ff > x+y+d or it->ss > x+d) ok = 0;
    
        if (ok)
        {
            ans[0] = i, ans[1] = mp[mkp(x+d/2, y-d/2)];
            ans[2] = mp[mkp(it->ss, it->ff-it->ss)];
            break;
        }
        
        ok = 1;
        it = st.lower_bound({x+y-d, x-d/2});
        if (it == st.end() or it->ff > x+y-d or it->ss > x) ok = 0;

        if (ok)
        {
            ans[0] = i, ans[1] = mp[mkp(x+d/2, y-d/2)];
            ans[2] = mp[mkp(it->ss, it->ff-it->ss)];
            break;
        }
    }

    st.clear();
    for (int i = 1; i <= n; i++)
        st.ins({a[i].ff-a[i].ss, a[i].ff});
    
    // second case
    for (int i = 1; i <= n; i++)
    {
        auto [x, y] = a[i];
        if (mp.find(mkp(x+d/2, y+d/2)) == mp.end()) continue;

        bool ok = 1;
        auto it = st.lower_bound({x-y+d, x+d/2});
        if (it == st.end() or it->ff > x-y+d or it->ss > x+d) ok = 0;

        if (ok)
        {
            ans[0] = i, ans[1] = mp[mkp(x+d/2, y+d/2)];
            ans[2] = mp[mkp(it->ss, -(it->ff-it->ss))];
            break;
        }

        ok = 1;
        it = st.lower_bound({x-y-d, x-d/2});
        if (it == st.end() or it->ff > x-y-d or it->ss > x) ok = 0;

        if (ok)
        {
            ans[0] = i, ans[1] = mp[mkp(x+d/2, y+d/2)];
            ans[2] = mp[mkp(it->ss, -(it->ff-it->ss))];
            break;

        }
    }

    cout << ans[0] << " " << ans[1] << " " << ans[2] << nl;
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

