// Codeforces 1413C - Perform Easily
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
const int inf = 2e9+10;

int v[7], a[maxn];
vector<int> dif[maxn];
vector<pii> vv;
int ptr[maxn];

void solve()
{
    for (int i = 1; i <= 6; i++)
        cin >> v[i];

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        for (int j = 1; j <= 6; j++)
            dif[i].pb(a[i]-v[j]), vv.pb({a[i]-v[j], i});
        sort(all(dif[i]));
    }

    sort(all(vv));
    
    int ans = inf;
    
    bool done = 0;
    set<pii> st;

    for (int i = 1; i <= n; i++)
        st.ins({dif[i][0], i});

    for (auto [mn, ind]: vv)
    {
        auto pp = *(st.find({dif[ind][ptr[ind]], ind}));
        st.erase(pp);

        while (st.size() and st.begin()->ff < mn)
        {
            int i = st.begin()->ss;
            while (ptr[i]+1 <= 5 and dif[i][ptr[i]] < mn)
                ptr[i]++;

            if (dif[i][ptr[i]] < mn)
            {
                done = 1;
                break;
            }

            st.erase(st.begin());
            st.ins({dif[i][ptr[i]], i});
        }

        if (done) break;

        ans = min(ans, (st.size() ? st.rbegin()->ff-mn : 0));
        st.ins(pp);
    }

    cout << ans << nl;
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
 
